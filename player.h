#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

/**
 * @brief Represents the player character in the game
 * 
 * This class manages player attributes including health, attack, equipment,
 * potions inventory, and gold. It handles player actions during battles
 * and manages equipment slots (maximum 3).
 */
class Player {
private:
    int maxHealth;          // Maximum health value
    int currentHealth;      // Current health value
    int baseAttack;         // Base attack damage
    int gold;               // Gold currency
    int bossAttackBonus;    // Bonus attack for boss battles
    
    // Equipment system (max 3 pieces)
    std::vector<std::string> equipment;
    int extraActions;       // Extra actions from Shoes equipment
    std::string disabledEquipment; // Name of disabled equipment (empty if none)
    
public:
    /**
     * @brief Constructor - Initializes player with default values
     * 
     * Initializes player with 100 health, 25 attack, 0 gold, and empty equipment
     */
    Player();
    
    /**
     * @brief Destructor - Cleans up player resources
     */
    ~Player();
    
    /**
     * @brief Get current health
     * @return Current health value
     */
    int getCurrentHealth() const;
    
    /**
     * @brief Get maximum health
     * @return Maximum health value
     */
    int getMaxHealth() const;
    
    /**
     * @brief Get total attack power (base + equipment bonuses)
     * @return Total attack damage
     */
    int getAttack() const;
    
    /**
     * @brief Get gold amount
     * @return Gold currency amount
     */
    int getGold() const;
    
    /**
     * @brief Get boss attack bonus
     * @return Bonus attack for boss battles
     */
    int getBossAttackBonus() const;
    
    /**
     * @brief Take damage from enemy
     * @param damage Raw damage amount before reduction
     */
    void takeDamage(int damage);
    
    /**
     * @brief Heal player
     * @param amount Amount of health to restore
     */
    void heal(int amount);
    
    /**
     * @brief Restore health to maximum
     */
    void restoreToFull();
    
    /**
     * @brief Add equipment to player (max 3 pieces)
     * @param equipName Name of equipment to add
     * @return true if equipment was added, false if inventory is full
     */
    bool addEquipment(const std::string& equipName);
    
    /**
     * @brief Get list of equipped items
     * @return Vector of equipment names
     */
    std::vector<std::string> getEquipment() const;
    
    /**
     * @brief Check if player has specific equipment
     * @param equipName Name of equipment to check
     * @return true if player has the equipment, false otherwise
     */
    bool hasEquipment(const std::string& equipName) const;
    
    /**
     * @brief Count number of specific equipment pieces
     * @param equipName Name of equipment to count
     * @return Number of that equipment type
     */
    int countEquipment(const std::string& equipName) const;
    
    /**
     * @brief Get number of extra actions available
     * @return Number of extra actions (from Shoes)
     */
    int getExtraActions() const;
    
    /**
     * @brief Set number of extra actions
     * @param actions Number of extra actions
     */
    void setExtraActions(int actions);
    
    /**
     * @brief Consume one extra action
     */
    void useExtraAction();
    
    /**
     * @brief Increase maximum health permanently
     * @param amount Amount to increase max health by
     */
    void increaseMaxHealth(int amount);
    
    /**
     * @brief Increase base attack permanently
     * @param amount Amount to increase base attack by
     */
    void increaseAttack(int amount);
    
    /**
     * @brief Add gold
     * @param amount Amount of gold to add
     */
    void addGold(int amount);
    
    /**
     * @brief Spend gold
     * @param amount Amount of gold to spend
     * @return true if gold was spent, false if insufficient funds
     */
    bool spendGold(int amount);
    
    /**
     * @brief Add boss attack bonus
     * @param amount Bonus attack amount for boss battles
     */
    void addBossAttackBonus(int amount);
    
    /**
     * @brief Set base maximum health (for save/load)
     * @param health Base maximum health value
     */
    void setBaseMaxHealth(int health);
    
    /**
     * @brief Set base attack (for save/load)
     * @param attack Base attack value
     */
    void setBaseAttack(int attack);
    
    /**
     * @brief Set current health (for save/load)
     * @param health Current health value
     */
    void setCurrentHealth(int health);
    
    /**
     * @brief Set gold amount (for save/load)
     * @param amount Gold amount
     */
    void setGold(int amount);
    
    /**
     * @brief Set boss attack bonus (for save/load)
     * @param bonus Boss attack bonus value
     */
    void setBossAttackBonus(int bonus);
    
    /**
     * @brief Clear all equipment
     */
    void clearEquipment();
    
    /**
     * @brief Get base maximum health (without equipment bonuses)
     * @return Base maximum health
     */
    int getBaseMaxHealth() const;
    
    /**
     * @brief Get base attack (without equipment/boss bonuses)
     * @return Base attack value
     */
    int getBaseAttack() const;
    
    /**
     * @brief Set disabled equipment for next battle
     * @param equipName Name of equipment to disable (empty string to clear)
     */
    void setDisabledEquipment(const std::string& equipName);
    
    /**
     * @brief Get disabled equipment name
     * @return Name of disabled equipment (empty if none)
     */
    std::string getDisabledEquipment() const;
    
    /**
     * @brief Check if player is alive
     * @return true if health > 0, false otherwise
     */
    bool isAlive() const;
};

#endif // PLAYER_H

