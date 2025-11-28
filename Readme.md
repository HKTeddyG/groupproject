# Fight to Monsters

## Team Members
Zihao Gao

## Application Description

Fight to Monsters is a text-based role-playing game (RPG) implemented in C++ that can be played in a Linux terminal environment. The game features a progression system with 12 levels, turn-based combat, equipment management, potion system, and a shop for permanent upgrades. Players must complete all 12 levels to win the game, with increasing difficulty as they progress.

## Features

### 1. Multiple Difficulty Levels
- **Easy Mode**: Player acts first in each turn, then enemies act. Only positive events occur.
- **Hard Mode**: Enemies act first in each turn, then player acts. Negative events can occur, making the game more challenging.

### 2. Turn-Based Combat System
- Each battle begins with full player health
- Turn order depends on difficulty level
- Player can choose to attack, use potions, or skip turn
- Battle ends when all enemies are defeated (victory) or player dies/loses after 50 turns (defeat)
- Maximum of 3 enemies can be present simultaneously in battle

### 3. Enemy Types
- **Slim**: Weak enemy with 30 HP and 10 attack
- **Batho**: Medium enemy with 60 HP and 30 attack
- **Goust**: High-damage enemy with 10 HP and 80 attack
- **Boss**: Final boss with 300 HP, 50 attack, and special summoning abilities

### 4. Equipment System
- Players can equip up to 3 pieces of equipment
- Equipment types:
  - **Shield**: Reduces incoming damage by 50% (stacks multiplicatively)
  - **Sword**: Increases attack damage by 50% of base attack per sword (stacks)
  - **Armor**: Increases maximum HP by 100 per armor (stacks)
  - **Shoes**: Grants one extra action per turn (stacks)
- Equipment effects stack when multiple pieces are equipped

### 5. Potion System
- **Strength Potion**: Permanently increases max HP by 20 and heals 20 HP
- **Attacker Potion**: Permanently increases attack by 5
- **Life Potion**: Restores 50 HP
- **Mystery Potion**: Permanently increases max HP by 40, heals 40 HP, and increases attack by 10
- Players receive a random potion after each battle victory

### 6. Level Progression (12 Levels)
- **Battle Levels**: Levels 1, 2, 4, 5, 6, 8, 9, 10, 12 (Boss)
- **Event Levels**: Levels 3, 7, 11
- Each level increases in difficulty with more or stronger enemies
- **Special Rewards**: Completing Level 4 and Level 8 awards an additional random piece of equipment

### 7. Event System
- **Positive Events**:
  1. Gain a random piece of equipment
  2. Gain +30 attack bonus for boss battle
  3. Nothing happens
  4. Receive Strength Potion, Attacker Potion, and Life Potion (one each)
- **Negative Events** (Hard Mode only):
  - Take damage from traps
  - Lose gold to thieves
  - **Enemies in next battle have double HP** (negative event 1)
  - **One random equipment disabled in next battle** (negative event 2)

### 8. Shop System
- Players earn 1 gold coin upon completing all 12 levels
- Shop items:
  - **Hamburger**: Permanently increases max HP by 20 (Cost: 1 gold)
  - **Coke**: Permanently increases attack by 10 (Cost: 1 gold)

### 9. Save/Load System
- Game automatically saves when exiting
- Load saved games to continue progress
- Saves player stats, equipment, potions, gold, and level progress

## Coding Requirements Implementation

### 1. Generation of Random Events
- **Location**: `event.cpp` (EventManager class)
- **Implementation**: The `executeRandomEvent()` function uses `std::rand()` to generate random events. In hard mode, there's a 30% chance of negative events. Positive events are randomly selected from 4 types. Random potions are also generated after battles using `PotionManager::getRandomPotion()`.

### 2. Data Structures for Storing Data
- **Location**: Multiple files
- **Implementation**: 
  - `std::vector<std::string>` for storing equipment (player.h/cpp)
  - `std::map<std::string, int>` for storing potions with quantities (potion.h/cpp)
  - `std::vector<std::unique_ptr<Enemy>>` for managing enemies in battles (battle.h/cpp)
  - Structures like Player, Enemy classes encapsulate related data

### 3. Dynamic Memory Management
- **Location**: `game.cpp`, `battle.cpp`
- **Implementation**: 
  - `Player*`, `PotionManager*`, etc. are dynamically allocated using `new` in Game constructor
  - `std::unique_ptr<Enemy>` is used for enemy management to automatically handle memory
  - All dynamically allocated memory is properly deallocated in destructors using `delete`

### 4. File Input/Output
- **Location**: `save.cpp` (SaveManager class)
- **Implementation**: 
  - `saveGame()` writes game state to `savegame.txt` using `std::ofstream`
  - `loadGame()` reads game state from file using `std::ifstream`
  - Saves player stats, equipment, potions, level progress, and difficulty setting

### 5. Program Codes in Multiple Files
- **Organization**: The project is split into logical modules:
  - `main.cpp`: Entry point
  - `player.h/cpp`: Player character management
  - `enemy.h/cpp`: Enemy class hierarchy
  - `potion.h/cpp`: Potion inventory management
  - `battle.h/cpp`: Battle system logic
  - `level.h/cpp`: Level definitions and progression
  - `event.h/cpp`: Random event system
  - `shop.h/cpp`: Shop system
  - `save.h/cpp`: Save/load functionality
  - `game.h/cpp`: Main game controller

### 6. Multiple Difficulty Levels
- **Location**: `game.cpp`, `event.cpp`, `battle.cpp`
- **Implementation**: 
  - Difficulty selection in `Game::selectDifficulty()`
  - Turn order changes based on difficulty (easy: player first, hard: enemy first)
  - Hard mode enables negative events in `EventManager`
  - Difficulty is saved and loaded with game state

## Non-Standard Libraries

**None**. This project uses only the C++ standard library (`<iostream>`, `<vector>`, `<map>`, `<string>`, `<fstream>`, `<cstdlib>`, `<ctime>`, `<memory>`, `<limits>`, `<sstream>`, `<algorithm>`, `<cstdio>`). All code is standard C++11 compliant and requires no additional library installation.

## Compilation and Execution Instructions

### Prerequisites
- A C++ compiler with C++11 support (g++ recommended)
- Make utility (for using Makefile)
- Linux/Unix environment (or compatible terminal)

### Compilation

1. Navigate to the project directory containing the source files and Makefile.

2. Compile the project using the provided Makefile:
   ```bash
   make
   ```

   Alternatively, compile manually:
   ```bash
   g++ -std=c++11 -Wall -Wextra -g -o game main.cpp player.cpp enemy.cpp potion.cpp battle.cpp level.cpp event.cpp shop.cpp save.cpp game.cpp
   ```

3. If compilation is successful, an executable named `game` will be created.

### Execution

1. Run the game:
   ```bash
   ./game
   ```

2. Follow the on-screen menu:
   - Select "1" to start a new game
   - Select "2" to load a saved game (if available)
   - Select "3" to exit (game will be saved automatically if you have progress)

3. If starting a new game:
   - Choose difficulty level (1 = Easy, 2 = Hard)
   - Play through 12 levels, defeating enemies and experiencing events
   - Visit the shop after completing all levels
   - Exit anytime and your progress will be saved automatically

### Game Controls

During gameplay:
- Follow on-screen prompts to select actions
- In battle: Choose attack, use potion, or skip
- When multiple enemies are present: Select target by number
- Between levels: Choose to continue, visit shop, or exit (auto-save)

### Clean Build

To remove compiled files and start fresh:
```bash
make clean
```

To clean and rebuild:
```bash
make rebuild
```

## Additional Notes

- Save files are stored as `savegame.txt` in the same directory as the executable
- The game uses random number generation for events and potion rewards
- Equipment effects stack (multiple shields, swords, etc.)
- Boss battles have special mechanics with enemy summoning
- All output text is in English as requested
