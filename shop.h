#ifndef SHOP_H
#define SHOP_H

#include "player.h"

/**
 * @brief Manages the shop system where players can purchase items
 * 
 * This class handles shop interactions, item purchasing, and permanent
 * stat upgrades using gold currency.
 */
class Shop {
private:
    /**
     * @brief Display available items in shop
     */
    void displayItems() const;
    
public:
    /**
     * @brief Constructor - Initializes shop
     */
    Shop();
    
    /**
     * @brief Destructor - Cleans up shop resources
     */
    ~Shop();
    
    /**
     * @brief Open shop menu and handle purchases
     * @param player Pointer to player object
     * @return true if player wants to continue, false if they want to exit
     */
    bool open(Player* player);
    
    /**
     * @brief Process item purchase
     * @param player Pointer to player object
     * @param itemName Name of item to purchase
     * @return true if purchase was successful, false otherwise
     */
    bool purchaseItem(Player* player, const std::string& itemName);
};

#endif // SHOP_H

