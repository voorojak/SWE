#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "Shaker.h"
#include "Timer.h"
#undef protected
#undef private


#include <sstream>

class ShakerTest : public ::testing::Test {
protected:
    Shaker* shaker;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        shaker = new Shaker();
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete shaker;
    }
};

TEST_F(ShakerTest, testEquality) {
    ss.str("");
    ss.clear();
    shaker->execute(1);
    std::string executeOutput = ss.str();
    std::string expectedOutput = "\n";
    EXPECT_TRUE(executeOutput.size() > 0);
    EXPECT_EQ(expectedOutput, executeOutput.substr(executeOutput.size() - 1, 1)); //Printing "\n" after using timer
}