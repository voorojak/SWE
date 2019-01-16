//@(#) VorhandeneZutaten.h

#ifndef INGREDIENTMANAGER_H_H
#define INGREDIENTMANAGER_H_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib> // fuer exit() unter Linux
#include <iostream>

/**
 * @class IngredientManager
 * @brief Stores and manages the available ingredients
 * 
 * Reads and stores the ingredients that are available.
 */
class IngredientManager {
public:
    /**
     * @brief Constructor of IngredientManager
     * @param file Path to the ingredients file
     * @param isDemo Indicates to run in demo mode
     */
    explicit IngredientManager(std::string file, bool isDemo);

    /**
     * @brief Copy constructor of IngredientManager;
     * @param toCopy object to copy
     */
    IngredientManager(const IngredientManager& toCopy);

    /**
     * @brief Destructor of IngredientManager, freeing dynamic allocated memory
     */
    virtual ~IngredientManager();

    /**
     * @brief Prints all available ingredients
     */
    void browse(void);

    /**
     * @brief Gets the ingredient at the given position
     * @param [in] position Position to query the available ingredients at
     * @return The ingredient at the queried position in the array
     */
    std::string getIngredient(int position);

    /**
     * @brief Gets the total count of all available ingredients
     * @return Count of available ingredients
     * 
     * Returns the size of the vector that stores the available ingredients.
     */
    int getIngredientCount();

private:
    /**
     * Vector that stores the names of the available ingredients.
     */
    std::vector<std::string> * ingredients;

    /**
     * Flag that can be set to bypass the file I/O to get available ingredients.
     * If set DummyZutatenEinfuegen will be used instead.
     */
    static const bool DEBUG = false;

    /**
     * @brief Reads the available ingredients
     * @param file Path to the ingredients file
     * Based on the DEBUG flag either the file I/O or the dummy data set are chosen.
     * Also adds special abilities as ingredients.
     */
    void readIngredients(std::string file);

    /**
     * @brief Read the available ingredients from a given file
     * @param [in] myfile The path to the file to read from
     */
    virtual void readIngredientsFromFile(std::string myfile);

    /**
     * @brief Adds special abilities like ricing and mixing as ingredients
     * 
     * Adds special device abilities to the ingredients vector.
     */
    void insertDeviceAbilities();

    /**
     * @brief Insert hardcoded demo ingredients
     */
    void insertDemoIngredients();
    
    /**
     * The count of all dosers based on the count of all available ingredients.
     */
    int doserCount;

    /**
     * Flag that is set when in demo mode
     */
    bool isDemo_;
};
/**
 * Path to the file that has all available ingredients listed.
 * Only initialized if the available ingredients where read from file.
 */
static std::string FileName;
#endif
