#include <limits.h>

#include "gtest/gtest.h"



#define protected public

#define private public

#include "Scale.h"

#undef protected

#undef private

class ScaleTest : public ::testing::Test {
protected:
    Scale* w;

    virtual void SetUp() {
        w = new Scale();
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        delete w;
    }
};

TEST_F(ScaleTest, getWeightOfIngredientsReturnsValueOfAttribute) {
    int ingredient_weight = w->weight;
    EXPECT_EQ(ingredient_weight, w->getWeight());
}

TEST_F(ScaleTest, getDeltaWeightOfIngredientsReturnsValueOfAttribute) {
    int ingredient_deltaweight = w->deltaweight;
    EXPECT_EQ(ingredient_deltaweight, w->getDelta());
}

TEST_F(ScaleTest, getTaraReturnsZero) {
    int ingredient_taraweight = 0;
    EXPECT_EQ(ingredient_taraweight, w->tara());
}

