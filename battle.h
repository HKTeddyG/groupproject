#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"
#include "enemy.h"
#include "potion.h"
#include <vector>
#include <memory>

class Battle {
private:
    Player* player;
    PotionManager* potionManager;
    std::vector<std::unique_ptr<Enemy>> enemies;
    bool playerTurnFirst;
    int turnCount;
    
    // What it does: Displays current battle status including player HP and all enemy HP
    // Inputs: None
    // Outputs: None
    void displayStatus() const;
    
    // What it does: Handles player's turn, allowing player to choose action (attack, use potion, or skip)
    // Inputs: None
    // Outputs: Returns true if player wants to continue battle, false if they quit
    bool playerTurn();
    
    // What it does: Handles player attack action, allowing player to select target enemy
    // Inputs: None
    // Outputs: None
    void playerAttack();
    
    // What it does: Handles player potion usage, allowing player to select and use a potion
    // Inputs: None
    // Outputs: None
    void playerUsePotion();
    
    // What it does: Handles enemy turn where all alive enemies attack the player
    // Inputs: None
    // Outputs: None
    void enemyTurn();
    
    // What it does: Handles boss enemy special actions (attack or summon enemies)
    // Inputs: boss - pointer to boss enemy
    // Outputs: None
    void bossAction(Enemy* boss);
    
    // What it does: Removes dead enemies from the battle
    // Inputs: None
    // Outputs: None
    void removeDeadEnemies();
    
    // What it does: Checks if battle is won (all enemies are dead)
    // Inputs: None
    // Outputs: Returns true if all enemies are dead, false otherwise
    bool isWon() const;
    
    // What it does: Checks if battle is lost (player is dead or turn limit exceeded)
    // Inputs: None
    // Outputs: Returns true if player is dead or turn count > 50, false otherwise
    bool isLost() const;
    
public:
    // What it does: Initializes battle with enemies, sets turn order, and applies battle modifiers
    // Inputs: player - pointer to player object, potionManager - pointer to potion manager, enemyTypes - vector of enemy type strings to create, playerFirst - true if player acts first, enemyDoubleHP - true if enemies should have double HP, disabledEquip - name of disabled equipment (empty if none)
    // Outputs: None
    Battle(Player* player, PotionManager* potionManager, 
           const std::vector<std::string>& enemyTypes, bool playerFirst,
           bool enemyDoubleHP = false, const std::string& disabledEquip = "");
    
    // What it does: Cleans up battle resources
    // Inputs: None
    // Outputs: None
    ~Battle();
    
    // What it does: Starts and executes the battle, managing turns until victory or defeat
    // Inputs: None
    // Outputs: Returns true if player wins, false if player loses
    bool execute();
    
    // What it does: Returns number of turns taken in battle
    // Inputs: None
    // Outputs: Turn count (int)
    int getTurnCount() const;
};

#endif
