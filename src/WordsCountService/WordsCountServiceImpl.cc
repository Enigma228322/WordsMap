#include "spdlog/spdlog.h"
#include <filesystem>

#include "WordsCountService/WordsCountServiceImpl.hh"

namespace wordscount {

WordsCountServiceImpl::WordsCountServiceImpl(const char* in_filename, const char* out_filename):
in(std::ifstream(in_filename)), out(std::ofstream(out_filename)) {
    words_map.reserve(MAX_UNIQUE_WORDS);
};

int WordsCountServiceImpl::count_words() {
    if (!in) {
        spdlog::error("Unable to open input file.");
        return 1;
    }
    buffer.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    uint32_t word_len = 0;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        *it = std::tolower(*it);
        if (*it != ' ') ++word_len;
        else {
            ++words_map[std::string(it - word_len, it)];
            word_len = 0;
        }
    }
    ++words_map[std::string(buffer.end() - word_len, buffer.end())];
    return 0;
}

void WordsCountServiceImpl::write_result() {
    std::vector<std::pair<std::string, uint32_t>> temporary_vector(words_map.begin(), words_map.end());
    std::sort(temporary_vector.begin(), temporary_vector.end(), [](std::pair<std::string, uint32_t>& a, std::pair<std::string, uint32_t>& b) {
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });
    for (const auto& [k, v] : temporary_vector) {
        out << k << ' ' << v << '\n';
    }
    out.close();
}

WordsCountServiceImpl::~WordsCountServiceImpl() {}

} // namespace wordscount;
