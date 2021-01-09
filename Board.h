#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include "Property.h"

class CommandInput; // Forward declaration

// Board class that takes the role of view in MVC model 
class Board {
  // Stores the visual representation of the board in the form of strings
  std::vector<std::vector<std::string>> board;
  // Also stores the CommandInput class(controller module) of the MVC model
  CommandInput * command;

  public:
  // Constructor
  Board();
  // Returns a shared pointer to CommandInput
  CommandInput * getCommand();
  // Sets CommandInput
  void setCommand(CommandInput * c);
  // Updates the improvement information stored in the board 
  void updateImprovement(std::shared_ptr<Academic> academic);
  // Updates the player position information stored in the board
  void updatePlayer(int oldPosition, int newPosition, std::string playerName);
  void removePlayer(int position, std::string playerName);
  // Outputs message
  void printMessage(std::string message, std::ostream & out);
  // Outputs the visual representation of the baord
  void drawBoard(std::ostream & out);
};

#endif
