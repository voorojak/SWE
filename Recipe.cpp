//Comments by Vedat Oeskan
#include <algorithm>
#include <iostream>

#include "Recipe.h"

Recipe::Recipe(void) : availiable_(false) {
    mixable_ = true;
    recipeCraftingSteps_.clear();
     recipeName_ = "";
}

Recipe::~Recipe() {
}

int Recipe::getNoOfRecipeSteps() {
    return (recipeCraftingSteps_.size());
}

RecipeStep * Recipe::getRecipeStep(unsigned int i) {
    if (i > recipeCraftingSteps_.size()) return NULL;
    else {
        std::list<RecipeStep*>::iterator iteratorRecipeStep; // Iterator
        advance(iteratorRecipeStep = recipeCraftingSteps_.begin(), i); // iteratorRecipeStep zeigt jetzt auf das i-te Element
        return (*iteratorRecipeStep); // Adresse vom Wert von iteratorRecipeStep -> also den Pointer auf den der Iterator zeigt
    }
}

std::string Recipe::getName(void) const {
    return  recipeName_;
}

void Recipe::setName(const std::string& recipeName) {
    this->recipeName_ = recipeName;
}

void Recipe::browse() {
    std::cout <<  recipeName_ << ": ";
    for (int i = 0; i< this->getNoOfRecipeSteps(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << getRecipeStep(i)->getZutat();
    }
}

void Recipe::appendStep(std::string recipeName, float ingredientAmount) {
    RecipeStep* newRecipeStep;
    newRecipeStep = new RecipeStep;
    newRecipeStep->setZutat(recipeName);
    newRecipeStep->setMenge(ingredientAmount);
    recipeCraftingSteps_.push_back(newRecipeStep);
}

bool Recipe::isAvailable() const {
    return availiable_;
}

void Recipe::setAvailable(bool availiable) {
    availiable_ = availiable;
}

bool Recipe::isMixable() const {
    return mixable_;
}

void Recipe::setMixable(bool mixable) {
    mixable_ = mixable;
}
