#include <unordered_map>

#include "WordsCountService/WordsCountService.hh"

namespace wordscount {

class WordsCountServiceFasterImpl : public WordsCountService {

public:
    WordsCountServiceFasterImpl(const char* in_filename, const char* out_filename);

    int count_words() override;

    void write_result() override;

    ~WordsCountServiceFasterImpl() override;

private:
    const char* in_filename;
    const char* out_filename;
    std::unordered_map<std::string, uint32_t> words_map;
    uint64_t result_serialized_file_size = 0;
    const uint64_t SERIALIZED_STR_OVERHEAD = 12;
};

} // namespace wordscount;