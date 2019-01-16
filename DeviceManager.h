//@(#) DeviceVerwalter.h

#ifndef DEVICEMANAGER_H_H
#define DEVICEMANAGER_H_H

#include <string>
#include <map>
#include <typeinfo>

#include "InternalDevice.h"
#include "IngredientManager.h"
#include "Doser.h"
#include "Mixer.h"
#include "Ricer.h"
#include "Shaker.h"
#include "Dispenser.h"
#include "Scale.h"

/**
 * @class DeviceManager
 * @brief Initializes the used devices and executes given recipe steps
 * 
 * The DeviceManager manages all used devices and executes recipe steps by manipulating those devices.
 */
class DeviceManager {
public:
    /**
     * @brief Constructor of DeviceManager
     * @param ingredientManager List of all available ingredients
     */
    explicit DeviceManager(IngredientManager * ingredientManager);

    /**
     * @brief Finds and uses needed device for a given recipe step
     * @param ingredient Ingredient to be used in the recipe step
     * @param amount Amount of ingredient to be used in the recipe step
     * @return Success or failure of the execution.
     * 
     * Finds the proper device and uses it according to the given amount and ingredient.
     */
    bool executeRecipeStep(std::string ingredient, float amount);

    /**
     * @brief Releases a given amount from the mixing container
     * @param amount Amount to be released
     * 
     * Uses the Dispenser device to release a given amount from the mixing container.
     */
    void dispense(float amount);

    /**
     * @brief Releases all content from the mixing container
     */
    void dispenseAll();
    /**
     * @brief Cleans all devices
     * 
     * Loops through all devices and cleans them.
     */
    void cleanAll();
    /**
     * @brief Printing all filling levels
     * Printing the filling level of al availiable ingredients
     */
    void printAllFillngLevels();

    /**
     * @brief returns true when amount in doser is larger than the needed amount
     * @return true if enough
     */
     bool isAmountEnough(std::string name, int amount);

private:
    /**
     * @brief Map of available devices
     * 
     * Map of available devices.
     * Formatted as <"ingredient", device>.
     */
    std::map<std::string, InternalDevice *> * devices_;

    /**
     * Instance variable dispenser_.
     * Can be used to release a given amount from the mixing container.
     */
    Dispenser * dispenser_;

    /**
     * Instance variable mixer_.
     * Can be used to mix ingredients.
     */
    Mixer * mixer_;

    /**
     * Instance variable ricer_.
     * Can be used to rice ingredients.
     */
    Ricer * ricer_;

    /**
     * Instance variable shaker_.
     * Can be used to shake ingredients.
     */
    Shaker * shaker_;

    /**
     * Instance variable ingredientManager_.
     * Contains a list of all available ingredients.
     */
    IngredientManager * ingredientManager_;

    /**
     * Instance variable scale_.
     * Attached to instances of Doser.
     */
    Scale * scale_;

    /**
     * Variable for counting the 'normal' ingredients (not ice of limepieces...)
     */
    int usualIngredientCounter_;

    /**
     * Defines the maximum number of ordinary dosing units allowed
     */
    int MAX_USUAL_INGREDIENTS;

    /**
     * @brief Initializes all devices
     * 
     * Creates new instances of all needed devices.
     */
    void createDevices();

    /**
     * @brief creating device for a given ingredient
     * @param nameOfIngredient name of new ingredient
     * creating new device for a given ingredient
     */
    void handleInsertOfNewDevice(std::string nameOfIngredient);

    /**
     * @brief handling known ingredients
     * @param nameOfIngredient name of known ingredient
     * adjusting fillinglevel (or not) depending on the ingredientname.
     */
    void handleInsertOfKnownDevice(std::string nameOfIngredient);

    /**
     * @brief Printing all filling levels
     * Printing the filling level of al availiable ingredients
     */
    void printErrorStatus(std::string nameOfIngredient);

};

#endif
