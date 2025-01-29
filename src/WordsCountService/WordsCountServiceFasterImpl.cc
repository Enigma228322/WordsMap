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

#include "WordsCountService/WordsCountServiceFasterImpl.hh"

namespace wordscount {

WordsCountServiceFasterImpl::WordsCountServiceFasterImpl(const char* inFilename, const char* outFilename): inFilename(inFilename), outFilename(outFilename) {
};

int WordsCountServiceFasterImpl::count_words() {
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
    bool in_word = false;
    size_t start = 0;

    for (size_t i = 0; i < file_size; ++i) {
        if (!in_word && !std::isspace(data[i])) {
            start = i;
            in_word = true;
        } else if (in_word && std::isspace(data[i])) {
            std::string word = std::string(data + start, i - start);
            std::transform(word.begin(), word.end(), word.begin(),[](unsigned char letter){ return std::tolower(letter); });
            wordsMap[word]++;
            in_word = false;
            resultSerializedFileSize += (i - start) + SERIALIZED_STR_OVERHEAD;
        }
    }

    /* Handle the last word if the file ends without whitespace */
    if (in_word) {
        std::string word = std::string(data + start, file_size - start);
        std::transform(word.begin(), word.end(), word.begin(),[](unsigned char letter){ return std::tolower(letter); });
        wordsMap[word]++;
    }
    return 0;
}

void WordsCountServiceFasterImpl::write_result() {
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

WordsCountServiceFasterImpl::~WordsCountServiceFasterImpl() {}

} // namespace wordscount;
