#include <limits.h>
#include <string>
#include "gtest/gtest.h"



#define protected public
#define private public
#include "RecipeStep.h"
#undef protected
#undef private

#include <sstream>

class RecipeStepTest : public ::testing::Test {
 protected:
  RecipeStep* rs;
  std::basic_streambuf<char>* old_buf;
  std::stringstream ss;
  


  virtual void SetUp() {
      old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
      rs = new RecipeStep();
  }

  virtual void TearDown() {
    std::cout.rdbuf(old_buf); // redirect cout back to standard cout
    delete rs;
  }

};

TEST_F(RecipeStepTest,getReturnMZutatFirst){
    ss.clear();
    EXPECT_EQ("", rs->getZutat());
}

TEST_F(RecipeStepTest,getReturnMMengeFirst){
    EXPECT_FLOAT_EQ(0, rs->getMenge());
}

TEST_F(RecipeStepTest,getReturnMZutat){
    std::string zutat = "Orange";
    rs->setZutat(zutat);
    EXPECT_EQ(zutat, rs->getZutat());
}

TEST_F(RecipeStepTest,getReturnMMenge){
    float menge = 5;
    rs->setMenge(menge);
    EXPECT_FLOAT_EQ(menge, rs->getMenge());
}
