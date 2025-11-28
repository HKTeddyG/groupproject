#ifndef POTION_H
#define POTION_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Manages potion inventory and effects
 * 
 * This class handles all potion-related operations including storage,
 * usage, and effects during battles and events.
 */
class PotionManager {
private:
    // Map storing potion names and their quantities
    std::map<std::string, int> potions;
    
public:
    /**
     * @brief Constructor - Initializes empty potion inventory
     */
    PotionManager();
    
    /**
     * @brief Destructor - Cleans up potion resources
     */
    ~PotionManager();
    
    /**
     * @brief Add potion to inventory
     * @param potionName Name of potion to add
     * @param quantity Number of potions to add (default 1)
     */
    void addPotion(const std::string& potionName, int quantity = 1);
    
    /**
     * @brief Remove one potion from inventory
     * @param potionName Name of potion to use
     * @return true if potion was used, false if not available
     */
    bool usePotion(const std::string& potionName);
    
    /**
     * @brief Get quantity of specific potion
     * @param potionName Name of potion to check
     * @return Number of that potion in inventory
     */
    int getQuantity(const std::string& potionName) const;
    
    /**
     * @brief Get all potions in inventory
     * @return Map of potion names and quantities
     */
    std::map<std::string, int> getAllPotions() const;
    
    /**
     * @brief Check if potion exists in inventory
     * @param potionName Name of potion to check
     * @return true if potion exists, false otherwise
     */
    bool hasPotion(const std::string& potionName) const;
    
    /**
     * @brief Get list of all available potion types
     * @return Vector of potion names
     */
    static std::vector<std::string> getPotionTypes();
    
    /**
     * @brief Get random potion type
     * @return Name of random potion
     */
    static std::string getRandomPotion();
};

#endif // POTION_H

