#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "RecipeBook.h"
#include "IngredientManager.h"
#undef protected
#undef private


#include <sstream>

class RecipeBookTest : public ::testing::Test {
protected:
    RecipeBook* recipeBook;
    RecipeBook* recipeBookFail;
    IngredientManager* ingredientManager;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        ingredientManager = new IngredientManager("zutaten.txt", false);
        recipeBook = new RecipeBook(ingredientManager, "rezepte.csv", false); // Empty constructor for testing
        recipeBookFail = new RecipeBook(ingredientManager, "impossible.csv", false); // Empty constructor for testing
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete recipeBook;
        delete ingredientManager;
    }
};

TEST_F(RecipeBookTest, testBrowseAllRecipes) {
    ss.str("");
    ss.clear();
    recipeBook->browseAllRecipes();
    std::string browseOutput = ss.str();
    std::string expectedOutput = "Es gibt 8 Cocktails";
    std::size_t fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(RecipeBookTest, testFileIsFound) {
    EXPECT_EQ(recipeBook->getNumberOfRecipes(), 8);
}

TEST_F(RecipeBookTest, testGetNumberOfMixableRecipes) {
    EXPECT_EQ(recipeBook->getNumberOfAvailiableRecipes(), 6);

}

TEST_F(RecipeBookTest, testFileNotFound) {
    EXPECT_EQ(recipeBookFail->getNumberOfRecipes(), 8);
}

TEST_F(RecipeBookTest, testBrowseMixableRecipes) {
    ss.str("");
    ss.clear();
    recipeBook->browseAvailiableRecipes();
    std::string browseOutput = ss.str();
    std::string expectedOutput = "Es gibt 6 Cocktails";
    std::size_t fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(RecipeBookTest, testParseLine) {
    Recipe* expectedRecipe = new Recipe();
    expectedRecipe->setName("TestRecipe");
    expectedRecipe->appendStep("TestIngredient1", 1);
    expectedRecipe->appendStep("TestIngredient2", 2);
    std::string testLine = "TestRecipe;TestIngredient1;1;TestIngredient2;2";
    recipeBook->parseLine(testLine);
    Recipe* outputRecipe = recipeBook->recipes_.back();
    EXPECT_EQ(expectedRecipe->getName(), outputRecipe->getName());
    for (int i = 0; i < expectedRecipe->recipeCraftingSteps_.size(); ++i) {
        EXPECT_EQ(expectedRecipe->getRecipeStep(i)->getZutat(), outputRecipe->getRecipeStep(i)->getZutat());
        EXPECT_EQ(expectedRecipe->getRecipeStep(i)->getMenge(), outputRecipe->getRecipeStep(i)->getMenge());
    }
}

TEST_F(RecipeBookTest, testGetRecipe) {
    Recipe* recipe = new Recipe();
    recipeBook->recipes_.push_back(recipe);
    EXPECT_EQ(recipe, recipeBook->getRecipe(recipeBook->recipes_.size() - 1));
}

TEST_F(RecipeBookTest, testFilterRecipes) {
    Recipe* recipe = new Recipe();
    recipe->setName("TestRecipe");
    recipe->appendStep("ImpossibleIngredient", 1);
    recipeBook->recipes_.push_back(recipe);
    recipeBook->filterRecipes();
    EXPECT_FALSE(recipeBook->recipes_.back()->isAvailable());
}

TEST_F(RecipeBookTest, testStaticRecipeNumbers) {

    ss.str("");
    ss.clear();
    recipeBook->browseAvailiableRecipes();
    std::string browseOutput = ss.str();

    std::string expectedOutput = "Es gibt 6 Cocktails";
    std::size_t fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);

    expectedOutput = "1. Caipirinha: Limettenstuecke, Zucker, Stampfen, Eis, Cachaca, Mischen";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);

    expectedOutput = "5. Caipiroska: Limettenstuecke, Zucker, Stampfen, Eis, Wodka, Mischen";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);

    expectedOutput = "8. Martini James B: Gin, Wodka, Noilly Prat, Schuetteln";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);


    // Clear and insert only ingredients for Caipirinha, Caipiroska and Martini James B
    recipeBook->ingredientManager_->ingredients->clear();
    recipeBook->ingredientManager_->insertDeviceAbilities();

    recipeBook->ingredientManager_->ingredients->push_back("Limettenstuecke");
    recipeBook->ingredientManager_->ingredients->push_back("Zucker");
    recipeBook->ingredientManager_->ingredients->push_back("Stampfen");
    recipeBook->ingredientManager_->ingredients->push_back("Eis");
    recipeBook->ingredientManager_->ingredients->push_back("Cachaca");

    recipeBook->ingredientManager_->ingredients->push_back("Gin");
    recipeBook->ingredientManager_->ingredients->push_back("Wodka");
    recipeBook->ingredientManager_->ingredients->push_back("Noilly Prat");

    ss.str("");
    ss.clear();

    recipeBook->filterRecipes();
    recipeBook->browseAvailiableRecipes();

    browseOutput = ss.str();

    expectedOutput = "Es gibt 3 Cocktails";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);

    expectedOutput = "1. Caipirinha: Limettenstuecke, Zucker, Stampfen, Eis, Cachaca, Mischen";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);

    expectedOutput = "5. Caipiroska: Limettenstuecke, Zucker, Stampfen, Eis, Wodka, Mischen";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);

    expectedOutput = "8. Martini James B: Gin, Wodka, Noilly Prat, Schuetteln";
    fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}
