#include "spdlog/spdlog.h"
#include <filesystem>

#include "WordsCountService/WordsCountServiceImpl.hh"

namespace wordscount {

WordsCountServiceImpl::WordsCountServiceImpl(const char* inFilename, const char* outFilename):
in(std::ifstream(inFilename)), out(std::ofstream(outFilename)) {
    wordsMap.reserve(MAX_UNIQUE_WORDS);
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
            ++wordsMap[std::string(it - word_len, it)];
            word_len = 0;
        }
    }
    ++wordsMap[std::string(buffer.end() - word_len, buffer.end())];
    return 0;
}

void WordsCountServiceImpl::write_result() {
    std::vector<std::pair<std::string, uint32_t>> temporary_vector(wordsMap.begin(), wordsMap.end());
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
