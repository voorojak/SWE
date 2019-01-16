//@(#) DeviceVerwalter.cpp

#include "DeviceManager.h"

DeviceManager::DeviceManager(IngredientManager * ingredientManager) : ingredientManager_(ingredientManager) {
    this->createDevices();
}

void DeviceManager::createDevices() {
    usualIngredientCounter_ = 0;
    MAX_USUAL_INGREDIENTS = 11;

    scale_ = new Scale();
    devices_ = new std::map<std::string, InternalDevice *>;

    dispenser_ = new Dispenser(25, 1000, scale_);
    devices_->insert(std::make_pair("Entleeren", dispenser_));

    ricer_ = new Ricer();
    devices_->insert(std::make_pair("Stampfen", ricer_));

    shaker_ = new Shaker();
    devices_->insert(std::make_pair("Schuetteln", shaker_));

    mixer_ = new Mixer();
    devices_->insert(std::make_pair("Mischen", mixer_));

    std::string ingredient;
    for (int i = ingredientManager_->getIngredientCount() - 4; i >= 0; i--) {
        ingredient = ingredientManager_->getIngredient(i);

        if (devices_->find(ingredient) == devices_->end()) {// not in devices_ yet 
            handleInsertOfNewDevice(ingredient);
        } else {//found in devices_
            handleInsertOfKnownDevice(ingredient);
        }
    }
}

void DeviceManager::handleInsertOfNewDevice(std::string nameOfIngredient) {
    if (nameOfIngredient == "Eis") {
        devices_->insert(std::make_pair(nameOfIngredient, new Doser(20, 1000, nameOfIngredient, scale_)));
    } else if (nameOfIngredient == "Limettenstuecke") {
        devices_->insert(std::make_pair(nameOfIngredient, new Doser(10, 1000, nameOfIngredient, scale_)));
    } else {
        if (usualIngredientCounter_ < MAX_USUAL_INGREDIENTS) {
            devices_->insert(std::make_pair(nameOfIngredient, new Doser(1, 250, nameOfIngredient, scale_)));
            usualIngredientCounter_++;
        } else {
            printErrorStatus(nameOfIngredient);
        }
    }
}

void DeviceManager::handleInsertOfKnownDevice(std::string nameOfIngredient) {
    //If ice or limepieces -> ignore. Only once allowed
    if (nameOfIngredient == "Eis") {
        printErrorStatus(nameOfIngredient);
    } else if (nameOfIngredient == "Limettenstuecke") {
        printErrorStatus(nameOfIngredient);
    } else {
        if (usualIngredientCounter_ < MAX_USUAL_INGREDIENTS) {
            static_cast<Doser*> (devices_->at(nameOfIngredient))->addFillingCapacity();
            usualIngredientCounter_++;
        } else {
            printErrorStatus(nameOfIngredient);
        }
    }
}

bool DeviceManager::executeRecipeStep(std::string zutat, float menge) {
    if (zutat == "Limettenstuecke") {
        // Der Kunde will Limetten ja unbedingt nach Stueck und nicht nach Gewicht abmessen...
        int stckProZeit = (static_cast<Doser*> (devices_->at(zutat)))->getThroughput();
        return devices_->at(zutat)->execute(menge * stckProZeit);
    } else {
        return devices_->at(zutat)->execute(menge);
    }
}

void DeviceManager::dispense(float amount) {
    dispenser_->execute(amount);
}

void DeviceManager::dispenseAll() {
    dispense(scale_->getWeight());
}

void DeviceManager::cleanAll() {
    for (std::map<std::string, InternalDevice*>::iterator i = devices_->begin(); i != devices_->end(); ++i) {
        i->second->clean();
    }
}

void DeviceManager::printAllFillngLevels() {
    for (std::map<std::string, InternalDevice*>::iterator i = devices_->begin(); i != devices_->end(); ++i) {
        i->second->status();
    }
}

void DeviceManager::printErrorStatus(std::string nameOfIngredient) {
    std::cerr << std::endl << std::endl << "Nicht genuegend freie Dosierertypen vorhanden fuer: " << nameOfIngredient << std::endl
            << "Bitte korrigieren Sie die Zutatendatei und starten Sie das System neu!" << std::endl;
    exit(0);
}

bool DeviceManager::isAmountEnough(std::string name, int amount) {
    if (amount > devices_->at(name)->getFillingLevel()) {
        return false;
    }
    return true;
}