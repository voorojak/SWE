#include <limits.h>
#include <string>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "IngredientManager.h"
#undef protected
#undef private


#include <sstream>

class IngredientManagerTest : public ::testing::Test {
protected:
    IngredientManager* ingredientManager;
    IngredientManager* ingredientManager_copy;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        ingredientManager = new IngredientManager("zutaten.txt", false);
        ingredientManager_copy = new IngredientManager(*ingredientManager);
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        std::cout.rdbuf(old_buf); // redirect cout back to standard cout
        delete ingredientManager;
        delete ingredientManager_copy;
    }
};

TEST_F(IngredientManagerTest, getReturnZutatAtPosition) {
    ingredientManager->ingredients->clear();
    ingredientManager->ingredients->push_back("Limettenstuecke");
    EXPECT_EQ("Limettenstuecke", ingredientManager->getIngredient(0));
}

TEST_F(IngredientManagerTest, browsing) {
    ss.str("");
    ss.clear();
    ingredientManager->browse();
    std::string browseOutput = ss.str();
    std::string expectedOutput = "Schuetteln\n**********************************************************\n";
    std::size_t fpos = browseOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(IngredientManagerTest, getAnzahlVorhandeneZutaten) {
    EXPECT_EQ(16, ingredientManager->getIngredientCount());
}

TEST_F(IngredientManagerTest, getAnzahlVorhandeneZutatenWithCopyConstructor) {
    EXPECT_EQ(16, ingredientManager_copy->getIngredientCount());
}

TEST_F(IngredientManagerTest, FileZutatenDotTxtIsAvailable) {
    // Test redirects the standard cout to another stream (ss)
    // this stream can be read and compared
    // after the test the normal cout is activated again

    ss.clear();
    ingredientManager->readIngredientsFromFile("zutaten.txt");
    std::string testOutput = ss.str();
    std::string expectedOutput = "Oeffne Zutatendatei";
    std::size_t fpos = testOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(IngredientManagerTest, FileZutatenDotTxtIsNotAvailable) {
    // Test asserts that an exception is thrown and that the type of the exception is the one expected
    //https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
    EXPECT_THROW({
        try {
            ingredientManager->readIngredientsFromFile("xxxx.txt");
        }        catch (std::string e) {
            std::cout << e << std::endl;
                    EXPECT_EQ("File not found", e.substr(0, 14));
                    throw;
        }
    }, std::string);
}

