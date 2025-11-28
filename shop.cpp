#include "shop.h"
#include <iostream>
#include <limits>
using namespace std;

Shop::Shop() {
}

Shop::~Shop() {
}

void Shop::displayItems() const {
    cout << "\n=== SHOP ===" << endl;
    cout << "1. Hamburger - Permanently increase Max HP by 20 (Cost: 1 gold)" << endl;
    cout << "2. Coke - Permanently increase Attack by 10 (Cost: 1 gold)" << endl;
    cout << "3. Exit Shop" << endl;
    cout << "============\n" << endl;
}

bool Shop::open(Player* player) {
    while (true) {
        displayItems();
        cout << "Your gold: " << player->getGold() << endl;
        cout << "Your current stats:" << endl;
        cout << "  Max HP: " << player->getMaxHealth() << endl;
        cout << "  Attack: " << player->getAttack() << endl;
        cout << "\nSelect item to purchase (1-3): ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                if (purchaseItem(player, "Hamburger")) {
                    cout << "Purchase successful!" << endl;
                } else {
                    cout << "Purchase failed! Insufficient gold." << endl;
                }
                break;
            case 2:
                if (purchaseItem(player, "Coke")) {
                    cout << "Purchase successful!" << endl;
                } else {
                    cout << "Purchase failed! Insufficient gold." << endl;
                }
                break;
            case 3:
                cout << "Leaving shop..." << endl;
                return false;
            default:
                cout << "Invalid choice. Please select 1-3." << endl;
                break;
        }
    }
}

bool Shop::purchaseItem(Player* player, const std::string& itemName) {
    if (itemName == "Hamburger") {
        if (player->spendGold(1)) {
            player->increaseMaxHealth(20);
            player->heal(20);
            return true;
        }
    } else if (itemName == "Coke") {
        if (player->spendGold(1)) {
            player->increaseAttack(10);
            return true;
        }
    }
    return false;
}

