#include <limits.h>
#include "gtest/gtest.h"
#include <sstream>

#define protected public
#define private public
#include "Recipe.h"
#include "RecipeBook.h"
#include "DeviceManager.h"
#include "CocktailMixer.h"

#undef protected
#undef private

class CocktailMixerTest : public ::testing::Test {
 protected:
     CocktailMixer* cm;
     DeviceManager* dm;
     IngredientManager* im;
     std::basic_streambuf<char>* old_buf;
     std::stringstream ss;
     Recipe* r ;
     

  virtual void SetUp()
    {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        im = new IngredientManager("zutaten.txt", false);
        dm = new DeviceManager(im);
        cm = new CocktailMixer(dm);
        r = new Recipe();
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete dm;
        delete im;
        delete cm;
        delete r;
    }
};

TEST_F(CocktailMixerTest,testingCocktailMix){
    r->setName("TestRezept");
    r->appendStep("Limettenstuecke", 1);
    EXPECT_EQ(true, cm->mixCocktail(r));
}

TEST_F(CocktailMixerTest,getReturningRecipes){
    EXPECT_EQ(0,r->getNoOfRecipeSteps());
}