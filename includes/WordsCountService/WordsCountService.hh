#pragma once

namespace wordscount {

class WordsCountService {
public:
    virtual int count_words() = 0;
    virtual void write_result() = 0;
    virtual ~WordsCountService() = default;
};

} // namespace wordscount;