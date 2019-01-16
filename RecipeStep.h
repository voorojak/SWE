//Comments by Vedat Oeskan
#ifndef RECIPESTEP_H_H
#define RECIPESTEP_H_H

#include <list>
#include <string>

/**
 * @class RecipeStep
 * @brief containing ingredient and amount of it fo a recipestep
 *
 * containing ingridient and amount of it fo a recipestep with getter and setter to access
 */
class RecipeStep {
	/**
	* containing the ingredient for this step
	*/
    std::string m_Zutat;
	/**
	* containing the amount of the ingredient for this step
	*/
    float m_Menge;

public:
	/**
	* @brief Constructor: initializing all variabels with '0'
	*/
    RecipeStep(void);

	/**
	* @brief Destructor: standard
	*/
    ~RecipeStep();

	/**
	* @brief getter: get m_Zutat
	*/
    std::string getZutat(void) const;

	/**
	* @brief getter: get m_Menge
	*/
    float getMenge(void) const;

	/**
	* @brief setter: set m_Zutat
	* @param zutat setter
	*/
    void setZutat(std::string zutat);

	/**
	* @brief setter: set m_Menge
	* @param menge setter
	*/
    void setMenge(float menge);

};
#endif
