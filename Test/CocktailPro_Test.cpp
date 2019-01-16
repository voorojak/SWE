#include <limits.h>
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "CocktailPro.h"
#include "RecipeBook.h"
#undef protected
#undef private

#include <sstream>

class CocktailProTest : public ::testing::Test {
protected:
    CocktailPro* cocktailPro;
    std::basic_streambuf<char>* old_buf;
    std::stringstream outSS;
    
    virtual void SetUp() {
        char* testArgs[5];
        testArgs[0] = (char*)"CocktailPro\0";
        testArgs[1] = (char*)"-DEMO\0";
        testArgs[2] = (char*)"-TEST\0";
        testArgs[3] = (char*)"-TURBO\0";
        testArgs[4] = NULL;
        old_buf = std::cout.rdbuf(outSS.rdbuf()); // redirect cout to stream for testing  
        cocktailPro = new CocktailPro(4,  testArgs);
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout to stream for testing
        delete cocktailPro;
    }
};

TEST_F(CocktailProTest, testStart) {
    outSS.str("");
    outSS.clear();
    cocktailPro->start();
    std::string executeOutput = outSS.str();
    std::string expectedOutputBegin = "Ich habe Ihre Bestellung: Caipirinha erhalten.";
    std::string expectedOutputEnd = "Ihr Cocktail hat ein Gesamtgewicht von 200g";
    size_t fpos = executeOutput.find(expectedOutputBegin);
    EXPECT_TRUE(fpos != std::string::npos);
    fpos = executeOutput.find(expectedOutputEnd);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(CocktailProTest, testWrongChoice) {
    outSS.str("");
    outSS.clear();
    cocktailPro->mixChoice(12345);
    std::string executeOutput = outSS.str();
    std::string expectedOutput = "Falsche Cocktailnummer!";
    size_t fpos = executeOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(CocktailProTest, testCopyConstructor) {
    outSS.str("");
    outSS.clear();
    CocktailPro cocktailPro2(*cocktailPro);
    std::string executeOutput = outSS.str();
    std::string expectedOutput = "haha no!1";
    size_t fpos = executeOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(CocktailProTest, notMixableAnymore) {
    //Mix DEATHWISH-Cocktail
    outSS.str("");
    outSS.clear();
    cocktailPro->mixChoice(9);
    std::string executeOutput = outSS.str();
    std::string expectedOutput = "Entleervorgang wurde beendet, bitte entnehmen Sie ihren Cocktail!";
    size_t fpos = executeOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
    
    //Mix DEATHWISH-Cocktail - should not be possible anymore (out of ingredients)
    outSS.str("");
    outSS.clear();
    cocktailPro->mixChoice(9);
    std::string executeOutput2 = outSS.str();
    std::string expectedOutput2 = "Falsche Cocktailnummer!";
    size_t fpos2 = executeOutput2.find(expectedOutput);
    EXPECT_TRUE(fpos2 != std::string::npos);
}