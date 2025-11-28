#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#include "potion.h"
#include <string>

class EventManager {
private:
    bool isHardMode;
    
public:
    // What it does: Initializes event manager with difficulty mode
    // Inputs: hardMode - true if hard difficulty, false if easy
    // Outputs: None
    EventManager(bool hardMode = false);
    
    // What it does: Cleans up event manager resources
    // Inputs: None
    // Outputs: None
    ~EventManager();
    
    // What it does: Executes a random event (positive or negative in hard mode)
    // Inputs: player - pointer to player object, potionManager - pointer to potion manager, enemyDoubleHP - reference to set enemy double HP flag, disabledEquipment - reference to set disabled equipment name
    // Outputs: Description of the event that occurred (string)
    std::string executeRandomEvent(Player* player, PotionManager* potionManager,
                                   bool& enemyDoubleHP, std::string& disabledEquipment);
    
    // What it does: Executes a positive event (gives rewards to player)
    // Inputs: player - pointer to player object, potionManager - pointer to potion manager, eventNum - event number (1-4)
    // Outputs: Description of the event (string)
    std::string executePositiveEvent(Player* player, PotionManager* potionManager, int eventNum);
    
    // What it does: Executes a negative event (hard mode only, applies penalties)
    // Inputs: player - pointer to player object, enemyDoubleHP - reference to set enemy double HP flag, disabledEquipment - reference to set disabled equipment name
    // Outputs: Description of the event (string)
    std::string executeNegativeEvent(Player* player, bool& enemyDoubleHP, std::string& disabledEquipment);
    
    // What it does: Sets difficulty mode
    // Inputs: hardMode - true for hard mode, false for easy mode
    // Outputs: None
    void setHardMode(bool hardMode);
};

#endif
