#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "potion.h"
#include "battle.h"
#include "level.h"
#include "event.h"
#include "shop.h"
#include "save.h"

class Game {
private:
    Player* player;
    PotionManager* potionManager;
    EventManager* eventManager;
    Shop* shop;
    SaveManager* saveManager;
    
    int currentLevel;
    int difficulty;
    bool gameOver;
    bool gameWon;
    bool enemyDoubleHP;
    std::string disabledEquipment;
    
    // What it does: Displays main menu with options (New Game, Load Game, Exit)
    // Inputs: None
    // Outputs: None
    void displayMainMenu() const;
    
    // What it does: Returns a random equipment type name
    // Inputs: None
    // Outputs: Name of random equipment (string)
    std::string getRandomEquipment() const;
    
    // What it does: Prompts player to select difficulty level
    // Inputs: None
    // Outputs: Selected difficulty (0=easy, 1=hard) (int)
    int selectDifficulty();
    
    // What it does: Starts a new game, resets player and initializes game state
    // Inputs: None
    // Outputs: None
    void startNewGame();
    
    // What it does: Loads existing game from save file
    // Inputs: None
    // Outputs: None
    void loadGame();
    
    // What it does: Main game loop that processes levels until game over or completion
    // Inputs: None
    // Outputs: None
    void gameLoop();
    
    // What it does: Processes a battle level, executes battle and returns result
    // Inputs: level - Level object containing level information
    // Outputs: Returns true if player won, false if player lost
    bool processBattleLevel(const Level& level);
    
    // What it does: Processes an event level, executes random event
    // Inputs: level - Level object containing level information
    // Outputs: None
    void processEventLevel(const Level& level);
    
    // What it does: Displays player status including HP, attack, gold, equipment, and potions
    // Inputs: None
    // Outputs: None
    void displayPlayerStatus() const;
    
    // What it does: Handles level completion rewards (random potion and equipment for levels 4 and 8)
    // Inputs: None
    // Outputs: None
    void handleLevelRewards();
    
    // What it does: Handles game completion, awards gold and offers shop visit
    // Inputs: None
    // Outputs: None
    void handleGameCompletion();
    
public:
    // What it does: Initializes game systems and sets up random number generation
    // Inputs: None
    // Outputs: None
    Game();
    
    // What it does: Cleans up game resources and deallocates memory
    // Inputs: None
    // Outputs: None
    ~Game();
    
    // What it does: Starts the game and runs main menu loop
    // Inputs: None
    // Outputs: None
    void run();
};

#endif
