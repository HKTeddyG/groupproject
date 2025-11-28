#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include "potion.h"
#include <string>
#include <vector>

/**
 * @brief Manages save and load functionality for game state
 * 
 * This class handles saving game progress to a file and loading
 * it back, including player stats, equipment, potions, and level progress.
 */
class SaveManager {
private:
    std::string saveFileName; // Name of save file
    
public:
    /**
     * @brief Constructor - Initializes save manager with filename
     * @param filename Name of save file (default: "savegame.txt")
     */
    SaveManager(const std::string& filename = "savegame.txt");
    
    /**
     * @brief Destructor - Cleans up save manager resources
     */
    ~SaveManager();
    
    /**
     * @brief Save game state to file
     * @param player Pointer to player object
     * @param potionManager Pointer to potion manager
     * @param currentLevel Current level number
     * @param difficulty Difficulty mode (0=easy, 1=hard)
     * @return true if save was successful, false otherwise
     */
    bool saveGame(Player* player, PotionManager* potionManager, int currentLevel, int difficulty);
    
    /**
     * @brief Load game state from file
     * @param player Pointer to player object (will be modified)
     * @param potionManager Pointer to potion manager (will be modified)
     * @param currentLevel Reference to store loaded level number
     * @param difficulty Reference to store loaded difficulty mode
     * @return true if load was successful, false otherwise
     */
    bool loadGame(Player* player, PotionManager* potionManager, int& currentLevel, int& difficulty);
    
    /**
     * @brief Check if save file exists
     * @return true if save file exists, false otherwise
     */
    bool saveExists() const;
    
    /**
     * @brief Delete save file
     * @return true if deletion was successful, false otherwise
     */
    bool deleteSave();
};

#endif // SAVE_H

