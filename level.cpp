#include "level.h"
using namespace std;

Level::Level(int number, const std::string& type, const std::vector<std::string>& enemyTypes)
    : levelNumber(number), levelType(type), enemies(enemyTypes) {
}

Level::~Level() {
}

int Level::getNumber() const {
    return levelNumber;
}

std::string Level::getType() const {
    return levelType;
}

std::vector<std::string> Level::getEnemies() const {
    return enemies;
}

Level Level::createLevel(int levelNum) {
    vector<string> enemies;
    string type;
    
    switch (levelNum) {
        case 1:
            type = "battle";
            enemies = {"Slim"};
            break;
        case 2:
            type = "battle";
            enemies = {"Slim", "Slim"};
            break;
        case 3:
            type = "event";
            break;
        case 4:
            type = "battle";
            enemies = {"Batho"};
            break;
        case 5:
            type = "battle";
            enemies = {"Batho", "Slim"};
            break;
        case 6:
            type = "battle";
            enemies = {"Batho", "Slim", "Slim"};
            break;
        case 7:
            type = "event";
            break;
        case 8:
            type = "battle";
            enemies = {"Batho", "Batho"};
            break;
        case 9:
            type = "battle";
            enemies = {"Batho", "Batho", "Slim"};
            break;
        case 10:
            type = "battle";
            enemies = {"Batho", "Batho", "Batho"};
            break;
        case 11:
            type = "event";
            break;
        case 12:
            type = "battle";
            enemies = {"Boss"};
            break;
        default:
            type = "battle";
            enemies = {};
            break;
    }
    
    return Level(levelNum, type, enemies);
}

int Level::getTotalLevels() {
    return 12;
}

