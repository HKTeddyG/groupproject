#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

class Level {
private:
    int levelNumber;
    std::string levelType;
    std::vector<std::string> enemies;
    
public:
    // What it does: Creates a level with given number, type, and enemy types
    // Inputs: number - level number (1-12), type - level type ("battle" or "event"), enemyTypes - vector of enemy types for battle levels
    // Outputs: None
    Level(int number, const std::string& type, const std::vector<std::string>& enemyTypes);
    
    // What it does: Cleans up level resources
    // Inputs: None
    // Outputs: None
    ~Level();
    
    // What it does: Returns level number
    // Inputs: None
    // Outputs: Level number (1-12) (int)
    int getNumber() const;
    
    // What it does: Returns level type
    // Inputs: None
    // Outputs: Level type string ("battle" or "event")
    std::string getType() const;
    
    // What it does: Returns enemy types for battle level
    // Inputs: None
    // Outputs: Vector of enemy type strings
    std::vector<std::string> getEnemies() const;
    
    // What it does: Creates level definition based on level number
    // Inputs: levelNum - level number (1-12)
    // Outputs: Level object for the specified level
    static Level createLevel(int levelNum);
    
    // What it does: Returns total number of levels in the game
    // Inputs: None
    // Outputs: Total number of levels (12) (int)
    static int getTotalLevels();
};

#endif
