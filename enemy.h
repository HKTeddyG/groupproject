#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
protected:
    std::string name;
    int maxHealth;
    int currentHealth;
    int attack;
    
public:
    // What it does: Initializes enemy with given name, health, and attack values
    // Inputs: name - enemy name, health - enemy health, attack - enemy attack damage
    // Outputs: None
    Enemy(const std::string& name, int health, int attack);
    
    // What it does: Cleans up enemy resources
    // Inputs: None
    // Outputs: None
    virtual ~Enemy();
    
    // What it does: Returns enemy name
    // Inputs: None
    // Outputs: Enemy name (string)
    std::string getName() const;
    
    // What it does: Returns current health value
    // Inputs: None
    // Outputs: Current health value (int)
    int getCurrentHealth() const;
    
    // What it does: Returns maximum health value
    // Inputs: None
    // Outputs: Maximum health value (int)
    int getMaxHealth() const;
    
    // What it does: Returns attack damage value
    // Inputs: None
    // Outputs: Attack damage value (int)
    int getAttack() const;
    
    // What it does: Reduces enemy health by damage amount
    // Inputs: damage - amount of damage to take
    // Outputs: None
    void takeDamage(int damage);
    
    // What it does: Checks if enemy is alive
    // Inputs: None
    // Outputs: Returns true if health > 0, false otherwise
    bool isAlive() const;
    
    // What it does: Doubles the enemy's maximum and current health
    // Inputs: None
    // Outputs: None
    void doubleHealth();
    
    // What it does: Returns enemy type identifier (pure virtual function)
    // Inputs: None
    // Outputs: Enemy type string
    virtual std::string getType() const = 0;
};

class Slim : public Enemy {
public:
    // What it does: Creates a Slim enemy with 30 HP and 10 attack
    // Inputs: None
    // Outputs: None
    Slim();
    
    // What it does: Returns enemy type as "Slim"
    // Inputs: None
    // Outputs: Enemy type string "Slim"
    virtual std::string getType() const override;
};

class Batho : public Enemy {
public:
    // What it does: Creates a Batho enemy with 60 HP and 30 attack
    // Inputs: None
    // Outputs: None
    Batho();
    
    // What it does: Returns enemy type as "Batho"
    // Inputs: None
    // Outputs: Enemy type string "Batho"
    virtual std::string getType() const override;
};

class Goust : public Enemy {
public:
    // What it does: Creates a Goust enemy with 10 HP and 80 attack
    // Inputs: None
    // Outputs: None
    Goust();
    
    // What it does: Returns enemy type as "Goust"
    // Inputs: None
    // Outputs: Enemy type string "Goust"
    virtual std::string getType() const override;
};

class Boss : public Enemy {
public:
    // What it does: Creates a Boss enemy with 300 HP and 50 attack
    // Inputs: None
    // Outputs: None
    Boss();
    
    // What it does: Returns enemy type as "Boss"
    // Inputs: None
    // Outputs: Enemy type string "Boss"
    virtual std::string getType() const override;
};

#endif
