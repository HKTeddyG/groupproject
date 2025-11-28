# Makefile for Text-based RPG Game
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g
TARGET = game
SOURCES = main.cpp player.cpp enemy.cpp potion.cpp battle.cpp level.cpp event.cpp shop.cpp save.cpp game.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = player.h enemy.h potion.h battle.h level.h event.h shop.h save.h game.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run './game' to play."

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete."

# Rebuild everything
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild

