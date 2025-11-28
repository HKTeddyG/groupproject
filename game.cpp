#include "game.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

Game::Game() : currentLevel(1), difficulty(0), gameOver(false), gameWon(false),
               enemyDoubleHP(false), disabledEquipment("") {
    player = new Player();
    potionManager = new PotionManager();
    eventManager = new EventManager(false);
    shop = new Shop();
    saveManager = new SaveManager();
    
    srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game() {
    delete player;
    delete potionManager;
    delete eventManager;
    delete shop;
    delete saveManager;
}

void Game::run() {
    while (!gameOver) {
        displayMainMenu();
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                startNewGame();
                break;
            case 2:
                if (saveManager->saveExists()) {
                    loadGame();
                } else {
                    cout << "No save file found!" << endl;
                }
                break;
            case 3:
                cout << "Thank you for playing! Goodbye!" << endl;
                gameOver = true;
                break;
            default:
                cout << "Invalid choice. Please select 1-3." << endl;
                break;
        }
    }
}

void Game::displayMainMenu() const {
    cout << "\n========================================" << endl;
    cout << "      TEXT-BASED RPG GAME" << endl;
    cout << "========================================" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Select option (1-3): ";
}

int Game::selectDifficulty() {
    cout << "\n=== Select Difficulty ===" << endl;
    cout << "1. Easy (Player acts first)" << endl;
    cout << "2. Hard (Enemy acts first, negative events possible)" << endl;
    cout << "Select difficulty (1-2): ";
    
    int choice;
    cin >> choice;
    
    if (cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Defaulting to Easy." << endl;
        return 0;
    }
    
    return choice - 1;
}

void Game::startNewGame() {
    delete player;
    delete potionManager;
    player = new Player();
    potionManager = new PotionManager();
    
    currentLevel = 1;
    difficulty = selectDifficulty();
    eventManager->setHardMode(difficulty == 1);
    gameWon = false;
    enemyDoubleHP = false;
    disabledEquipment = "";
    
    cout << "\n=== New Game Started ===" << endl;
    cout << "Difficulty: " << (difficulty == 0 ? "Easy" : "Hard") << endl;
    cout << "Your journey begins..." << endl;
    
    gameLoop();
}

void Game::loadGame() {
    cout << "\nLoading game..." << endl;
    
    delete player;
    delete potionManager;
    player = new Player();
    potionManager = new PotionManager();
    
    if (saveManager->loadGame(player, potionManager, currentLevel, difficulty)) {
        eventManager->setHardMode(difficulty == 1);
        cout << "Game loaded successfully!" << endl;
        cout << "Current Level: " << currentLevel << endl;
        cout << "Difficulty: " << (difficulty == 0 ? "Easy" : "Hard") << endl;
        gameLoop();
    } else {
        cout << "Failed to load game!" << endl;
    }
}

void Game::gameLoop() {
    while (currentLevel <= Level::getTotalLevels() && !gameOver) {
        cout << "\n========================================" << endl;
        cout << "           LEVEL " << currentLevel << "/" << Level::getTotalLevels() << endl;
        cout << "========================================" << endl;
        
        displayPlayerStatus();
        
        Level level = Level::createLevel(currentLevel);
        
        if (level.getType() == "battle") {
            bool won = processBattleLevel(level);
            if (!won) {
                cout << "\nGame Over! You have been defeated." << endl;
                cout << "You reached Level " << currentLevel << "." << endl;
                gameOver = true;
                break;
            }
            handleLevelRewards();
        } else if (level.getType() == "event") {
            processEventLevel(level);
        }
        
        if (currentLevel > Level::getTotalLevels()) {
            handleGameCompletion();
            break;
        }
        
        cout << "\n=== What would you like to do? ===" << endl;
        cout << "1. Continue to next level" << endl;
        cout << "2. Save game" << endl;
        cout << "3. Visit shop" << endl;
        cout << "4. Exit game" << endl;
        cout << "Select option (1-4): ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 1;
        }
        
        switch (choice) {
            case 1:
                currentLevel++;
                break;
            case 2:
                if (saveManager->saveGame(player, potionManager, currentLevel, difficulty)) {
                    cout << "Game saved successfully!" << endl;
                } else {
                    cout << "Failed to save game!" << endl;
                }
                break;
            case 3:
                shop->open(player);
                break;
            case 4:
                gameOver = true;
                break;
            default:
                currentLevel++;
                break;
        }
    }
}

bool Game::processBattleLevel(const Level& level) {
    cout << "\n=== BATTLE LEVEL ===" << endl;
    cout << "Enemies: ";
    auto enemies = level.getEnemies();
    for (size_t i = 0; i < enemies.size(); i++) {
        cout << enemies[i];
        if (i < enemies.size() - 1) cout << ", ";
    }
    cout << endl;
    
    if (enemyDoubleHP) {
        cout << "Warning: Enemies have double HP in this battle!" << endl;
    }
    if (!disabledEquipment.empty()) {
        cout << "Warning: Your " << disabledEquipment << " equipment is disabled in this battle!" << endl;
    }
    
    bool playerFirst = (difficulty == 0);
    Battle battle(player, potionManager, enemies, playerFirst, enemyDoubleHP, disabledEquipment);
    bool won = battle.execute();
    
    enemyDoubleHP = false;
    disabledEquipment = "";
    
    return won;
}

void Game::processEventLevel(const Level& level) {
    cout << "\n=== EVENT LEVEL ===" << endl;
    string eventDescription = eventManager->executeRandomEvent(player, potionManager, 
                                                                 enemyDoubleHP, disabledEquipment);
    cout << eventDescription << endl;
    
    displayPlayerStatus();
}

void Game::displayPlayerStatus() const {
    cout << "\n=== Player Status ===" << endl;
    cout << "HP: " << player->getCurrentHealth() << "/" << player->getMaxHealth() << endl;
    cout << "Attack: " << player->getAttack() << endl;
    cout << "Gold: " << player->getGold() << endl;
    
    auto equipment = player->getEquipment();
    if (!equipment.empty()) {
        cout << "Equipment: ";
        for (size_t i = 0; i < equipment.size(); i++) {
            cout << equipment[i];
            if (i < equipment.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    
    auto potions = potionManager->getAllPotions();
    if (!potions.empty()) {
        cout << "Potions: ";
        bool first = true;
        for (const auto& pair : potions) {
            if (!first) cout << ", ";
            cout << pair.first << " x" << pair.second;
            first = false;
        }
        cout << endl;
    }
    cout << "====================\n" << endl;
}

void Game::handleLevelRewards() {
    string randomPotion = PotionManager::getRandomPotion();
    potionManager->addPotion(randomPotion, 1);
    cout << "\n=== Level Complete! ===" << endl;
    cout << "Reward: " << randomPotion << " x1" << endl;
    
    if (currentLevel == 4 || currentLevel == 8) {
        string randomEquipment = getRandomEquipment();
        if (player->addEquipment(randomEquipment)) {
            cout << "Bonus Reward: " << randomEquipment << " equipment!" << endl;
        } else {
            cout << "Bonus Reward: " << randomEquipment << " equipment found, but your equipment inventory is full!" << endl;
        }
    }
}

string Game::getRandomEquipment() const {
    vector<string> equipmentTypes = {"Shield", "Sword", "Armor", "Shoes"};
    int index = rand() % equipmentTypes.size();
    return equipmentTypes[index];
}

void Game::handleGameCompletion() {
    cout << "\n========================================" << endl;
    cout << "        CONGRATULATIONS!" << endl;
    cout << "========================================" << endl;
    cout << "You have completed all 12 levels!" << endl;
    cout << "You earned 1 gold coin!" << endl;
    player->addGold(1);
    gameWon = true;
    
    cout << "\nWould you like to visit the shop? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        shop->open(player);
    }
    
    gameOver = true;
}
