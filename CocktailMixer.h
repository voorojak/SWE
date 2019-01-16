//@(#) CocktailZubereiter.h

#ifndef COCKTAILMIXER_H_H
#define COCKTAILMIXER_H_H



#include "Recipe.h"
#include "RecipeBook.h"
#include "DeviceManager.h"

/**
 * @class CocktailMixer
 * @brief Mixes the cocktail
 * 
 * Does the actual mixing of the cocktail by following the steps in the recipe.
 */
class CocktailMixer {
public:
    /**
     * @brief Constructor of CocktailMixer
     * @param deviceManager DeviceManager that is used to execute the recipe steps
     */
    explicit CocktailMixer(DeviceManager * deviceManager);
    
    /**
     * @brief Reads and executes the steps from a recipe
     * @param recipe Recipe to mix
     * @return true if mixing was successful, false otherwise
     */
    bool mixCocktail(Recipe * recipe);

private:
    /**
     * Instance variable deviceManager_.
     * Used to execute the steps of a given recipe.
     */
    DeviceManager * deviceManager_;
};

#endif
