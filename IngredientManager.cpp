//@(#) VorhandeneZutaten.cpp

#include "IngredientManager.h"

IngredientManager::IngredientManager(std::string file, bool isDemo) : isDemo_(isDemo) {
    this->ingredients = new std::vector<std::string>;
    readIngredients(file);
    this->doserCount = ingredients->size();
}

IngredientManager::IngredientManager(const IngredientManager& toCopy) {
    this->ingredients = new std::vector<std::string>;
    for (unsigned int i = 0; i < toCopy.ingredients->size(); i++) {
        this->ingredients->push_back(toCopy.ingredients->at(i));
    }
    this->doserCount = ingredients->size();
    this->isDemo_ = toCopy.isDemo_;
}

IngredientManager::~IngredientManager(void) {
}

void IngredientManager::readIngredientsFromFile(std::string myfile) {
    std::ifstream in;
    FileName = myfile;
    in.open(FileName.c_str(), std::ios::in); // c_str wandelt den String in char[]
    if (!in) {// File konnte nicht geoeffnet werden
        std::string my_exception = "File not found: " + FileName;
        std::cout << my_exception << std::endl;
        throw my_exception;
    }
    std::cout << "Oeffne Zutatendatei " << FileName << std::endl;
    std::string zeile;
    while (getline(in, zeile)) {
        if (zeile.size() && zeile[zeile.size() - 1] == '\r') { // Cut trailing \r - to make Linux or Windows Files equal
            zeile = zeile.substr(0, zeile.size() - 1);
        }
        this->ingredients->push_back(zeile);
    }
    in.close();
}

void IngredientManager::readIngredients(std::string file) {
    if (isDemo_) {
        insertDemoIngredients();
    } else {
        readIngredientsFromFile(file);
    }
    this->browse(); // Eingelesene Zutaten ausgeben
    insertDeviceAbilities(); // Mischen und Stampfen, etc hinzufuegen
}

void IngredientManager::browse(void) {
    std::cout << "*********** Verfuegbare Einheiten bzw. Zutaten: ***********" << std::endl;
    for (unsigned int i = 0; i < ingredients->size(); i++/*std::string zutat : zutaten*/) {
        std::cout << ingredients->at(i) << std::endl;
    }
    std::cout << "**********************************************************" << std::endl;
}

void IngredientManager::insertDeviceAbilities() {
    ingredients->push_back("Mischen");
    ingredients->push_back("Stampfen");
    ingredients->push_back("Schuetteln");
}

void IngredientManager::insertDemoIngredients() {
    std::cout << "Fuege Demo-Zutaten ein..." << std::endl;
    ingredients->push_back("Limettenstuecke");
    ingredients->push_back("Zucker");
    ingredients->push_back("Cointreau");
    ingredients->push_back("Cachaca");
    ingredients->push_back("Eis");
    ingredients->push_back("Wodka");
    ingredients->push_back("Wodka");
    ingredients->push_back("Zitronensaft");
    ingredients->push_back("Gerandine");
    ingredients->push_back("Limettensaft");
    ingredients->push_back("Tequilla");
    ingredients->push_back("Gin");
    ingredients->push_back("Noilly Prat");
}

std::string IngredientManager::getIngredient(int position) {
    return ingredients->at(position);
}

int IngredientManager::getIngredientCount() {
    return ingredients->size();
}
