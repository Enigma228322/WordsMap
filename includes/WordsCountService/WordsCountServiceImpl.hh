#include <fstream>
#include <string>
#include <unordered_map>

#include "WordsCountService/WordsCountService.hh"

namespace wordscount {

class WordsCountServiceImpl : public WordsCountService {

const int MAX_UNIQUE_WORDS = 1e3;

public:
    WordsCountServiceImpl(const char* inFilename, const char* outFilename);

    int count_words() override;

    void write_result() override;

    ~WordsCountServiceImpl() override;

private:
    std::ifstream in;
    std::ofstream out;
    std::unordered_map<std::string, uint32_t> wordsMap;
    std::string buffer;
};

} // namespace wordscount;