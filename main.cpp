#include "game.h"
#include <iostream>
using namespace std;

// What it does: Main entry point for Fight to Monsters game. Initializes and runs the game.
// Inputs: None
// Outputs: Returns exit code (0 for successful execution)
int main() {
    Game game;
    game.run();
    return 0;
}
