//Comments by Vedat Oeskan
#ifndef RECIPE_H_H
#define RECIPE_H_H

#include "RecipeStep.h"
#include <list>
#include <string>

/**
 * @class Recipe
 * @brief Contains recipesteps and output / changing operations of the recipe
 */
class Recipe {
public:
    /**
     * @brief Constructor: Initializing variables (clears them)
     */
    Recipe(void);

    /**
     * @brief Destructor: standard
     */
    ~Recipe();

    /**
     * @brief get amount of different irgredient in this recipe
     */
    int getNoOfRecipeSteps();

    /**
     * @brief getter for selected recipestep 
     * @param i returns the recipestep(ingredient) on place i of the recipestep list
     */
    RecipeStep * getRecipeStep(unsigned int i);

    /**
     * @brief getter of recipe name
     */
    std::string getName(void) const;

    /**
     * @brief Set name of recipe
     * @param recipeName contains name to set
     */
    void setName(const std::string& recipeName);

    /**
     * @brief add a recipestep to the recipestep list (appended at the end of the list)
     * @param recipeName name of the ingredient
     * @param ingredientAmount needed amount of this ingredient
     */
    void appendStep(std::string recipeName, float ingredientAmount);

    /**
     * @brief lists all names of ingriedients needed for this recipe
     */
    void browse();

    /**
     * Returns if this recipe is avialable with the current ingredients.
     * @return The value of available_
     */
    bool isAvailable() const;

    /**
     * Set if this recipe is available or not
     * @param available Value to set available_ to
     */
    void setAvailable(bool available);

    /**
     * Returns if this recipe is still mixable or not
     * @return The value of mixable_
     */
    bool isMixable() const;

    /**
     * Set if this recipe is still mixable or not
     * @param mixable Value to set mixable_ to
     */
    void setMixable(bool mixable);

private:

    /**
     * Boolean that indicates if this recipe is mixable with the current ingredients
     */
    bool availiable_;
    /**
     * Boolean that indicates if this recipe is mixable with the current ingredients
     */
    bool mixable_;
    /**
     * Contains needed Steps (means igredient and amount) fot this recipe
     */
    std::list<RecipeStep*> recipeCraftingSteps_;

    /**
     * Name of this Recipe
     */
    std::string recipeName_;
};

#endif
