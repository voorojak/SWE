#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "Recipe.h"
#undef protected
#undef private

#include<sstream>

class RecipeTest  : public ::testing::Test {
    protected:
        Recipe* r;
        std::basic_streambuf<char>* old_buf;
        std::stringstream ss;
        
        virtual void SetUp() {
            old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
            r = new Recipe();
        }
        
        virtual void TearDown() {
            std::cout.rdbuf(old_buf); // redirect cout back to standard cout
            delete r;
        }
};

TEST_F(RecipeTest,browsing) {
    ss.str("");
    ss.clear();
    std::string browseOutput;
    r->setName("Rezept1"); //Rezeptname
    r->appendStep("Orange", 2); //Zutat und Menge hinzufügen
    r->browse();    //Alle Zutaten vom Rezept ausgeben
    browseOutput = ss.str(); //ss in string speichern
    EXPECT_EQ("Rezept1: Orange", browseOutput.substr(0, 20));
}

TEST_F(RecipeTest, getReturnRecipeName) {
    std::string name = "Rezept";
    r->setName(name);
    EXPECT_EQ("Rezept", r->getName());
}

TEST_F(RecipeTest, getAmountOfDifferenIrgredientFirst) {
     EXPECT_EQ(0, r->getNoOfRecipeSteps());
}

TEST_F(RecipeTest, getAmountOfDifferenIrgredientAfter) {
    std::string name = "Rezept";
    float amount = 2;
    r->appendStep(name, amount);
    EXPECT_EQ(1, r->getNoOfRecipeSteps());
}
