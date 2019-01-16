//Comments by Vedat Oeskan
#include <algorithm>
#include "RecipeStep.h"


RecipeStep::RecipeStep(void) : m_Zutat(""), m_Menge(0)
{
}

RecipeStep::~RecipeStep() {
}

std::string RecipeStep::getZutat(void) const {
    return m_Zutat;
}

float RecipeStep::getMenge(void) const {
    return m_Menge;
}

void RecipeStep::setZutat(std::string zutat) {
    this->m_Zutat = zutat;
}

void RecipeStep::setMenge(float menge) {
    this->m_Menge = menge;
}
