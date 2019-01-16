//@(#) CocktailZubereiter.cpp
#include "CocktailMixer.h"

CocktailMixer::CocktailMixer(DeviceManager * deviceManager) {
    deviceManager_ = deviceManager;
}

bool CocktailMixer::mixCocktail(Recipe * recipe) {
    std::cout << "Gruess Gott, ich bin der CocktailZubereiter!" << std::endl
            << "Ich habe Ihre Bestellung: " << recipe->getName() << " erhalten." << std::endl
            << "Bitte gedulden Sie sich einen Moment, waehrend ich den Cocktail zubereite!\n" << std::endl;
    for (int i = 0; i < recipe->getNoOfRecipeSteps(); i++) {
        RecipeStep * schritt = recipe->getRecipeStep(i);
        std::string zutat = schritt->getZutat();
        float menge = schritt->getMenge();
        std::cout << "Rezeptschritt: " << zutat << ", " << menge << std::endl;
        deviceManager_->executeRecipeStep(zutat, menge);
    }
    deviceManager_->dispenseAll();
    deviceManager_->cleanAll();
    return true;
}

