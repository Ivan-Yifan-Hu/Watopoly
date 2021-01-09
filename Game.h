#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Building.h"
#include "Property.h"
#include "NonProperty.h"
#include "Board.h"
#include "Dice.h"
#include "Exception.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>


// in charges of all workflow of Watopoly
// location where main game takes palce
class Game {
  private:
  bool hasRolled;
  // stores all buildings in vector
    std::vector<std::shared_ptr<Building>> buildings;
  // stores all players in vector
    std::vector<std::shared_ptr<Player>> players;
  // current player
    std::vector<std::shared_ptr<Player>>::iterator currentPlayer;
  // shared pointer to Board class
    std::shared_ptr<Board> board;
  // shared pointer to Dice class
    std::shared_ptr<Dice> dice;
  // shared pointer to RimCup class
    std::shared_ptr<RimCup> rimcup;
  public:
  // constructor
    Game(std::map<std::string, std::string> player_names);
    Game(std::ifstream & file);
    std::shared_ptr<Board> getBoard();
    std::string currentPlayerName();
    int currentTimRound();
  // updates currentPlayer field
    void nextPlayer();
  // updates current player's location
    void movePlayer(int steps);
  // find the player with given name
    std::shared_ptr<Player> findPlayer(std::string s);
  // find the building with given name
    std::shared_ptr<Building> findBuilding(std::string name);
  // allows the current player to pruchase building
    void purchase(std::string buildingName);
  // allows players to trade building
    void tradeBuilding(std::string buildingName, std::string receiver);
    void tradeBuilding(std::string giver, std::string receiver, std::string buildingName);
  // allows the current player to trade with others
    void trade(std::string receiver, int giveAmount, std::string buildingName);
    void trade(std::string receiver, std::string buildingName, int receiveAmount);
    void trade(std::string receiver, std::string giveBuildingName, std::string receiveBuildingName);
    int sellImprovement(std::string playerName, std::string buildingName);
    void buyImprovement(std::string buildingName);
  // mortgage building 
    int mortgage(std::string playerName, std::string buildingName);
  // unmortgage building
    void unmortgage(std::string buildingName);
  // allows player to declares bankrupcy
    void bankrupt(std::string playerName, std::string bankruptTo);
  // save game into a file
    void saveGame(std::ofstream & file);
  // displays the current state of the board
    void drawBoard();
  // roll dice
    int roll();
    void setRolled(bool roll);
    bool getRolled();
  // determines if the player has rolled doubles
    bool rollDouble();
  // allows the current player to use Rim Cup to get out of the DC Tims Line
    void useRimCup();
  // allows the current player to pay $50 to get out of the DC Tims Line
    void buyCoffee();
  // current player leaves the DC Tims Line
    void leaveLine();
  // current player's Tim Round plus one
    void stayInLine();
  // prints message
    void printMessage(std::string message);
  // returns total assets of the given player
    int totalAsset(std::string playerName);
  // displays assets of the current player
    void asset();
    void howToPayTuition(std::string option);
    std::vector<std::string> getPlayerNames();
    void allassets();
    int getCurrentPosition();
};

#endif
