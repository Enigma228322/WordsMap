#include "spdlog/spdlog.h"
#include "WordsCountService/WordsCountService.hh"
#include "WordsCountService/WordsCountServiceImpl.hh"

int main(int argc, char** argv) {
    if (argc < 2) {
      spdlog::error("Pass in.txt and out.txt");
      return 1;
    }
    std::unique_ptr<wordscount::WordsCountService> wordsCountServiceInstance =
      std::make_unique<wordscount::WordsCountServiceImpl>(argv[1], argv[2]);
    spdlog::info("Created WordsCountService");
    wordsCountServiceInstance->count_words();
    spdlog::info("Calculated words map");
    wordsCountServiceInstance->write_result();
    spdlog::info("Wrote the result to a file");
    return 0;
}
