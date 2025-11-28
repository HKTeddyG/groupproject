#ifndef ENEMY_H
#define ENEMY_H

#include <string>

/**
 * @brief Base class for all enemy types in the game
 * 
 * This class represents enemies that the player will fight during battles.
 * Different enemy types inherit from this class.
 */
class Enemy {
protected:
    std::string name;       // Enemy name
    int maxHealth;          // Maximum health
    int currentHealth;      // Current health
    int attack;             // Attack damage
    
public:
    /**
     * @brief Constructor - Initializes enemy with given parameters
     * @param name Enemy name
     * @param health Enemy health
     * @param attack Enemy attack damage
     */
    Enemy(const std::string& name, int health, int attack);
    
    /**
     * @brief Destructor - Cleans up enemy resources
     */
    virtual ~Enemy();
    
    /**
     * @brief Get enemy name
     * @return Enemy name
     */
    std::string getName() const;
    
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
     * @brief Get attack damage
     * @return Attack damage value
     */
    int getAttack() const;
    
    /**
     * @brief Take damage
     * @param damage Amount of damage to take
     */
    void takeDamage(int damage);
    
    /**
     * @brief Check if enemy is alive
     * @return true if health > 0, false otherwise
     */
    bool isAlive() const;
    
    /**
     * @brief Double the enemy's maximum and current health
     */
    void doubleHealth();
    
    /**
     * @brief Get enemy type identifier
     * @return Enemy type string
     */
    virtual std::string getType() const = 0;
};

/**
 * @brief Slim enemy type - Weak enemy with low health and attack
 */
class Slim : public Enemy {
public:
    /**
     * @brief Constructor - Creates a Slim enemy
     */
    Slim();
    virtual std::string getType() const override;
};

/**
 * @brief Batho enemy type - Medium enemy with moderate health and attack
 */
class Batho : public Enemy {
public:
    /**
     * @brief Constructor - Creates a Batho enemy
     */
    Batho();
    virtual std::string getType() const override;
};

/**
 * @brief Goust enemy type - High damage but low health enemy
 */
class Goust : public Enemy {
public:
    /**
     * @brief Constructor - Creates a Goust enemy
     */
    Goust();
    virtual std::string getType() const override;
};

/**
 * @brief Boss enemy type - Final boss with special abilities
 */
class Boss : public Enemy {
public:
    /**
     * @brief Constructor - Creates a Boss enemy
     */
    Boss();
    virtual std::string getType() const override;
};

#endif // ENEMY_H

