#include "event.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

EventManager::EventManager(bool hardMode) : isHardMode(hardMode) {
    static bool initialized = false;
    if (!initialized) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }
}

EventManager::~EventManager() {
}

string EventManager::executeRandomEvent(Player* player, PotionManager* potionManager,
                                       bool& enemyDoubleHP, string& disabledEquipment) {
    if (isHardMode) {
        // Hard mode: 50% positive, 50% negative (2 out of 4 negative events affect next battle)
        int roll = rand() % 4;
        if (roll < 2) {
            return executeNegativeEvent(player, enemyDoubleHP, disabledEquipment);
        }
    }
    
    // Positive event (1-4)
    int eventNum = (rand() % 4) + 1;
    return executePositiveEvent(player, potionManager, eventNum);
}

string EventManager::executePositiveEvent(Player* player, PotionManager* potionManager, int eventNum) {
    switch (eventNum) {
        case 1: {
            // Get random equipment
            vector<string> equipmentTypes = {"Shield", "Sword", "Armor", "Shoes"};
            int index = rand() % equipmentTypes.size();
            string equip = equipmentTypes[index];
            
            if (player->addEquipment(equip)) {
                return "Event: You found a " + equip + "! Equipment added to inventory.";
            } else {
                return "Event: You found a " + equip + ", but your equipment inventory is full!";
            }
        }
        case 2: {
            player->addBossAttackBonus(30);
            return "Event: You feel a surge of power! +30 attack bonus for boss battle!";
        }
        case 3: {
            return "Event: Nothing happens. You continue your journey.";
        }
        case 4: {
            potionManager->addPotion("Strength Potion", 1);
            potionManager->addPotion("Attacker Potion", 1);
            potionManager->addPotion("Life Potion", 1);
            return "Event: You found a treasure chest! Received: Strength Potion, Attacker Potion, Life Potion x1 each.";
        }
        default:
            return "Event: Nothing happens.";
    }
}

string EventManager::executeNegativeEvent(Player* player, bool& enemyDoubleHP, string& disabledEquipment) {
    int eventType = rand() % 4;
    
    switch (eventType) {
        case 0: {
            // Lose some health
            int damage = 20 + (rand() % 30); // 20-50 damage
            player->takeDamage(damage);
            return "Event: You stepped on a trap! Lost " + to_string(damage) + " HP.";
        }
        case 1: {
            // Lose gold (if any)
            if (player->getGold() > 0) {
                int goldLost = 1;
                if (player->getGold() > 1) {
                    goldLost = 1 + (rand() % player->getGold());
                }
                for (int i = 0; i < goldLost; i++) {
                    player->spendGold(1);
                }
                return "Event: You were robbed! Lost " + to_string(goldLost) + " gold.";
            } else {
                return "Event: A thief tried to rob you, but you have no gold!";
            }
        }
        case 2: {
            // Negative Event 1: Next battle enemies have double HP
            enemyDoubleHP = true;
            return "Event: A dark curse weakens you! Enemies in the next battle will have double HP.";
        }
        case 3: {
            // Negative Event 2: Next battle one random equipment is disabled
            vector<string> equipment = player->getEquipment();
            if (!equipment.empty()) {
                int index = rand() % equipment.size();
                disabledEquipment = equipment[index];
                return "Event: A curse has been placed on your " + disabledEquipment + "! It will be disabled in the next battle.";
            } else {
                // If no equipment, apply damage instead
                player->takeDamage(25);
                return "Event: A cursed spirit curses you! Lost 25 HP.";
            }
        }
        default:
            return "Event: Nothing happens.";
    }
}

void EventManager::setHardMode(bool hardMode) {
    isHardMode = hardMode;
}

