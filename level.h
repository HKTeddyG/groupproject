#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

/**
 * @brief Manages level progression and level definitions
 * 
 * This class handles level data structure, level completion,
 * and determining what type of level (battle or event) each level is.
 */
class Level {
private:
    int levelNumber;                // Current level number (1-12)
    std::string levelType;          // "battle" or "event"
    std::vector<std::string> enemies; // Enemy types for battle levels
    
public:
    /**
     * @brief Constructor - Creates a level with given parameters
     * @param number Level number (1-12)
     * @param type Level type ("battle" or "event")
     * @param enemyTypes Vector of enemy types for battle levels
     */
    Level(int number, const std::string& type, const std::vector<std::string>& enemyTypes);
    
    /**
     * @brief Destructor - Cleans up level resources
     */
    ~Level();
    
    /**
     * @brief Get level number
     * @return Level number (1-12)
     */
    int getNumber() const;
    
    /**
     * @brief Get level type
     * @return Level type string ("battle" or "event")
     */
    std::string getType() const;
    
    /**
     * @brief Get enemy types for battle level
     * @return Vector of enemy type strings
     */
    std::vector<std::string> getEnemies() const;
    
    /**
     * @brief Create level definition based on level number
     * @param levelNum Level number (1-12)
     * @return Level object for the specified level
     */
    static Level createLevel(int levelNum);
    
    /**
     * @brief Get total number of levels
     * @return Total number of levels (12)
     */
    static int getTotalLevels();
};

#endif // LEVEL_H

