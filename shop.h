#ifndef SHOP_H
#define SHOP_H

#include "player.h"

class Shop {
private:
    // What it does: Displays available items in shop menu
    // Inputs: None
    // Outputs: None
    void displayItems() const;
    
public:
    // What it does: Initializes shop
    // Inputs: None
    // Outputs: None
    Shop();
    
    // What it does: Cleans up shop resources
    // Inputs: None
    // Outputs: None
    ~Shop();
    
    // What it does: Opens shop menu and handles purchases
    // Inputs: player - pointer to player object
    // Outputs: Returns true if player wants to continue, false if they want to exit
    bool open(Player* player);
    
    // What it does: Processes item purchase and applies effects to player
    // Inputs: player - pointer to player object, itemName - name of item to purchase
    // Outputs: Returns true if purchase was successful, false otherwise
    bool purchaseItem(Player* player, const std::string& itemName);
};

#endif
