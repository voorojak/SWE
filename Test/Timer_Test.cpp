#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "Timer.h"
#undef protected
#undef private


#include <sstream>

class TimerTest : public ::testing::Test {
protected:
    Timer* timer;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        timer = new Timer();
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete timer;

    }
};

TEST_F(TimerTest, testSetTubro) {
    timer->setTurbo(123);
    EXPECT_EQ(123, timer->turbo);
}



