#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include "potion.h"
#include <string>
#include <vector>

class SaveManager {
private:
    std::string saveFileName;
    
public:
    // What it does: Initializes save manager with filename
    // Inputs: filename - name of save file (default: "savegame.txt")
    // Outputs: None
    SaveManager(const std::string& filename = "savegame.txt");
    
    // What it does: Cleans up save manager resources
    // Inputs: None
    // Outputs: None
    ~SaveManager();
    
    // What it does: Saves game state to file including player stats, equipment, potions, level, and difficulty
    // Inputs: player - pointer to player object, potionManager - pointer to potion manager, currentLevel - current level number, difficulty - difficulty mode (0=easy, 1=hard)
    // Outputs: Returns true if save was successful, false otherwise
    bool saveGame(Player* player, PotionManager* potionManager, int currentLevel, int difficulty);
    
    // What it does: Loads game state from file and restores player stats, equipment, potions, level, and difficulty
    // Inputs: player - pointer to player object (will be modified), potionManager - pointer to potion manager (will be modified), currentLevel - reference to store loaded level number, difficulty - reference to store loaded difficulty mode
    // Outputs: Returns true if load was successful, false otherwise
    bool loadGame(Player* player, PotionManager* potionManager, int& currentLevel, int& difficulty);
    
    // What it does: Checks if save file exists
    // Inputs: None
    // Outputs: Returns true if save file exists, false otherwise
    bool saveExists() const;
    
    // What it does: Deletes save file
    // Inputs: None
    // Outputs: Returns true if deletion was successful, false otherwise
    bool deleteSave();
};

#endif
