#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "Dispenser.h"
#include "Scale.h"
#undef protected
#undef private


#include <sstream>

class DispenserTest : public ::testing::Test {
protected:
    Dispenser* dispenser;
    Scale* scale;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        scale = new Scale();
        scale->changeWeight(10);
        dispenser = new Dispenser(1, 250, scale);
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete dispenser;
        delete scale;
    }
};

TEST_F(DispenserTest, DispenseCocktail) {
    ss.clear();
    dispenser->execute(1);
    EXPECT_EQ(9, scale->getWeight());
}
