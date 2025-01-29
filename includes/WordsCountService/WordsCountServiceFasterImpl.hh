#include <unordered_map>

#include "WordsCountService/WordsCountService.hh"

namespace wordscount {

class WordsCountServiceFasterImpl : public WordsCountService {

public:
    WordsCountServiceFasterImpl(const char* inFilename, const char* outFilename);

    int count_words() override;

    void write_result() override;

    ~WordsCountServiceFasterImpl() override;

private:
    const char* inFilename;
    const char* outFilename;
    std::unordered_map<std::string, uint32_t> wordsMap;
    uint64_t resultSerializedFileSize = 0;
    const uint64_t SERIALIZED_STR_OVERHEAD = 12;
};

} // namespace wordscount;