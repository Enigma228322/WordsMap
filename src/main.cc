#include "spdlog/spdlog.h"
#include "WordsCountService/WordsCountService.hh"
#include "WordsCountService/WordsCountServiceImpl.hh"
#include "WordsCountService/WordsCountServiceFasterImpl.hh"
#include "WordsCountService/WordsCountServiceMultithreadImpl.hh"

int main(int argc, char** argv) {
    if (argc < 2) {
      spdlog::error("Pass in.txt and out.txt");
      return 1;
    }

    std::unique_ptr<wordscount::WordsCountService> words_count_service_instance =
      std::make_unique<wordscount::WordsCountServiceMultithreadImpl>(argv[1], argv[2]);
    spdlog::info("Created WordsCountService");

    if (words_count_service_instance->count_words()) {
      return 1;
    }
    spdlog::info("Calculated words map");

    words_count_service_instance->write_result();
    spdlog::info("Wrote the result to a file");

    return 0;
}
