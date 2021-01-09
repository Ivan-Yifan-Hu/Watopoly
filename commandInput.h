#ifndef COMMAND_INPUT_H
#define COMMAND_INPUT_H

#include "Game.h"
#include <iostream>
#include <sstream>

// controller of the MVC model
class CommandInput {
    // shared pointer to the Game class
    std::shared_ptr<Game> game;
  public:
    // constructor
    CommandInput(std::shared_ptr<Game> game);
    // takes in commandline input and process it
    void readInput(std::istream & in, bool testing);
    // handles the sitution of building purchase
    void purchaseOrNot(std::istream & in, std::string building);
    // handles the sitution of aution
    void auction(std::istream & in, std::string building);
    // handles the sitution when the player does not have enough money
    bool NotEnoughMoney(std::istream & in, int amount, std::string playerName, std::string toPlayer);
    // handles the sitution when the player is at Tim Hortons
    void TimHortons(std::istream & in, int currentRound);
    // handles the sitution when the player is at Tuition
    void payTuition(std::istream & in);
};

#endif
