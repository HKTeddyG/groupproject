#include "battle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
using namespace std;

Battle::Battle(Player* player, PotionManager* potionManager,
               const vector<string>& enemyTypes, bool playerFirst,
               bool enemyDoubleHP, const string& disabledEquip)
    : player(player), potionManager(potionManager), 
      playerTurnFirst(playerFirst), turnCount(0) {
    
    // Create enemies based on types
    for (const auto& type : enemyTypes) {
        if (type == "Slim") {
            enemies.push_back(make_unique<Slim>());
        } else if (type == "Batho") {
            enemies.push_back(make_unique<Batho>());
        } else if (type == "Goust") {
            enemies.push_back(make_unique<Goust>());
        } else if (type == "Boss") {
            enemies.push_back(make_unique<Boss>());
        }
    }
    
    // Limit to maximum 3 enemies
    while (enemies.size() > 3) {
        enemies.pop_back();
    }
    
    // Apply double HP effect to all enemies
    if (enemyDoubleHP) {
        for (auto& enemy : enemies) {
            enemy->doubleHealth();
        }
    }
    
    // Set disabled equipment for player
    player->setDisabledEquipment(disabledEquip);
}

Battle::~Battle() {
}

void Battle::displayStatus() const {
    cout << "\n=== Battle Status ===" << endl;
    cout << "Player HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << endl;
    cout << "Turn: " << turnCount << endl;
    cout << "\nEnemies:" << endl;
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->isAlive()) {
            cout << "  " << (i + 1) << ". " << enemies[i]->getName() 
                 << " HP: " << enemies[i]->getCurrentHealth() << "/" 
                 << enemies[i]->getMaxHealth() << endl;
        }
    }
    cout << "====================\n" << endl;
}

bool Battle::execute() {
    player->restoreToFull();
    // Set extra actions from Shoes, but only if Shoes are not disabled
    int shoesCount = 0;
    if (player->getDisabledEquipment() != "Shoes") {
        shoesCount = player->countEquipment("Shoes");
    }
    player->setExtraActions(shoesCount);
    
    cout << "\n=== BATTLE BEGINS ===" << endl;
    displayStatus();
    
    while (!isWon() && !isLost()) {
        turnCount++;
        
        if (playerTurnFirst) {
            if (!playerTurn()) {
                return false; // Player quit
            }
            removeDeadEnemies();
            if (isWon()) break;
            
            enemyTurn();
            removeDeadEnemies();
        } else {
            enemyTurn();
            removeDeadEnemies();
            if (isWon()) break;
            
            if (!playerTurn()) {
                return false; // Player quit
            }
            removeDeadEnemies();
        }
        
        displayStatus();
    }
    
    // Clear disabled equipment after battle
    player->setDisabledEquipment("");
    
    if (isWon()) {
        cout << "\n=== VICTORY! ===" << endl;
        return true;
    } else {
        cout << "\n=== DEFEAT ===" << endl;
        return false;
    }
}

bool Battle::playerTurn() {
    int actions = 1 + player->getExtraActions();
    player->setExtraActions(0); // Reset after use
    
    for (int actionNum = 0; actionNum < actions; actionNum++) {
        if (isWon() || isLost()) break;
        
        cout << "\n--- Player Turn ---" << endl;
        cout << "Choose action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Potion" << endl;
        cout << "3. Skip" << endl;
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            actionNum--; // Retry this action
            continue;
        }
        
        switch (choice) {
            case 1:
                playerAttack();
                break;
            case 2:
                playerUsePotion();
                break;
            case 3:
                cout << "You skip your turn." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                actionNum--; // Retry this action
                continue;
        }
        
        if (actions > 1 && actionNum < actions - 1) {
            cout << "You have " << (actions - actionNum - 1) << " more action(s)." << endl;
        }
    }
    
    return true;
}

void Battle::playerAttack() {
    if (enemies.empty()) return;
    
    // Count alive enemies
    vector<int> aliveIndices;
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i]->isAlive()) {
            aliveIndices.push_back(i);
        }
    }
    
    if (aliveIndices.empty()) return;
    
    int targetIndex;
    if (aliveIndices.size() == 1) {
        targetIndex = aliveIndices[0];
    } else {
        cout << "Select target:" << endl;
        for (size_t i = 0; i < aliveIndices.size(); i++) {
            int idx = aliveIndices[i];
            cout << (i + 1) << ". " << enemies[idx]->getName() 
                 << " (HP: " << enemies[idx]->getCurrentHealth() << ")" << endl;
        }
        
        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > (int)aliveIndices.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Attack cancelled." << endl;
            return;
        }
        targetIndex = aliveIndices[choice - 1];
    }
    
    int damage = player->getAttack();
    enemies[targetIndex]->takeDamage(damage);
    cout << "You attack " << enemies[targetIndex]->getName() 
         << " for " << damage << " damage!" << endl;
    
    if (!enemies[targetIndex]->isAlive()) {
        cout << enemies[targetIndex]->getName() << " is defeated!" << endl;
    }
}

void Battle::playerUsePotion() {
    auto allPotions = potionManager->getAllPotions();
    if (allPotions.empty()) {
        cout << "You have no potions!" << endl;
        return;
    }
    
    cout << "Available potions:" << endl;
    vector<string> potionList;
    int index = 1;
    for (const auto& pair : allPotions) {
        cout << index << ". " << pair.first << " x" << pair.second << endl;
        potionList.push_back(pair.first);
        index++;
    }
    
    int choice;
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > (int)potionList.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Potion use cancelled." << endl;
        return;
    }
    
    string potionName = potionList[choice - 1];
    if (!potionManager->usePotion(potionName)) {
        cout << "Cannot use potion!" << endl;
        return;
    }
    
    if (potionName == "Strength Potion") {
        player->increaseMaxHealth(20);
        player->heal(20);
        cout << "You used Strength Potion! Max HP +20, Current HP +20" << endl;
    } else if (potionName == "Attacker Potion") {
        player->increaseAttack(5);
        cout << "You used Attacker Potion! Attack +5" << endl;
    } else if (potionName == "Life Potion") {
        player->heal(50);
        cout << "You used Life Potion! HP +50" << endl;
    } else if (potionName == "Mystery Potion") {
        player->increaseMaxHealth(40);
        player->heal(40);
        player->increaseAttack(10);
        cout << "You used Mystery Potion! Max HP +40, Current HP +40, Attack +10" << endl;
    }
}

void Battle::enemyTurn() {
    cout << "\n--- Enemy Turn ---" << endl;
    
    for (auto& enemy : enemies) {
        if (!enemy->isAlive() || !player->isAlive()) continue;
        
        if (enemy->getType() == "Boss") {
            bossAction(enemy.get());
        } else {
            int damage = enemy->getAttack();
            player->takeDamage(damage);
            cout << enemy->getName() << " attacks you for " << damage << " damage!" << endl;
        }
    }
}

void Battle::bossAction(Enemy* boss) {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
    
    // Count alive enemies (including boss)
    int aliveCount = 0;
    for (const auto& e : enemies) {
        if (e->isAlive()) aliveCount++;
    }
    
    if (aliveCount >= 3) {
        // Must attack if 3 enemies
        int damage = boss->getAttack();
        player->takeDamage(damage);
        cout << boss->getName() << " attacks you for " << damage << " damage!" << endl;
    } else if (aliveCount == 2) {
        // 50% attack, 50% summon Goust
        int roll = rand() % 2;
        if (roll == 0) {
            int damage = boss->getAttack();
            player->takeDamage(damage);
            cout << boss->getName() << " attacks you for " << damage << " damage!" << endl;
        } else {
            // Summon Goust (if not at max)
            if (enemies.size() < 3) {
                enemies.push_back(make_unique<Goust>());
                cout << boss->getName() << " summons a Goust!" << endl;
            } else {
                int damage = boss->getAttack();
                player->takeDamage(damage);
                cout << boss->getName() << " attacks you for " << damage << " damage!" << endl;
            }
        }
    } else {
        // Only boss alive: 34% attack, 33% summon 2 Batho, 33% summon Goust
        int roll = rand() % 100;
        if (roll < 34) {
            int damage = boss->getAttack();
            player->takeDamage(damage);
            cout << boss->getName() << " attacks you for " << damage << " damage!" << endl;
        } else if (roll < 67) {
            // Summon 2 Batho
            int canAdd = 3 - enemies.size();
            int toAdd = (canAdd > 2) ? 2 : canAdd;
            for (int i = 0; i < toAdd; i++) {
                enemies.push_back(make_unique<Batho>());
            }
            cout << boss->getName() << " summons " << toAdd << " Batho(s)!" << endl;
        } else {
            // Summon Goust
            if (enemies.size() < 3) {
                enemies.push_back(make_unique<Goust>());
                cout << boss->getName() << " summons a Goust!" << endl;
            } else {
                int damage = boss->getAttack();
                player->takeDamage(damage);
                cout << boss->getName() << " attacks you for " << damage << " damage!" << endl;
            }
        }
    }
}

void Battle::removeDeadEnemies() {
    enemies.erase(
        remove_if(enemies.begin(), enemies.end(),
            [](const unique_ptr<Enemy>& e) { return !e->isAlive(); }),
        enemies.end()
    );
}

bool Battle::isWon() const {
    for (const auto& enemy : enemies) {
        if (enemy->isAlive()) {
            return false;
        }
    }
    return true;
}

bool Battle::isLost() const {
    return !player->isAlive() || turnCount > 50;
}

int Battle::getTurnCount() const {
    return turnCount;
}

