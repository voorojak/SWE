#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "Doser.h"
#include "Scale.h"
#undef protected
#undef private


#include <sstream>

class DoserTest : public ::testing::Test {
protected:
    Doser* doser;
    Scale* scale;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        scale = new Scale();
        doser = new Doser(1, 250, "TestZutat", scale);
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete doser;
        delete scale;
    }
};

TEST_F(DoserTest, DispenseTestZutat) {
    ss.clear();
    doser->execute(1);
    EXPECT_EQ(1, scale->getDelta());
}

TEST_F(DoserTest, GetThroughput) {
    EXPECT_EQ(1, doser->getThroughput());
}

TEST_F(DoserTest, checkValidationOfFillingLevel) {
    doser->execute(1);
    EXPECT_EQ(doser->fillingLevel_, 999);
    doser->fillingLevel_ = 1;
    doser->execute(5);
    EXPECT_EQ(doser->fillingLevel_, 0); //Check: cannot goes minus
}

TEST_F(DoserTest, checkFillingModification) {
    EXPECT_EQ(1000, doser->fillingLevel_);
    doser->addFillingCapacity();
    EXPECT_EQ(2000, doser->fillingLevel_);
    doser->execute(1);
    EXPECT_EQ(1999, doser->fillingLevel_);
}

//still here cuz test coverage
TEST_F(DoserTest, testInsufficientIngredient) {
    EXPECT_TRUE(doser->execute(1100));
}