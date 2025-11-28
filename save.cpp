#include "save.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

SaveManager::SaveManager(const std::string& filename) : saveFileName(filename) {
}

SaveManager::~SaveManager() {
}

bool SaveManager::saveGame(Player* player, PotionManager* potionManager, int currentLevel, int difficulty) {
    ofstream file(saveFileName);
    if (!file.is_open()) {
        cerr << "Error: Cannot open save file for writing." << endl;
        return false;
    }
    
    file << "LEVEL " << currentLevel << endl;
    file << "DIFFICULTY " << difficulty << endl;
    file << "PLAYER_BASE_MAXHP " << player->getBaseMaxHealth() << endl;
    file << "PLAYER_CURRENTHP " << player->getCurrentHealth() << endl;
    file << "PLAYER_BASE_ATTACK " << player->getBaseAttack() << endl;
    file << "PLAYER_GOLD " << player->getGold() << endl;
    file << "PLAYER_BOSS_BONUS " << player->getBossAttackBonus() << endl;
    
    auto equipment = player->getEquipment();
    file << "EQUIPMENT_COUNT " << equipment.size() << endl;
    for (const auto& equip : equipment) {
        file << "EQUIPMENT " << equip << endl;
    }
    
    auto potions = potionManager->getAllPotions();
    file << "POTION_COUNT " << potions.size() << endl;
    for (const auto& pair : potions) {
        file << "POTION " << pair.first << " " << pair.second << endl;
    }
    
    file.close();
    return true;
}

bool SaveManager::loadGame(Player* player, PotionManager* potionManager, int& currentLevel, int& difficulty) {
    ifstream file(saveFileName);
    if (!file.is_open()) {
        return false;
    }
    
    string line;
    string key;
    int equipmentCount = 0;
    int potionCount = 0;
    
    player->clearEquipment();
    
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> key;
        
        if (key == "LEVEL") {
            iss >> currentLevel;
        } else if (key == "DIFFICULTY") {
            iss >> difficulty;
        } else if (key == "PLAYER_BASE_MAXHP") {
            int maxHP;
            iss >> maxHP;
            player->setBaseMaxHealth(maxHP);
        } else if (key == "PLAYER_CURRENTHP") {
            int currentHP;
            iss >> currentHP;
            player->setCurrentHealth(currentHP);
        } else if (key == "PLAYER_BASE_ATTACK") {
            int attack;
            iss >> attack;
            player->setBaseAttack(attack);
        } else if (key == "PLAYER_GOLD") {
            int gold;
            iss >> gold;
            player->setGold(gold);
        } else if (key == "PLAYER_BOSS_BONUS") {
            int bonus;
            iss >> bonus;
            player->setBossAttackBonus(bonus);
        } else if (key == "EQUIPMENT_COUNT") {
            iss >> equipmentCount;
        } else if (key == "EQUIPMENT" && equipmentCount > 0) {
            string equipName;
            iss >> equipName;
            player->addEquipment(equipName);
            equipmentCount--;
        } else if (key == "POTION_COUNT") {
            iss >> potionCount;
        } else if (key == "POTION" && potionCount > 0) {
            string potionName;
            int quantity;
            iss >> potionName >> quantity;
            potionManager->addPotion(potionName, quantity);
            potionCount--;
        }
    }
    
    file.close();
    return true;
}

bool SaveManager::saveExists() const {
    ifstream file(saveFileName);
    bool exists = file.good();
    file.close();
    return exists;
}

bool SaveManager::deleteSave() {
    return remove(saveFileName.c_str()) == 0;
}
