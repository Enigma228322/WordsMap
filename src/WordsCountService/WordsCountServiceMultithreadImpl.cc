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

namespace {
bool isSpace(char c) {
    return c < 65 || (c > 90 && c < 97) || c > 122;
}
}; // namespace

namespace wordscount {

WordsCountServiceMultithreadImpl::WordsCountServiceMultithreadImpl(const char* in_filename, const char* out_filename, unsigned int num_threads_): in_filename(in_filename), out_filename(out_filename) {
    num_threads = num_threads_ ? num_threads_ : std::thread::hardware_concurrency();
    spdlog::info("Thread number: {}", num_threads);
};

void WordsCountServiceMultithreadImpl::process_chunk(char* data, size_t start, size_t end, std::unordered_map<std::string, int>& word_counts) {
    bool in_word = false;
    size_t word_start = start;

    for (size_t i = start; i < end; ++i) {
        data[i] = std::tolower(data[i]);
        if (!in_word && !isSpace(data[i])) {
            word_start = i;
            in_word = true;
        } else if (in_word && isSpace(data[i])) {
            word_counts[std::string(data + word_start, i - word_start)]++;
            in_word = false;
        }
    }

    if (in_word) {
        word_counts[std::string(data + word_start, end - word_start)]++;
    }
}

int WordsCountServiceMultithreadImpl::count_words() {
    int fd = open(in_filename, O_RDWR);
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

    void* mapped = mmap(nullptr, file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
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
            while (end < file_size && !isSpace(data[end])) ++end;
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
            words_map[k] += v;
        }
    }

    if (munmap(mapped, file_size) == -1) {
        spdlog::error("Error un-mmapping");
        return 1;
    }
    return 0;
}

void WordsCountServiceMultithreadImpl::write_result() {
    int fd = open(out_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        spdlog::error("Failed to opent write file");
        return;
    }

    std::vector<std::pair<std::string, uint32_t>> temporary_vector(words_map.begin(), words_map.end());
    std::sort(temporary_vector.begin(), temporary_vector.end(),
        [](std::pair<std::string, uint32_t>& a, std::pair<std::string, uint32_t>& b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });
    std::string serialized_data;
    serialized_data.reserve(result_serialized_file_size);
    for (const auto& pair : temporary_vector) {
        serialized_data += std::to_string(pair.second) + " " + pair.first + "\n";
    }

    size_t data_size = serialized_data.size();
    if (ftruncate(fd, data_size) == -1) {
        spdlog::error("ftruncate, write to file error");
        close(fd);
        return;
    }

    void* map_ptr = mmap(nullptr, data_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (map_ptr == MAP_FAILED) {
        spdlog::error("Failed mmap to output file");
        close(fd);
        return;
    }

    std::memcpy(map_ptr, serialized_data.c_str(), data_size);

    if (msync(map_ptr, data_size, MS_SYNC) == -1) {
        spdlog::error("Failed to msync");
    }

    if (munmap(map_ptr, data_size) == -1) {
        spdlog::error("Failed to munmap");
    }

    close(fd);
}

WordsCountServiceMultithreadImpl::~WordsCountServiceMultithreadImpl() {}

} // namespace wordscount;
