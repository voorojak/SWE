/**********************************************************************************/
/*                                 Definitionsmodul                               */
/**********************************************************************************/
/*
 * File       : RecipeBook.cpp
 *
 */

#include <algorithm>
#include "RecipeBook.h"
#include "CocktailMixer.h"

RecipeBook::RecipeBook(IngredientManager* ingredientManager, std::string file, bool isDemo) : isDemo_(isDemo), ingredientManager_(ingredientManager){
    recipes_.clear();
    loadRecipes(file);
    browseAllRecipes();
    filterRecipes();
}

RecipeBook::~RecipeBook() {
}

void RecipeBook::browseAllRecipes()  {
    browse(false);
}

void RecipeBook::browseAvailiableRecipes()  {
    browse(true);
}
    
void RecipeBook::browse(bool onlyAvailiable)  {
    std::cout << "*********************************************" << std::endl;
    std::cout << "Es gibt " << (onlyAvailiable ? getNumberOfAvailiableRecipes() : getNumberOfRecipes()) << " Cocktails" << std::endl;
    
    for (unsigned int i = 0; i < recipes_.size(); i++) {
        Recipe* r = recipes_[i];
        printRecipe(r, i, onlyAvailiable);
    }
    
    std::cout << "*********************************************" << std::endl;
}

void RecipeBook::printRecipe(Recipe* r, int i, bool onlyAvailiable) {
    if (!r->isMixable() && (!onlyAvailiable || r->isAvailable())) {
            std::cout << "(";
            std::cout << i + 1 << ". ";
            r->browse();
            std::cout << ")";
            std::cout << std::endl;
        } else if (!onlyAvailiable || r->isAvailable()) {
            std::cout << i + 1 << ". ";
            r->browse();
            std::cout << std::endl;
        }
}

void RecipeBook::loadRecipes(std::string file) {
    std::ifstream in;
    in.open(file.c_str(), std::ios::in);
    if (!in) {
        insertRecipes();
    } else {
        std::cout << "Rezepte aus " << file << " lesen..." << std::endl;
        std::string line;
        getline(in, line); // Discard first line
        while (getline(in, line)) {
            parseLine(line);
        }
        in.close();
    }
    if(isDemo_) {
        insertDemoRecipes();
    }
}

void RecipeBook::parseLine(std::string line) {
    std::istringstream inputString(line);
    std::string name;
    std::string ingredient;
    std::string amount;
    Recipe* r1 = new Recipe();
    getline(inputString, name, ';');
    r1->setName(name);
    while (getline(inputString, ingredient, ';')&& !ingredient.empty()) {
        getline(inputString, amount, ';');
        r1->appendStep(ingredient, std::atof(amount.c_str()));
    }
    this->recipes_.push_back(r1);
}

int RecipeBook::getNumberOfRecipes() {
    return recipes_.size();
}

int RecipeBook::getNumberOfAvailiableRecipes() {
    int count = 0;
    for (unsigned int i = 0; i < recipes_.size(); ++i) {
        if (recipes_[i]->isAvailable()) {
            ++count;
        }
    }
    return count;
}

Recipe* RecipeBook::getRecipe(unsigned int position) {
    return recipes_[position];
}

bool RecipeBook::isValidAndMixable(unsigned int position) {
    if (position < recipes_.size()) {
        if(getRecipe(position)->isAvailable() && getRecipe(position)->isMixable())
        return true;
    }
    return false;
}

void RecipeBook::filterRecipes() {
    for (unsigned int i = 0; i < recipes_.size(); ++i) {
        recipes_[i]->setAvailable(checkAmountOfIngredients(recipes_[i]));
    }
}

bool RecipeBook::checkAmountOfIngredients(Recipe* recipe) {
    for (int j = 0; j < recipe->getNoOfRecipeSteps(); j++) {
        std::string ingredientToSearch = recipe->getRecipeStep(j)->getZutat();
        if (!searchIngredient(ingredientToSearch)) {
            return false;
        }
    }
    return true;
}

bool RecipeBook::searchIngredient(std::string toSearch) {
    for (int k = 0; k < ingredientManager_->getIngredientCount(); k++) {
        if (ingredientManager_->getIngredient(k) == toSearch) {
            return true;
        }
    }
    return false;
}

void RecipeBook::insertRecipes() {
    Recipe1();
    Recipe2();
    Recipe3();
    Recipe4();
    Recipe5();
    Recipe6();
    Recipe7();
    Recipe8();
}

void RecipeBook::insertDemoRecipes() {
    Recipe9();
}

void RecipeBook::Recipe1() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Caipirinha");
    r1->appendStep("Limettenstuecke", 8);
    r1->appendStep("Zucker", 15);
    r1->appendStep("Stampfen", 20);
    r1->appendStep("Eis", 90);
    r1->appendStep("Cachaca", 5);
    r1->appendStep("Mischen", 10);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe2() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Margarita");
    r1->appendStep("Zitronensaft", 2);
    r1->appendStep("Cointreau", 2);
    r1->appendStep("Tequilla", 4);
    r1->appendStep("Eis", 50);
    r1->appendStep("Mischen", 20);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe3() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Daiquiri");
    r1->appendStep("Limettensaft", 2);
    r1->appendStep("Zuckersirup", 2);
    r1->appendStep("Rum weiss", 5);
    r1->appendStep("Eis", 50);
    r1->appendStep("Mischen", 20);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe4() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Planters Punch");
    r1->appendStep("Zitronensaft", 2);
    r1->appendStep("Grenadine", 1);
    r1->appendStep("Orangensaft", 8);
    r1->appendStep("Rum braun", 6);
    r1->appendStep("Eis", 100);
    r1->appendStep("Mischen", 20);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe5() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Caipiroska");
    r1->appendStep("Limettenstuecke", 8);
    r1->appendStep("Zucker", 15);
    r1->appendStep("Stampfen", 20);
    r1->appendStep("Eis", 90);
    r1->appendStep("Wodka", 5);
    r1->appendStep("Mischen", 10);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe6() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Caipirissima");
    r1->appendStep("Limettenstuecke", 8);
    r1->appendStep("Zucker", 15);
    r1->appendStep("Stampfen", 20);
    r1->appendStep("Eis", 90);
    r1->appendStep("Rum weiss", 5);
    r1->appendStep("Mischen", 10);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe7() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Cuban Island");
    r1->appendStep("Zitronensaft", 2);
    r1->appendStep("Cointreau", 2);
    r1->appendStep("Rum weiss", 2);
    r1->appendStep("Wodka", 2);
    r1->appendStep("Eis", 30);
    r1->appendStep("Mischen", 30);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe8() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Martini James B");
    r1->appendStep("Gin", 6);
    r1->appendStep("Wodka", 2);
    r1->appendStep("Noilly Prat", 1);
    r1->appendStep("Schuetteln", 10);
    this->recipes_.push_back(r1);
}

void RecipeBook::Recipe9() {
    Recipe* r1;
    r1 = new Recipe;
    r1->setName("Deathwish XXX");
    r1->appendStep("Wodka", 1500);
    r1->appendStep("Zucker", 15);
    r1->appendStep("Eis", 100);
    r1->appendStep("Mischen", 20);
    this->recipes_.push_back(r1);
}