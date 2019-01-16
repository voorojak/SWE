//@(#) CocktailPro.cpp

#include "CocktailPro.h"
#include <string>
const std::string CocktailPro::DEMO_OPTION = "-DEMO";
const std::string CocktailPro::TEST_OPTION = "-TEST";
const std::string CocktailPro::TURBO_OPTION = "-TURBO";

CocktailPro::CocktailPro(int argc, char ** param) : isTest_(false), isDemo_(false), ingredientsFile_("zutaten.txt"), recipesFile_("rezepte.csv") {
    for (int i = 0; i < argc; ++i) {
        handleParameter(std::string(param[i]));
    }
    ingredientManager = new IngredientManager(ingredientsFile_, isDemo_);
    recipeBook = new RecipeBook(ingredientManager, recipesFile_, isDemo_);
    deviceManager = new DeviceManager(ingredientManager);
    cocktailMixer = new CocktailMixer(deviceManager);
    if (!isTest_) {
        start();
    }
}

void CocktailPro::refreshMixableStatus() {
    int mainIndex = 0;

    while (mainIndex < recipeBook->getNumberOfRecipes()) {
        Recipe* rec;
        RecipeStep* recStep;
        rec = recipeBook->getRecipe(mainIndex);

        int stepIndex = 0;
        while (stepIndex < rec->getNoOfRecipeSteps() && rec->isAvailable()) {
            recStep = recipeBook->getRecipe(mainIndex)->getRecipeStep(stepIndex);
            std::string name = recStep->getZutat();
            int amount = recStep->getMenge();
            //"Schuetteln", "Mischen", "Stampfen" are defaultdevices with no real limit. they always have a default-limit (fillinglevel) of 1000
                if (!deviceManager->isAmountEnough(name, amount)) {
                    rec->setMixable(false);
                }
            stepIndex++;
        }
        mainIndex++;
    }
}

void CocktailPro::handleParameter(std::string parameter) {
    Timer * timer = Timer::getInstance();
    if (parameter == DEMO_OPTION) {
        isDemo_ = true;
    }

    if (parameter == TEST_OPTION) {
        isTest_ = true;
    }

    if (parameter == TURBO_OPTION) {
        timer->setTurbo(Timer::TURBO_ON);
    }
}

// not used

CocktailPro::CocktailPro(const CocktailPro& toCopy) {
    bool yes = toCopy.isTest_;
    std::cout << "haha no!" << yes << std::endl;
}

void CocktailPro::mixChoice(int choice) {
    if (recipeBook->isValidAndMixable(choice - 1)) {
        Recipe * recipe = recipeBook->getRecipe(choice - 1);
        std::cout << recipe->getName() << std::endl;
        cocktailMixer->mixCocktail(recipe);
    } else if (choice != -1) {
        std::cout << "Falsche Cocktailnummer!" << std::endl;
    }
}

void CocktailPro::start() {
    int choice = -1;
    do {
        choice = chooseCocktail();
        mixChoice(choice);
    } while (choice != -1 && !isTest_);
}

int CocktailPro::chooseCocktail() {
    refreshMixableStatus();
    std::cout << std::endl << "********** Vorhandene Zutaten **********" << std::endl;
    deviceManager->printAllFillngLevels();
    std::cout << "********** Mischbare Rezepte **********" << std::endl;
    recipeBook->browseAvailiableRecipes();
    std::cout << "Was haetten Sie denn gern? (-1 zum Verlassen)" << std::endl;
    if (!isTest_) {
        std::cin >> eingabe_;
    } else {
        eingabe_ = "1";
    }
    int zahl = atoi(eingabe_.c_str());
    return zahl;
}
