#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"
#include "enemy.h"
#include "potion.h"
#include <vector>
#include <memory>

/**
 * @brief Manages battle system and turn-based combat
 * 
 * This class handles all battle-related logic including turn order,
 * player actions, enemy actions, and battle outcome determination.
 */
class Battle {
private:
    Player* player;
    PotionManager* potionManager;
    std::vector<std::unique_ptr<Enemy>> enemies;
    bool playerTurnFirst;
    int turnCount;
    
    /**
     * @brief Display current battle status
     */
    void displayStatus() const;
    
    /**
     * @brief Handle player's turn
     * @return true if player wants to continue battle, false if they quit
     */
    bool playerTurn();
    
    /**
     * @brief Handle player attack action
     */
    void playerAttack();
    
    /**
     * @brief Handle player potion usage
     */
    void playerUsePotion();
    
    /**
     * @brief Handle enemy turn - all enemies act
     */
    void enemyTurn();
    
    /**
     * @brief Handle boss enemy special actions
     * @param boss Pointer to boss enemy
     */
    void bossAction(Enemy* boss);
    
    /**
     * @brief Remove dead enemies from the battle
     */
    void removeDeadEnemies();
    
    /**
     * @brief Check if battle is won
     * @return true if all enemies are dead, false otherwise
     */
    bool isWon() const;
    
    /**
     * @brief Check if battle is lost
     * @return true if player is dead or turn limit exceeded, false otherwise
     */
    bool isLost() const;
    
public:
    /**
     * @brief Constructor - Initializes battle with enemies
     * @param player Pointer to player object
     * @param potionManager Pointer to potion manager
     * @param enemyTypes Vector of enemy type strings to create
     * @param playerFirst true if player acts first, false if enemies act first
     * @param enemyDoubleHP true if enemies should have double HP
     * @param disabledEquip Name of disabled equipment (empty if none)
     */
    Battle(Player* player, PotionManager* potionManager, 
           const std::vector<std::string>& enemyTypes, bool playerFirst,
           bool enemyDoubleHP = false, const std::string& disabledEquip = "");
    
    /**
     * @brief Destructor - Cleans up battle resources
     */
    ~Battle();
    
    /**
     * @brief Start and execute the battle
     * @return true if player wins, false if player loses
     */
    bool execute();
    
    /**
     * @brief Get number of turns taken in battle
     * @return Turn count
     */
    int getTurnCount() const;
};

#endif // BATTLE_H

