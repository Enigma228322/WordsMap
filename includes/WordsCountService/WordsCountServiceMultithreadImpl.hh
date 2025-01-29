#include <unordered_map>
#include <thread>

#include "WordsCountService/WordsCountService.hh"

namespace wordscount {

class WordsCountServiceMultithreadImpl : public WordsCountService {

public:
    WordsCountServiceMultithreadImpl(const char* in_filename, const char* out_filename, unsigned int num_threads_ = 0);

    int count_words() override;

    void write_result() override;

    ~WordsCountServiceMultithreadImpl() override;

private:
    const char* in_filename;
    const char* out_filename;
    std::unordered_map<std::string, uint32_t> words_map;
    unsigned int num_threads;
    uint64_t result_serialized_file_size = 0;
    const uint64_t SERIALIZED_STR_OVERHEAD = 12;

    void process_chunk(char* data, size_t start, size_t end, std::unordered_map<std::string, int>& word_counts);
};

} // namespace wordscount;