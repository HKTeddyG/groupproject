#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#include "potion.h"
#include <string>

/**
 * @brief Manages random events that occur in event levels
 * 
 * This class handles event generation and execution, including
 * positive events and negative events (in hard difficulty).
 */
class EventManager {
private:
    bool isHardMode; // Whether game is in hard mode (allows negative events)
    
public:
    /**
     * @brief Constructor - Initializes event manager
     * @param hardMode true if hard difficulty, false if easy
     */
    EventManager(bool hardMode = false);
    
    /**
     * @brief Destructor - Cleans up event manager resources
     */
    ~EventManager();
    
    /**
     * @brief Execute a random event
     * @param player Pointer to player object
     * @param potionManager Pointer to potion manager
     * @param enemyDoubleHP Reference to set enemy double HP flag
     * @param disabledEquipment Reference to set disabled equipment name
     * @return Description of the event that occurred
     */
    std::string executeRandomEvent(Player* player, PotionManager* potionManager,
                                   bool& enemyDoubleHP, std::string& disabledEquipment);
    
    /**
     * @brief Execute a positive event
     * @param player Pointer to player object
     * @param potionManager Pointer to potion manager
     * @param eventNum Event number (1-4)
     * @return Description of the event
     */
    std::string executePositiveEvent(Player* player, PotionManager* potionManager, int eventNum);
    
    /**
     * @brief Execute a negative event (hard mode only)
     * @param player Pointer to player object
     * @param enemyDoubleHP Reference to set enemy double HP flag
     * @param disabledEquipment Reference to set disabled equipment name
     * @return Description of the event
     */
    std::string executeNegativeEvent(Player* player, bool& enemyDoubleHP, std::string& disabledEquipment);
    
    /**
     * @brief Set difficulty mode
     * @param hardMode true for hard mode, false for easy mode
     */
    void setHardMode(bool hardMode);
};

#endif // EVENT_H

