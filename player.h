#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player {
private:
    int maxHealth;
    int currentHealth;
    int baseAttack;
    int gold;
    int bossAttackBonus;
    std::vector<std::string> equipment;
    int extraActions;
    std::string disabledEquipment;
    
public:
    // What it does: Initializes player with default values (100 health, 25 attack, 0 gold, empty equipment)
    // Inputs: None
    // Outputs: None
    Player();
    
    // What it does: Cleans up player resources
    // Inputs: None
    // Outputs: None
    ~Player();
    
    // What it does: Returns the current health value
    // Inputs: None
    // Outputs: Current health value (int)
    int getCurrentHealth() const;
    
    // What it does: Returns the maximum health value (including equipment bonuses)
    // Inputs: None
    // Outputs: Maximum health value (int)
    int getMaxHealth() const;
    
    // What it does: Returns the total attack power (base attack + equipment bonuses + boss bonus)
    // Inputs: None
    // Outputs: Total attack damage (int)
    int getAttack() const;
    
    // What it does: Returns the gold currency amount
    // Inputs: None
    // Outputs: Gold amount (int)
    int getGold() const;
    
    // What it does: Returns the boss attack bonus
    // Inputs: None
    // Outputs: Boss attack bonus value (int)
    int getBossAttackBonus() const;
    
    // What it does: Reduces player health by damage amount (after applying shield reduction)
    // Inputs: damage - raw damage amount before reduction
    // Outputs: None
    void takeDamage(int damage);
    
    // What it does: Restores player health by specified amount (capped at max health)
    // Inputs: amount - amount of health to restore
    // Outputs: None
    void heal(int amount);
    
    // What it does: Restores player health to maximum
    // Inputs: None
    // Outputs: None
    void restoreToFull();
    
    // What it does: Adds equipment to player inventory (maximum 3 pieces)
    // Inputs: equipName - name of equipment to add
    // Outputs: Returns true if equipment was added, false if inventory is full
    bool addEquipment(const std::string& equipName);
    
    // What it does: Returns list of all equipped items
    // Inputs: None
    // Outputs: Vector of equipment names
    std::vector<std::string> getEquipment() const;
    
    // What it does: Checks if player has specific equipment
    // Inputs: equipName - name of equipment to check
    // Outputs: Returns true if player has the equipment, false otherwise
    bool hasEquipment(const std::string& equipName) const;
    
    // What it does: Counts number of specific equipment pieces
    // Inputs: equipName - name of equipment to count
    // Outputs: Number of that equipment type (int)
    int countEquipment(const std::string& equipName) const;
    
    // What it does: Returns number of extra actions available (from Shoes equipment)
    // Inputs: None
    // Outputs: Number of extra actions (int)
    int getExtraActions() const;
    
    // What it does: Sets number of extra actions
    // Inputs: actions - number of extra actions
    // Outputs: None
    void setExtraActions(int actions);
    
    // What it does: Consumes one extra action
    // Inputs: None
    // Outputs: None
    void useExtraAction();
    
    // What it does: Permanently increases maximum health and current health
    // Inputs: amount - amount to increase max health by
    // Outputs: None
    void increaseMaxHealth(int amount);
    
    // What it does: Permanently increases base attack
    // Inputs: amount - amount to increase base attack by
    // Outputs: None
    void increaseAttack(int amount);
    
    // What it does: Adds gold to player's inventory
    // Inputs: amount - amount of gold to add
    // Outputs: None
    void addGold(int amount);
    
    // What it does: Spends gold if player has sufficient amount
    // Inputs: amount - amount of gold to spend
    // Outputs: Returns true if gold was spent, false if insufficient funds
    bool spendGold(int amount);
    
    // What it does: Adds boss attack bonus for boss battles
    // Inputs: amount - bonus attack amount for boss battles
    // Outputs: None
    void addBossAttackBonus(int amount);
    
    // What it does: Sets base maximum health (for save/load system)
    // Inputs: health - base maximum health value
    // Outputs: None
    void setBaseMaxHealth(int health);
    
    // What it does: Sets base attack (for save/load system)
    // Inputs: attack - base attack value
    // Outputs: None
    void setBaseAttack(int attack);
    
    // What it does: Sets current health (for save/load system)
    // Inputs: health - current health value
    // Outputs: None
    void setCurrentHealth(int health);
    
    // What it does: Sets gold amount (for save/load system)
    // Inputs: amount - gold amount
    // Outputs: None
    void setGold(int amount);
    
    // What it does: Sets boss attack bonus (for save/load system)
    // Inputs: bonus - boss attack bonus value
    // Outputs: None
    void setBossAttackBonus(int bonus);
    
    // What it does: Clears all equipment from inventory
    // Inputs: None
    // Outputs: None
    void clearEquipment();
    
    // What it does: Returns base maximum health (without equipment bonuses)
    // Inputs: None
    // Outputs: Base maximum health (int)
    int getBaseMaxHealth() const;
    
    // What it does: Returns base attack (without equipment/boss bonuses)
    // Inputs: None
    // Outputs: Base attack value (int)
    int getBaseAttack() const;
    
    // What it does: Sets disabled equipment for next battle (from negative events)
    // Inputs: equipName - name of equipment to disable (empty string to clear)
    // Outputs: None
    void setDisabledEquipment(const std::string& equipName);
    
    // What it does: Returns name of disabled equipment
    // Inputs: None
    // Outputs: Name of disabled equipment (empty string if none)
    std::string getDisabledEquipment() const;
    
    // What it does: Checks if player is alive
    // Inputs: None
    // Outputs: Returns true if health > 0, false otherwise
    bool isAlive() const;
};

#endif
