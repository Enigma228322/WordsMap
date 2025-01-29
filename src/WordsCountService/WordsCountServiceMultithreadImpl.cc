#include "spdlog/spdlog.h"
#include <filesystem>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cctype>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cstring>

#include "WordsCountService/WordsCountServiceMultithreadImpl.hh"

namespace wordscount {

WordsCountServiceMultithreadImpl::WordsCountServiceMultithreadImpl(const char* inFilename, const char* outFilename, unsigned int num_threads_): inFilename(inFilename), outFilename(outFilename) {
    num_threads = num_threads_ ? num_threads_ : std::thread::hardware_concurrency();
    spdlog::info("Thread number: {}", num_threads);
};

void WordsCountServiceMultithreadImpl::process_chunk(const char* data, size_t start, size_t end, std::unordered_map<std::string, int>& word_counts) {
    bool in_word = false;
    size_t word_start = start;

    for (size_t i = start; i < end; ++i) {
        if (!in_word && !std::isspace(data[i])) {
            word_start = i;
            in_word = true;
        } else if (in_word && std::isspace(data[i])) {
            std::string word(data + word_start, i - word_start);
            std::transform(word.begin(), word.end(), word.begin(),[](unsigned char letter){ return std::tolower(letter); });
            word_counts[word]++;
            in_word = false;
        }
    }

    if (in_word) {
        std::string word(data + word_start, end - word_start);
        std::transform(word.begin(), word.end(), word.begin(),[](unsigned char letter){ return std::tolower(letter); });
        word_counts[word]++;
    }
}

int WordsCountServiceMultithreadImpl::count_words() {
    int fd = open(inFilename, O_RDONLY);
    if (fd == -1) {
        spdlog::error("Error opening file");
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        spdlog::error("Error getting file stats");
        close(fd);
        return 1;
    }

    size_t file_size = sb.st_size;
    if (file_size == 0) {
        spdlog::info("File is empty");
        close(fd);
        return 0;
    }

    void* mapped = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        spdlog::error("Error mmapping the file");
        close(fd);
        return 1;
    }

    close(fd);
    char* data = static_cast<char*>(mapped);

    std::vector<std::pair<size_t, size_t>> chunk_boundaries;
    size_t chunk_size = file_size / num_threads;
    size_t previous_end = 0;

    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = previous_end;
        size_t end = start + chunk_size;

        if (i == num_threads - 1) {
            end = file_size;
        } else {
            while (end < file_size && !std::isspace(data[end])) ++end;
            if (end < file_size) ++end;
        }

        chunk_boundaries.emplace_back(start, end);
        previous_end = end;
    }

    std::vector<std::thread> threads;
    std::vector<std::unordered_map<std::string, int>> thread_maps(num_threads);

    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = chunk_boundaries[i].first;
        size_t end = chunk_boundaries[i].second;

        if (start >= end) continue;

        threads.emplace_back([=, &map = thread_maps[i]] {
            process_chunk(data, start, end, map);
        });
    }

    for (auto& t : threads) t.join();

    for (auto& tmap : thread_maps) {
        for (const auto& [k, v] : tmap) {
            wordsMap[k] += v;
        }
    }

    if (munmap(mapped, file_size) == -1) {
        spdlog::error("Error un-mmapping");
        return 1;
    }
    return 0;
}

void WordsCountServiceMultithreadImpl::write_result() {
    int fd = open(outFilename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        spdlog::error("Failed to opent write file");
        return;
    }

    std::vector<std::pair<std::string, uint32_t>> temporary_vector(wordsMap.begin(), wordsMap.end());
    std::sort(temporary_vector.begin(), temporary_vector.end(), [](std::pair<std::string, uint32_t>& a, std::pair<std::string, uint32_t>& b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });
    std::string serializedData;
    serializedData.reserve(resultSerializedFileSize);
    for (const auto& pair : temporary_vector) {
        serializedData += pair.first + " " + std::to_string(pair.second) + "\n";
    }

    size_t dataSize = serializedData.size();
    if (ftruncate(fd, dataSize) == -1) {
        spdlog::error("ftruncate, write to file error");
        close(fd);
        return;
    }

    void* mapPtr = mmap(nullptr, dataSize, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapPtr == MAP_FAILED) {
        spdlog::error("Failed mmap to output file");
        close(fd);
        return;
    }

    std::memcpy(mapPtr, serializedData.c_str(), dataSize);

    if (msync(mapPtr, dataSize, MS_SYNC) == -1) {
        spdlog::error("Failed to msync");
    }

    if (munmap(mapPtr, dataSize) == -1) {
        spdlog::error("Failed to munmap");
    }

    close(fd);
}

WordsCountServiceMultithreadImpl::~WordsCountServiceMultithreadImpl() {}

} // namespace wordscount;
