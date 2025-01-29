#include "WordsCountService/WordsCountServiceImpl.hh"
#include "WordsCountService/WordsCountServiceFasterImpl.hh"
#include "WordsCountService/WordsCountServiceMultithreadImpl.hh"
#include <cstdio>

#include <gtest/gtest.h>
namespace {
class WordsCountServiceTest : public ::testing::Test{
public:
	const std::string IN_FILENAME = "in.txt";
	const std::string OUT_FILENAME = "out.txt";
	const std::string EXPECTED_RESULT = "9 asd\n9 bds\n4 fds\n2 fd\n";

protected:
    WordsCountServiceTest() {
    }

    virtual ~WordsCountServiceTest() {
    }

    virtual void SetUp() {
	/* prepare input text */
	std::ofstream out(IN_FILENAME);
	out << "bdS bdS bdS bdS BDS asd asd asd asd fds fd fds asd asd bdS asd asd fds fd fds ASD bdS bdS bdS";
    }

    virtual void TearDown() {
		std::remove(IN_FILENAME.c_str());
		std::remove(OUT_FILENAME.c_str());
    }
};

TEST_F(WordsCountServiceTest, count_words)
{
	wordscount::WordsCountServiceImpl wordsCountService(
		WordsCountServiceTest::IN_FILENAME.c_str(),
		WordsCountServiceTest::OUT_FILENAME.c_str()
	);
	wordsCountService.count_words();
	wordsCountService.write_result();

	std::ifstream in(WordsCountServiceTest::OUT_FILENAME);
	std::string result_string;
	result_string.reserve(WordsCountServiceTest::EXPECTED_RESULT.size());
	{
		std::ifstream in(WordsCountServiceTest::OUT_FILENAME);
		while (!in.eof()) {
			std::string word;
			std::string num;
			in >> word >> num;
			if (word.size() > 0 || num.size() > 0) {
				result_string += word + " " + num + '\n';
			}
		}
	}

	EXPECT_EQ(result_string, WordsCountServiceTest::EXPECTED_RESULT);
}

TEST_F(WordsCountServiceTest, count_words_faster)
{
	wordscount::WordsCountServiceFasterImpl wordsCountService(
		WordsCountServiceTest::IN_FILENAME.c_str(),
		WordsCountServiceTest::OUT_FILENAME.c_str()
	);
	wordsCountService.count_words();
	wordsCountService.write_result();

	std::ifstream in(WordsCountServiceTest::OUT_FILENAME);
	std::string result_string;
	result_string.reserve(WordsCountServiceTest::EXPECTED_RESULT.size());
	{
		std::ifstream in(WordsCountServiceTest::OUT_FILENAME);
		while (!in.eof()) {
			std::string word;
			std::string num;
			in >> word >> num;
			if (word.size() > 0 || num.size() > 0) {
				result_string += word + " " + num + '\n';
			}
		}
	}

	EXPECT_EQ(result_string, WordsCountServiceTest::EXPECTED_RESULT);
}

TEST_F(WordsCountServiceTest, count_words_multithreaded)
{
	wordscount::WordsCountServiceMultithreadImpl wordsCountService(
		WordsCountServiceTest::IN_FILENAME.c_str(),
		WordsCountServiceTest::OUT_FILENAME.c_str()
	);
	wordsCountService.count_words();
	wordsCountService.write_result();

	std::ifstream in(WordsCountServiceTest::OUT_FILENAME);
	std::string result_string;
	result_string.reserve(WordsCountServiceTest::EXPECTED_RESULT.size());
	{
		std::ifstream in(WordsCountServiceTest::OUT_FILENAME);
		while (!in.eof()) {
			std::string word;
			std::string num;
			in >> word >> num;
			if (word.size() > 0 || num.size() > 0) {
				result_string += word + " " + num + '\n';
			}
		}
	}

	EXPECT_EQ(result_string, WordsCountServiceTest::EXPECTED_RESULT);
}
}; // namespace

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
