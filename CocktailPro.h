//@(#) CocktailPro.h

#ifndef COCKTAILPRO_H_H
#define COCKTAILPRO_H_H

#include "DeviceManager.h"
#include "IngredientManager.h"
#include "RecipeBook.h"
#include "CocktailMixer.h"

/**
 * @class CocktailPro
 * @brief CocktailPro connects all the parts to one complete unit.
 * 
 * This is the complete unit that the user interacts with.
 * Makes use of the other parts to mix the selected cocktail.
 *  
 */
class CocktailPro {
    /**
     * Constant string that represents the "-D" argument when executing
     */
    static const std::string DEMO_OPTION;

    /**
     * Constant string that represents the "-TEST" argument when executing
     */
    static const std::string TEST_OPTION;

    /**
     * Constant string that represents the "-TURBO" argument when executing
     */
    static const std::string TURBO_OPTION;

    /**
     * Instance variable cocktailMixer.
     * Used to execute the recipe steps.
     */
    CocktailMixer * cocktailMixer;

    /**
     * Instance variable deviceManager.
     * Used to communicate with the devices.
     */
    DeviceManager * deviceManager;

    /**
     * Instance variable recipeBook.
     * Used to compile a list of mixable recipes based on the available ingredients.
     */
    RecipeBook * recipeBook;

    /**
     * Instance variable ingredientManager.
     * Used to read available ingredients.
     */
    IngredientManager * ingredientManager;

private:
    /**
     * @brief Copy constructor for CocktailPro.
     * @param cocktailPro CocktailPro to copy.
     */
    CocktailPro(const CocktailPro &cocktailPro);

    /**
     * Flag that is set when the CocktailPro is run in test mode.
     */
    bool isTest_;
    
    /**
     * Flag that is set when the CocktailPro is run in demo mode.
     */
    bool isDemo_;
     /**
     * store input
     */
    std::string eingabe_;

    /**
     * Path to the ingredients file
     */
    std::string ingredientsFile_;

    /**
     * Path to the recipes file
     */
    std::string recipesFile_;

    /**
     * @brief Handles the parameter and sets the paths for ingredients and recipes
     * @param parameter Parameter to handle
     */
    void handleParameter(std::string parameter);

    /**
     * @brief Refresh the current "mixable"-status of each recipe
     */
    void refreshMixableStatus();

protected:
    /**
     * @brief Outputs the cocktail menu.
     * @return The number of the chosen cocktail.
     * 
     * This prints a menu of all mixable cocktails to console.
     * The user is then prompted to select a cocktail by inputing its number into the console.
     * Returns the selected number.
     */
    int chooseCocktail();

    /**
     * @brief The main loop of the CocktailPro
     * 
     * Queries the user for a cocktail and mixes it.
     */
    void start();

    /**
     * @brief Uses all subcomponents to mix the chosen cocktail
     * @param choice The number of the chose cocktail
     */
    void mixChoice(int choice);

public:
    /**
     * @brief Constructor for CocktailPro.
     * @param argc Number of arguments included in the program call. 
     * @param turbo Array of arguments.
     * 
     */
    CocktailPro(int argc, char * * turbo);
};

#endif
