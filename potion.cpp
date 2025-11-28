#include "potion.h"
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

PotionManager::PotionManager() {
    potions.clear();
}

PotionManager::~PotionManager() {
    potions.clear();
}

void PotionManager::addPotion(const std::string& potionName, int quantity) {
    if (potions.find(potionName) != potions.end()) {
        potions[potionName] += quantity;
    } else {
        potions[potionName] = quantity;
    }
}

bool PotionManager::usePotion(const std::string& potionName) {
    if (potions.find(potionName) != potions.end() && potions[potionName] > 0) {
        potions[potionName]--;
        if (potions[potionName] == 0) {
            potions.erase(potionName);
        }
        return true;
    }
    return false;
}

int PotionManager::getQuantity(const std::string& potionName) const {
    auto it = potions.find(potionName);
    if (it != potions.end()) {
        return it->second;
    }
    return 0;
}

std::map<std::string, int> PotionManager::getAllPotions() const {
    return potions;
}

bool PotionManager::hasPotion(const std::string& potionName) const {
    return potions.find(potionName) != potions.end() && potions.at(potionName) > 0;
}

std::vector<std::string> PotionManager::getPotionTypes() {
    return {"Strength Potion", "Attacker Potion", "Life Potion", "Mystery Potion"};
}

std::string PotionManager::getRandomPotion() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
    
    vector<string> types = getPotionTypes();
    int index = rand() % types.size();
    return types[index];
}
