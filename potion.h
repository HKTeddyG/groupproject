#ifndef POTION_H
#define POTION_H

#include <string>
#include <map>
#include <vector>

class PotionManager {
private:
    std::map<std::string, int> potions;
    
public:
    // What it does: Initializes empty potion inventory
    // Inputs: None
    // Outputs: None
    PotionManager();
    
    // What it does: Cleans up potion resources
    // Inputs: None
    // Outputs: None
    ~PotionManager();
    
    // What it does: Adds potion to inventory with specified quantity
    // Inputs: potionName - name of potion to add, quantity - number of potions to add (default 1)
    // Outputs: None
    void addPotion(const std::string& potionName, int quantity = 1);
    
    // What it does: Removes one potion from inventory
    // Inputs: potionName - name of potion to use
    // Outputs: Returns true if potion was used, false if not available
    bool usePotion(const std::string& potionName);
    
    // What it does: Returns quantity of specific potion in inventory
    // Inputs: potionName - name of potion to check
    // Outputs: Number of that potion in inventory (int)
    int getQuantity(const std::string& potionName) const;
    
    // What it does: Returns all potions in inventory as a map
    // Inputs: None
    // Outputs: Map of potion names and quantities
    std::map<std::string, int> getAllPotions() const;
    
    // What it does: Checks if potion exists in inventory
    // Inputs: potionName - name of potion to check
    // Outputs: Returns true if potion exists, false otherwise
    bool hasPotion(const std::string& potionName) const;
    
    // What it does: Returns list of all available potion types
    // Inputs: None
    // Outputs: Vector of potion names
    static std::vector<std::string> getPotionTypes();
    
    // What it does: Returns a random potion type name
    // Inputs: None
    // Outputs: Name of random potion (string)
    static std::string getRandomPotion();
};

#endif
