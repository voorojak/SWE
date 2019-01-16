#include <limits.h>
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "DeviceManager.h"
#include "Dispenser.h"
#include "Scale.h"
#include "IngredientManager.h"
#undef protected
#undef private

#include <sstream>

class DeviceManagerTest : public ::testing::Test {
protected:
    IngredientManager* availiableIngredients;
    DeviceManager* deviceManager;
    std::basic_streambuf<char>* old_buf;
    std::stringstream ss;

    virtual void SetUp() {
        old_buf = std::cout.rdbuf(ss.rdbuf()); // redirect cout to stream for testing
        availiableIngredients = new IngredientManager("zutaten.txt", false);
        deviceManager = new DeviceManager(availiableIngredients);
    }

    virtual void TearDown() {
        std::cout.rdbuf(old_buf); // redirect cout to stream for testing
        delete deviceManager;
        delete availiableIngredients;
    }
};

TEST_F(DeviceManagerTest, testDeviceAmount) {
    EXPECT_NE(0, deviceManager->devices_->size());
}

TEST_F(DeviceManagerTest, testExecuteRecipeStepCaseIngredient) {
    ss.str("");
    ss.clear();
    deviceManager->executeRecipeStep("Wodka", 1);
    std::string executeOutput = ss.str();
    std::string expectedOutput = "Es wurden 1g Wodka abgefuellt";
    std::size_t fpos = executeOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(DeviceManagerTest, testExecuteRecipeStepCaseNonExistentIngredient) {
        EXPECT_THROW({deviceManager->executeRecipeStep("NonExistantIngredient", 1);}, std::out_of_range);
}

TEST_F(DeviceManagerTest, testExecuteRecipeStepCaseLimette) {
    ss.str("");
    ss.clear();
    deviceManager->executeRecipeStep("Limettenstuecke", 1); // 1 -> 1x "*" and 10gr as output
    std::string executeOutput = ss.str();
    std::string expectedOutput = "Es wurden 10g Limettenstuecke abgefuellt";
    std::size_t fpos = executeOutput.find(expectedOutput);
    EXPECT_TRUE(fpos != std::string::npos);
}

TEST_F(DeviceManagerTest, testDispenseAmount) {
    deviceManager->scale_->changeWeight(50);
    deviceManager->dispense(25);
    EXPECT_EQ(25, deviceManager->scale_->getWeight());
    deviceManager->dispense(5);
    EXPECT_EQ(0, deviceManager->scale_->getWeight());
}

TEST_F(DeviceManagerTest, testDispenseAll) {
    deviceManager->scale_->changeWeight(55);
    deviceManager->dispenseAll();
    EXPECT_EQ(0, deviceManager->scale_->getWeight());
}

TEST_F(DeviceManagerTest, testCleanAll) {
    EXPECT_NO_THROW({deviceManager->cleanAll();});
}

TEST_F(DeviceManagerTest, testHandleIngredientNewName) {
    deviceManager->usualIngredientCounter_--;
    deviceManager->handleInsertOfNewDevice("testIngredient");
    EXPECT_NE(deviceManager->devices_->find("testIngredient"), deviceManager->devices_->end()); ///x.end() != x.find(y) -> availiable
    EXPECT_EQ(deviceManager->devices_->find("notAvailiableTestIngredient"), deviceManager->devices_->end()); //x.end() == x.find(y) -> not availiable with index y
}

TEST_F(DeviceManagerTest, testHandleIngredientNameByOutput) {
    std::string executeOutput;
    std::string expectedOutput;
    
    ss.str("");
    ss.clear();
    deviceManager->usualIngredientCounter_--;
    deviceManager->handleInsertOfNewDevice("testIngredient");
    deviceManager->devices_->at("testIngredient")->status();
    executeOutput = ss.str();
    expectedOutput = "testIngredient: 1000\n";
    EXPECT_EQ(expectedOutput, executeOutput);
}

TEST_F(DeviceManagerTest, testHandleDoubleIngredient) {
    std::string executeOutput;
    std::string expectedOutput;
    
    ss.str("");
    ss.clear();
    deviceManager->usualIngredientCounter_ -= 2;
    deviceManager->handleInsertOfNewDevice("testIngredient");
    deviceManager->handleInsertOfKnownDevice("testIngredient");
    deviceManager->devices_->at("testIngredient")->status();
    executeOutput = ss.str();
    expectedOutput = "testIngredient: 2000\n";
    EXPECT_EQ(expectedOutput, executeOutput);
}

TEST_F(DeviceManagerTest, testHandleDoubleIngredientErrorIce) {
    ss.str("");
    ss.clear();
    std::stringstream expectedStream;
    expectedStream << std::endl << std::endl << "Nicht genuegend freie Dosierertypen vorhanden fuer: " << "Eis" << std::endl
                        << "Bitte korrigieren Sie die Zutatendatei und starten Sie das System neu!" << std::endl;
    EXPECT_EXIT({deviceManager->handleInsertOfKnownDevice("Eis");}, ::testing::ExitedWithCode(0), expectedStream.str());
}

TEST_F(DeviceManagerTest, testHandleDoubleIngredientErrorLime) {
    ss.str("");
    ss.clear();
    std::stringstream expectedStream;
    expectedStream << std::endl << std::endl << "Nicht genuegend freie Dosierertypen vorhanden fuer: " << "Limettenstuecke" << std::endl
                        << "Bitte korrigieren Sie die Zutatendatei und starten Sie das System neu!" << std::endl;
    EXPECT_EXIT({deviceManager->handleInsertOfKnownDevice("Limettenstuecke");}, ::testing::ExitedWithCode(0), expectedStream.str());
}

TEST_F(DeviceManagerTest, testHandleDoubleIngredientError) {
    ss.str("");
    ss.clear();
    std::stringstream expectedStream;
    deviceManager->usualIngredientCounter_ -= 1;
    deviceManager->handleInsertOfNewDevice("testIngredient");
    expectedStream << std::endl << std::endl << "Nicht genuegend freie Dosierertypen vorhanden fuer: " << "testIngredient" << std::endl
                        << "Bitte korrigieren Sie die Zutatendatei und starten Sie das System neu!" << std::endl;
    EXPECT_EXIT({deviceManager->handleInsertOfKnownDevice("testIngredient");}, ::testing::ExitedWithCode(0), expectedStream.str());
}

TEST_F(DeviceManagerTest, testCheckDoserComparison) {
    //Eis-Standardfuellung: 1000
    EXPECT_TRUE(deviceManager->isAmountEnough("Eis", 999));
    EXPECT_TRUE(deviceManager->isAmountEnough("Eis", 1000));
    EXPECT_FALSE(deviceManager->isAmountEnough("Eis", 1001));
}