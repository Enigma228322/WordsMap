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

namespace {
bool isSpace(char c) {
    return c < 65 || (c > 90 && c < 97) || c > 122;
}
}; // namespace

namespace wordscount {

WordsCountServiceFasterImpl::WordsCountServiceFasterImpl(const char* in_filename, const char* out_filename): in_filename(in_filename), out_filename(out_filename) {
};

int WordsCountServiceFasterImpl::count_words() {
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
    bool in_word = false;
    size_t start = 0;

    for (size_t i = 0; i < file_size; ++i) {
        data[i] = std::tolower(data[i]);
        if (!in_word && !isSpace(data[i])) {
            start = i;
            in_word = true;
        } else if (in_word && isSpace(data[i])) {
            words_map[std::string(data + start, i - start)]++;
            in_word = false;
            result_serialized_file_size += (i - start) + SERIALIZED_STR_OVERHEAD;
        }
    }

    /* Handle the last word if the file ends without whitespace */
    if (in_word) {
        words_map[std::string(data + start, file_size - start)]++;
    }
    return 0;
}

void WordsCountServiceFasterImpl::write_result() {
    int fd = open(out_filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        spdlog::error("Failed to opent write file");
        return;
    }

    std::vector<std::pair<std::string, uint32_t>> temporary_vector(words_map.begin(), words_map.end());
    std::sort(temporary_vector.begin(), temporary_vector.end(), [](std::pair<std::string, uint32_t>& a, std::pair<std::string, uint32_t>& b) {
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

WordsCountServiceFasterImpl::~WordsCountServiceFasterImpl() {}

} // namespace wordscount;
