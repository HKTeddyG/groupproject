#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "potion.h"
#include "battle.h"
#include "level.h"
#include "event.h"
#include "shop.h"
#include "save.h"

/**
 * @brief Main game controller class
 * 
 * This class manages the overall game flow, level progression,
 * difficulty selection, and coordinates all game systems.
 */
class Game {
private:
    Player* player;
    PotionManager* potionManager;
    EventManager* eventManager;
    Shop* shop;
    SaveManager* saveManager;
    
    int currentLevel;
    int difficulty; // 0 = easy, 1 = hard
    bool gameOver;
    bool gameWon;
    
    // Battle modifiers from negative events (hard mode only)
    bool enemyDoubleHP;           // Next battle enemies have double HP
    std::string disabledEquipment; // Name of disabled equipment (empty if none)
    
    /**
     * @brief Display main menu
     */
    void displayMainMenu() const;
    
    /**
     * @brief Get random equipment type
     * @return Name of random equipment
     */
    std::string getRandomEquipment() const;
    
    /**
     * @brief Select difficulty level
     * @return Selected difficulty (0=easy, 1=hard)
     */
    int selectDifficulty();
    
    /**
     * @brief Start new game
     */
    void startNewGame();
    
    /**
     * @brief Load existing game
     */
    void loadGame();
    
    /**
     * @brief Main game loop
     */
    void gameLoop();
    
    /**
     * @brief Process a battle level
     * @param level Level object containing level information
     * @return true if player won, false if player lost
     */
    bool processBattleLevel(const Level& level);
    
    /**
     * @brief Process an event level
     * @param level Level object containing level information
     */
    void processEventLevel(const Level& level);
    
    /**
     * @brief Display player status
     */
    void displayPlayerStatus() const;
    
    /**
     * @brief Handle level completion rewards
     */
    void handleLevelRewards();
    
    /**
     * @brief Handle game completion
     */
    void handleGameCompletion();
    
public:
    /**
     * @brief Constructor - Initializes game systems
     */
    Game();
    
    /**
     * @brief Destructor - Cleans up game resources
     */
    ~Game();
    
    /**
     * @brief Start the game
     */
    void run();
};

#endif // GAME_H

