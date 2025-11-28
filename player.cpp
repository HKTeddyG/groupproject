#include "player.h"
#include <algorithm>
using namespace std;

Player::Player() : maxHealth(100), currentHealth(100), baseAttack(25), 
                   gold(0), bossAttackBonus(0), extraActions(0), disabledEquipment("") {
    equipment.clear();
}

Player::~Player() {
    equipment.clear();
}

int Player::getCurrentHealth() const {
    return currentHealth;
}

int Player::getMaxHealth() const {
    int totalMaxHealth = maxHealth;
    int armorCount = countEquipment("Armor");
    if (disabledEquipment != "Armor") {
        totalMaxHealth += armorCount * 100;
    }
    return totalMaxHealth;
}

int Player::getAttack() const {
    int totalAttack = baseAttack;
    int swordCount = countEquipment("Sword");
    // Each sword increases attack by 50% of base
    if (disabledEquipment != "Sword") {
        totalAttack += (int)(baseAttack * 0.5 * swordCount);
    }
    totalAttack += bossAttackBonus;
    return totalAttack;
}

int Player::getGold() const {
    return gold;
}

int Player::getBossAttackBonus() const {
    return bossAttackBonus;
}

void Player::takeDamage(int damage) {
    int shieldCount = countEquipment("Shield");
    double reductionFactor = 1.0;
    if (disabledEquipment != "Shield") {
        for (int i = 0; i < shieldCount; i++) {
            reductionFactor *= 0.5;
        }
    }
    int actualDamage = (int)(damage * reductionFactor);
    currentHealth -= actualDamage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}

void Player::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > getMaxHealth()) {
        currentHealth = getMaxHealth();
    }
}

void Player::restoreToFull() {
    currentHealth = getMaxHealth();
}

bool Player::addEquipment(const std::string& equipName) {
    if (equipment.size() >= 3) {
        return false;
    }
    equipment.push_back(equipName);
    
    // Update extra actions if Shoes are added
    if (equipName == "Shoes") {
        extraActions++;
    }
    
    return true;
}

std::vector<std::string> Player::getEquipment() const {
    return equipment;
}

bool Player::hasEquipment(const std::string& equipName) const {
    return std::find(equipment.begin(), equipment.end(), equipName) != equipment.end();
}

int Player::countEquipment(const std::string& equipName) const {
    int count = 0;
    for (const auto& equip : equipment) {
        if (equip == equipName) {
            count++;
        }
    }
    return count;
}

int Player::getExtraActions() const {
    return extraActions;
}

void Player::setExtraActions(int actions) {
    extraActions = actions;
}

void Player::useExtraAction() {
    if (extraActions > 0) {
        extraActions--;
    }
}

void Player::increaseMaxHealth(int amount) {
    maxHealth += amount;
    currentHealth += amount; // Also increase current health
}

void Player::increaseAttack(int amount) {
    baseAttack += amount;
}

void Player::addGold(int amount) {
    gold += amount;
}

bool Player::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Player::addBossAttackBonus(int amount) {
    bossAttackBonus += amount;
}

void Player::setBaseMaxHealth(int health) {
    maxHealth = health;
}

void Player::setBaseAttack(int attack) {
    baseAttack = attack;
}

void Player::setCurrentHealth(int health) {
    currentHealth = health;
    if (currentHealth > getMaxHealth()) {
        currentHealth = getMaxHealth();
    }
}

void Player::setGold(int amount) {
    gold = amount;
}

void Player::setBossAttackBonus(int bonus) {
    bossAttackBonus = bonus;
}

void Player::clearEquipment() {
    equipment.clear();
    extraActions = 0;
}

int Player::getBaseMaxHealth() const {
    return maxHealth;
}

int Player::getBaseAttack() const {
    return baseAttack;
}

void Player::setDisabledEquipment(const std::string& equipName) {
    disabledEquipment = equipName;
}

std::string Player::getDisabledEquipment() const {
    return disabledEquipment;
}

bool Player::isAlive() const {
    return currentHealth > 0;
}

