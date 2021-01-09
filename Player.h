#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Dice.h"
#include "Exception.h"

class Building;

class Player {
  // basic information of the player
  private:
    std::string name;
    std::string symbol;
    int money;
    std::map<std::string, int> properties;
    int position;
    int rimCup;
    int TimRound;
    std::shared_ptr<Dice> dice;
  // functions of player class
  public:
    Player(std::string name, std::string symbol, int position, std::shared_ptr<Dice> dice, int TimCup, int money, int TimRound);
    std::string getName();
    std::string getSymbol();
  // accessor
    int getMoney();
  // give money to others
    void giveMoney(std::shared_ptr<Player> other, int amount); // if other is nullptr, give money to bank, note exception
  // add money
    void addMoney(int amount);
  // returns building count of the given type
    unsigned int getProperties(std::string type);
    void addBuilding(std::string type);
    void loseBuilding(std::string type);
  // determines if the player has full monopoly of given type
    bool hasFullMonopoly(std::string type);
  // accessor
    int getPosition();
  // updates player position
    void move(int position);
  // visitor pattern function
    void visit(Building & b); // call b.accept(*this)
  // accessor and mutator for Rim Cup
    int getCup();
    void addCup();
    void removeCup(); // Note exception
  // accessor and mutator for Tim Round 
    int getTimRound();
    void stayInLine();
    void leaveLine();
  // returns a random number with uniform distribution between 1 to 6
  // mimics the function of dice
    int roll();
};

#endif
