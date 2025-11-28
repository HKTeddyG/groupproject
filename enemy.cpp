#include "enemy.h"
using namespace std;

Enemy::Enemy(const std::string& name, int health, int attack) 
    : name(name), maxHealth(health), currentHealth(health), attack(attack) {
}

Enemy::~Enemy() {
}

std::string Enemy::getName() const {
    return name;
}

int Enemy::getCurrentHealth() const {
    return currentHealth;
}

int Enemy::getMaxHealth() const {
    return maxHealth;
}

int Enemy::getAttack() const {
    return attack;
}

void Enemy::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

bool Enemy::isAlive() const {
    return currentHealth > 0;
}

void Enemy::doubleHealth() {
    maxHealth *= 2;
    currentHealth *= 2;
}

// Slim implementation
Slim::Slim() : Enemy("Slim", 30, 10) {
}

std::string Slim::getType() const {
    return "Slim";
}

// Batho implementation
Batho::Batho() : Enemy("Batho", 60, 30) {
}

std::string Batho::getType() const {
    return "Batho";
}

// Goust implementation
Goust::Goust() : Enemy("Goust", 10, 80) {
}

std::string Goust::getType() const {
    return "Goust";
}

// Boss implementation
Boss::Boss() : Enemy("Boss", 300, 50) {
}

std::string Boss::getType() const {
    return "Boss";
}

