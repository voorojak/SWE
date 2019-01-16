#ifndef RECIPEBOOK_H_H
#define RECIPEBOOK_H_H

#include <fstream>
#include <sstream>
#include <cstdlib> // fuer exit() unter Linux
#include <iostream>
#include <string>
#include <vector>
#include "Recipe.h"
#include "IngredientManager.h"

/**
 * @class RecipeBook
 * @brief RecipeBook manages a collection of recipes
 *
 * a list of recipes
 * You can ask for the number, delete query of recipes or recipes by index
 */
class RecipeBook {
private:

    /**
     * Flag that is set when in demo mode
     */
    bool isDemo_;

    /**
     * Containing all currently available ingredients
     */
    IngredientManager * ingredientManager_;

    /**
     * All available recipes
     */
    std::vector<Recipe *> recipes_;

    /**
     * @brief Loads recipes from file, if the file could not be opened loads them from code.
     * @param file Path to the recipe file
     */
    void loadRecipes(std::string file);

    /**
     * @brief Parses one line of the recipe file and adds the recipe to the recipe list
     * @param line Line to parse
     */
    void parseLine(std::string line);



    /**
     * @brief Checks a given recipe, whether it is craftable
     * @param recipe Recipe to check
     */
    bool checkAmountOfIngredients(Recipe* recipe);

    /**
     * @brief Checks a given ingredient, whether it is avaliable in the recipelist
     * @param toSearch ingredient to search for in recipelist
     */
    bool searchIngredient(std::string toSearch);

    /**
     * Prints all or only mixable recipes depending on the param onlyMixable
     * @param onlyAvailiable Indicates if all or only availaible cocktails should be printed
     */
    void browse(bool onlyAvailiable);

    /**
     * @brief Insert hardcoded recipes
     */
    void insertRecipes();

    /**
     * @brief Insert additional demo recipes
     */
    void insertDemoRecipes();
    
    /**
     * @brief prints a recipe and its number to console
     * @param r recipe to print
     * @param i number to display
     * @param onlyAvailiable if true, print only availiable recipes
     */
    void printRecipe(Recipe* r, int i, bool onlyAvailiable);

    /**
     * Hardcoded recipes
     */
    //regular recipes
    void Recipe1();
    void Recipe2();
    void Recipe3();
    void Recipe4();
    void Recipe5();
    void Recipe6();
    void Recipe7();
    void Recipe8();

    //demo recipes
    void Recipe9();

public:
    /** 
     * @brief Constructor that creates a RecipeBook
     * @param ingredientManager IngredientManager used to filter the non mixable recipes
     * @param file Path to the recipe file
     * @param isDemo Indicates to run in demo mode
     * @return A pointer to the created RecipeBook
     *
     * This method creates a RecipeBook.
     * It uses temporarily an object of the class Initialisierer
     * to initialize the list of recipes. After that the
     * Initialisierer is destroyed.
     */
    RecipeBook(IngredientManager* ingredientManager, std::string file, bool isDemo);

    /** @brief Destructor that deletes the RecipeBook
     */
    virtual ~RecipeBook();

    /** @brief Returns the number of recipes
     * @return The number of recipes in the RecipeBook
     */
    int getNumberOfRecipes();

    /** @brief Returns the number of availiable recipes
     * @return The number of recipes in the RecipeBook
     */
    int getNumberOfAvailiableRecipes();

    /**
     * @brief Browsing through all recipes and prinitng them out
     */
    void browseAllRecipes();

    /**
     * @brief Browsing through all availiable recipes and prinitng them out
     */
    void browseAvailiableRecipes();
    
    /** @brief fetches the position-th recipe
     * @param position a positive integer for the position-th recipe
     * @return A pointer to the requested recipe object, NULL for invalid position
     *
     * This method returns the i-th recipe;
     * where position is an integer from 0 to n-1
     * where n is the number of recipes in the RecipeBook
     */
    Recipe * getRecipe(unsigned int position);

    /**
     * @brief Checks if the recipe at position exists and is mixable
     * @param postition The position to check
     * @return True if recipe exists and is mixable, false otherwise
     */
    bool isValidAndMixable(unsigned int postition);

    /**
     * @brief Checking all recipes, whether they are craftable with the currently available ingredients
     * Flags recipes that can't be mixed as not mixable.
     */
    void filterRecipes();


};

#endif
