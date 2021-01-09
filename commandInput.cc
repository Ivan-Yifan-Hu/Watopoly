#include "commandInput.h"
#include <fstream>
#include <algorithm>

CommandInput::CommandInput(std::shared_ptr<Game> game) : game{game} {
  game->getBoard()->setCommand(this);
}

void CommandInput::readInput(std::istream & in, bool testing) {
  game->drawBoard();
  game->printMessage("First player is " + game->currentPlayerName() + ".");
  std::string s;
  std::string line;
  int times = 0;
  try {
      while (in >> s) {
        if (s == "roll") {
          if (!game->getRolled()) {
            if (game->currentTimRound() != 0) {
              TimHortons(std::cin, game->currentTimRound());
              game->setRolled(true);
              continue;
            } else if (!testing) {
                int dice1 = game->roll();
                int dice2 = game->roll();
                if (dice1 != dice2) {
                  game->setRolled(true);
                  if ((dice1 + dice2 + game->getCurrentPosition()) > 40) {
                    game->movePlayer(40 - game->getCurrentPosition());
                    game->movePlayer(dice1 + dice2 + game->getCurrentPosition() - 40);
                    times = 0;
                  } else {
                    game->movePlayer(dice1 + dice2);
                    times = 0;
                  }
                } else if ((dice1 == dice2) && (times != 2)) {
                  game->printMessage("You rolled doubles! Please roll again ...");
                  times += 1;
                } else {
                  game->printMessage("You rolled doubles three times! You are moved to DC Tims Line :(");
                  game->setRolled(true);
                  int steps = 30 - game->getCurrentPosition();
                  game->movePlayer(steps);
                  times = 0;
                }
            } else {
                int dice1;
                int dice2;
                getline(in, line);
                std::istringstream ss1{line};
                if (!(ss1 >> dice1)) {
                    dice1 = game->roll();
                    dice2 = game->roll();
                    // game->movePlayer(dice1 + dice2);
                } else if (!(ss1 >> dice2)) {
                    // game->setRolled(true);
                    dice2 = game->roll();
                    // game->movePlayer(dice1 + dice2);
                } else {
                    // game->setRolled(true);
                    // game->movePlayer(dice1 + dice2);
                }
                game->setRolled(true);
                if ((dice1 + dice2 + game->getCurrentPosition()) > 40) {
                    game->movePlayer(40 - game->getCurrentPosition());
                    game->movePlayer(dice1 + dice2 + game->getCurrentPosition() - 40);
                    times = 0;
                  } else {
                    game->movePlayer(dice1 + dice2);
                    times = 0;
                  }
            }
            game->drawBoard();
          } else {
            game->printMessage("You have already rolled!");
          }
        } else if (s == "next") {
          game->nextPlayer();
          game->setRolled(false);
        } else if (s == "assets") {
          game->asset();
        } else if (s == "all") {
          game->allassets();
        } else if (s == "trade") {
          std::string name;
          std::string give;
          std::string get;
          in >> name;
          in >> give;
          in >> get;
          if (in.fail()) {
            game->printMessage("Not enough arguments.");
            break;
          }
          if (!in.fail()) {
            try {
              int giveMoney = std::stoi(give);
              try {
                int getMoney = std::stoi(get);
                game->printMessage("Cannot trade money for money!");
                continue;
              } catch (std::invalid_argument) {
                game->printMessage("Does " + name + " accept the trade of giving " + get + " in exchange for $" + give + " ?");
                std::string response;
                std::cin >> response;
                if (response == "accept") {
                  try {
                    // do the trade give money, receive building
                    game->trade(name, giveMoney, get);
                  } catch (WrongBuildingException) { 
                    continue; 
                  } catch (NoEnoughMoney n) {
                    game->printMessage("Your total worth is not enough!");
                    continue;
                  } catch (WrongPlayerException) {
                    continue;
                  }
                } else if (response == "reject") {
                  continue;
                } else {
                  game->printMessage("Invalid response, trade cancelled.");
                  continue;
                }
              } catch (std::out_of_range) {
                game->printMessage("Cannot trade money for money and invalid amount of money to receive.");
                continue;
              }
            } catch (std::invalid_argument) {
              try {
                int getMoney = std::stoi(get);
                game->printMessage("Does " + name + " accept the trade of giving $" + get + " in exchange for " + give + " ?");
                std::string response;
                std::cin >> response;
                if (response == "accept") {
                  // do the trade give building receive money
                  try {
                    game->trade(name, give, getMoney); 
                  } catch (WrongBuildingException) { 
                    continue;
                  } catch (NoEnoughMoney n) {
                    game->printMessage("Your total worth is not enough!");
                    continue;
                  } catch (WrongPlayerException) {
                    continue;
                  }
                } else if (response == "reject") {
                  continue;
                } else {
                  game->printMessage("Invalid response, trade cancelled.");
                  continue;
                }
              } catch (std::invalid_argument) {
                game->printMessage("Does " + name + " accept the trade of giving " + get + " in exchange for " + give + " ?");
                std::string response;
                std::cin >> response;
                if (response == "accept") {
                  try {
                    // do the trade give building, receive building
                    game->trade(name, give, get);
                  } catch (WrongBuildingException) { 
                    continue; 
                  } catch (NoEnoughMoney n) {
                    game->printMessage("Your total worth is not enough!");
                    continue;
                  } catch (WrongPlayerException) {
                    continue;
                  }
                } else if (response == "reject") {
                  continue;
                } else {
                  game->printMessage("Invalid response, trade cancelled.");
                  continue;
                }
              } catch (std::out_of_range) {
                game->printMessage("Invalid amount of money to receive.");
                continue;
              }
            } catch (std::out_of_range) {
              game->printMessage("Invalid amount of money to give.");
              continue;
            }
          }
        } else if (s == "improve") {
          std::string buildingName;
          std::string op;
          in >> buildingName;
          in >> op;
          if (in.fail()) {
            game->printMessage("Not enough arguments.");
            break;
          }
          if (op == "sell") {
            try{
              game->sellImprovement(game->currentPlayerName(), buildingName);
            } catch(WrongBuildingException & e) {
              continue;
            }
          } else if (op == "buy") {
            try{
              game->buyImprovement(buildingName);
            } catch (WrongBuildingException & e) {
              continue;
            }
          } else {
            game->printMessage("Invalid operation.");
          }
        } else if (s == "mortgage") {
          std::string buildingName;
          in >> buildingName;
          if (in.fail()) {
            game->printMessage("Not enough arguments.");
            break;
          }
          try {
            game->mortgage(game->currentPlayerName(), buildingName);
          } catch (WrongBuildingException & e) {
            game->printMessage("Cannot mortgage.");
          }
        } else if (s == "unmortgage") {
          std::string buildingName;
          in >> buildingName;
          if (in.fail()) {
            game->printMessage("Not enough arguments.");
            break;
          }
          try {
            game->unmortgage(buildingName);
          } catch (WrongBuildingException & e) {
            game->printMessage("Cannot unmortgage.");
          }
        } else if (s == "bankrupt") {
          game->printMessage("Your total worth is positive so bankruptcy cannot be declared!");
        } else if (s == "map") {
          game->drawBoard();
        } else if (s == "save") {
          std::string fileName;
          in >> fileName;
          if (in.fail()) {
            game->printMessage("Need a file to store the information.");
            break;
          }
          std::ofstream realFile {fileName};
          game->saveGame(realFile);
        } else if (s == "quit"){
          break;
        } else {
          game->printMessage("Invalid input.");
          continue;
        } 
     }
  } catch (hasWon & e) {
     return;
  }
}

void CommandInput::purchaseOrNot(std::istream & in, std::string building) {
  std::string option;
  in >> option;
  if (in.fail()) {
    game->printMessage("No option is given, auction activated.");
    auction(std::cin, building);
  }
  if (option == "yes") {
    game->purchase(building);
  } else if (option == "no") {
    game->printMessage("Not purchased, auction activated.");
    auction(std::cin, building);
  } else {
    game->printMessage("Invalid input, auction activated.");
    auction(std::cin, building);
  }
}

void CommandInput::auction(std::istream & in, std::string building) {
  std::string buyer;
  std::string secondOp;
  int price;
  int highestPrice = 0;
  std::string currBuyer;
  std::vector<std::string> playerNames = game->getPlayerNames();
  
  while(!in.fail()) {
    in >> buyer;
    in >> secondOp;
    if (in.fail()) {
      game->printMessage("No more input.");
      if (currBuyer.length() != 0) {
        try {
          game->findPlayer(currBuyer)->giveMoney(nullptr, highestPrice);
        } catch (NoEnoughMoney & e) {
          game->printMessage(currBuyer + " needs $" + std::to_string(e.needAmount) + " more to complete purchase");
          in.clear();
          game->printMessage("Redo the auction round, please enter your price again.");
          continue;
        } catch (giveMoneyAlert & e) {
          game->printMessage(e.message);
          game->tradeBuilding(building, currBuyer);
          break;
        }
      } else {
        in.clear();
        game->printMessage("Redo the auction round, please enter your price again.");
        continue;
      }
    }
    
    if (std::find(playerNames.begin(), playerNames.end(), buyer) == playerNames.end()) {
      game->printMessage("Invalid buyer name, please re-enter.");
      continue;
    }
    
    if (secondOp == "withdraw") {
      if (currBuyer != buyer) {
        playerNames.erase(std::find(playerNames.begin(), playerNames.end(), buyer));
        std::cout << playerNames.size();
        game->printMessage(buyer + " has withdrawn from the current auction.");
      } else {
        game->printMessage("You are the hightest bidder, cannot withdraw.");
      }
      if (playerNames.size() == 1) {
        try {
          game->findPlayer(currBuyer)->giveMoney(nullptr, highestPrice);
        } catch (NoEnoughMoney & e) {
          game->printMessage(currBuyer + " needs $" + std::to_string(e.needAmount) + " more to complete purchase");
          in.clear();
          game->printMessage("Redo the auction round, please enter your price again.");
          continue;
        } catch (giveMoneyAlert & e) {
          game->printMessage(e.message);
          game->tradeBuilding(building, currBuyer);
        }
        break;
      }
      continue;
    } else {
      try {
        price = stoi(secondOp);
      } catch (std::invalid_argument) {
        game->printMessage("Invalid input, type again.");
        continue;
      } catch (std::out_of_range) {
        game->printMessage("Invalid number of money.");
        continue;
      }      
    }
    
    if (price > highestPrice) {
      highestPrice = price;
      currBuyer = buyer;
    } else {
      game->printMessage("Need to spend more money than $" + std::to_string(highestPrice));
      continue;
    }
  }
}

bool CommandInput::NotEnoughMoney(std::istream & in, int amount, std::string playerName, std::string toPlayer) {
  int currAmount = amount;
  if (game->totalAsset(playerName) < currAmount) {
    game->printMessage("You do not have enough asset to pay the money, type \"bankrupt\" to declare bankruptcy.");
    std::string bkrpt;
    in >> bkrpt;
    if (bkrpt == "bankrupt") {
      try {
          game->bankrupt(playerName, toPlayer);
      } catch (hasWon & e) {
          throw e;
      }
    } else {
      game->printMessage("Invalid input, forced bankruptcy.");
      try {
          game->bankrupt(playerName, toPlayer);
      } catch (hasWon & e) {
          throw e;
      }
    }
    return false;
  }
  game->printMessage("You need to raise $" + std::to_string(amount) + " by mortgaging properties or sell improvements.");
  std::string option;
  in >> option;
  while (!in.fail() && currAmount > 0) {
    if (option == "improve") {
      // sell improvement
      std::string buildingName;
      std::string m;
      in >> buildingName;
      in >> m;
      if (m == "sell") {
        try {
          int temp = game->sellImprovement(playerName, buildingName);
          currAmount -= temp;
        } catch (WrongBuildingException & w1) {
          game->printMessage("You don't own the building" + buildingName);
          continue;
        }
      } else {
        continue;
      }
    } else if (option == "mortgage") {
      // do mortgage
      std::string buildingName;
      in >> buildingName;
      try {
        int temp = game->mortgage(playerName, buildingName);
        currAmount -= temp;
      } catch (WrongBuildingException & w1) {
        continue;
      }
    } else {
      game->printMessage("Invalid option!");
      continue;
    }
  }
  return true;
}


void CommandInput::TimHortons(std::istream & in, int currentRound) {
  
  // player has been in the line for 3 rounds
  // ...

    if (currentRound == 3) {
        game->printMessage("It is your third turn in the DC Tims line. If you do not roll doubles, you must leave the line by either paying $50 or using a Roll Up the Rim cup.\nDo you want to roll dice, pay $50 or use a Roll Up the Rim Cup?");
        std::string command;
        in >> command;
        if (command == "roll") {
            game->leaveLine();
            int dice1 = game->roll();
            int dice2 = game->roll();
            if (dice1 == dice2) {
                game->printMessage("Your rolled doubles!\nYou are out of the line!");
                game->leaveLine();
            } else {
                game->printMessage("Your didn't roll doubles...\nYou need to pay $50 or using a Roll Up the Rim Cup.");
                while (true) {
                    in >> command;
                    if (command == "pay") {
                        try {
                            game->buyCoffee();
                        } catch (NoEnoughMoney & e) {
                            if (NotEnoughMoney(std::cin, e.needAmount, e.playerName, "Bank")) {
                                game->buyCoffee();
                                game->leaveLine();
                            } else break;
                        } catch (giveMoneyAlert & e) {
                            game->leaveLine();
                            game->printMessage(e.message);
                        } 
                        
                        game->printMessage("You payed $50!\nYou are out of the line!");
                        game->movePlayer(dice1 + dice2);
                        game->leaveLine();
                        std::cerr << "Leave line." << std::endl;
                        std::cerr << game->currentTimRound() << std::endl;
                        break;
                    } else {
                        try {
                            game->useRimCup();
                            game->printMessage("You used a Roll Up the Rim Cup!\nYou are out of the line!");
                            game->movePlayer(dice1 + dice2);
                            game->leaveLine();
                            break;
                        } catch (NoEnoughCup & e) {
                            game->printMessage(e.message);
                            continue;
                        }
                    }
                }
                
            }
        } else if (command == "pay") {
            try {
                game->buyCoffee();
            } catch (NoEnoughMoney & e) {
                if (NotEnoughMoney(std::cin, e.needAmount, e.playerName, "Bank")) {
                        game->buyCoffee();
                        game->leaveLine();
                } else return;
            } catch (giveMoneyAlert & e) {
                game->leaveLine();
                game->printMessage(e.message);
            }                     
            game->printMessage("You payed $50!\nYou are out of the line!");
        } else if (command == "use") {
            try {
                game->useRimCup();
                game->printMessage("You used a Roll Up the Rim Cup!\nYou are out of the line!");
            } catch (NoEnoughCup & e) {
                game->printMessage(e.message);
                TimHortons(in, currentRound);
            }
        } else {
            game->printMessage("Invalid input.");
            TimHortons(in, currentRound);
        }
    } else { 
        game->printMessage("You are in the DC Tims Line :(\nDo you want to roll dice, pay $50 or use a Roll Up the Rim Cup?");
        std::string command;
        in >> command;
        if (command == "roll") {
            if (game->rollDouble()) {
                game->printMessage("Your rolled doubles!\nYou are out of the line!");
                game->leaveLine();
            } else {
                game->printMessage("Your didn't roll doubles...\nYou are still in the line ...");
                game->stayInLine();
            }
        } else if (command == "pay") {
            try {
                game->buyCoffee();
            } catch (NoEnoughMoney & e) {
                if (NotEnoughMoney(std::cin, e.needAmount, e.playerName, "Bank")) {
                        game->buyCoffee();
                } else return;
            } catch (giveMoneyAlert & e) {
                game->leaveLine();
                game->printMessage(e.message);
            }
            game->leaveLine();
            game->printMessage("You payed $50!\nYou are out of the line!");
        } else if (command == "use") {
            try {
                game->useRimCup();
            } catch (NoEnoughCup & e) {
                game->printMessage(e.message);
                TimHortons(in, currentRound);
            }
            game->printMessage("You used a Roll Up the Rim Cup!\nYou are out of the line!");
        } else {
            game->printMessage("Invalid input.");
            TimHortons(in, currentRound);
        }
    }
    
}

void CommandInput::payTuition(std::istream & in) {
   game->printMessage("You need to pay tuition :(\nDo you want to pay $300(A) or 10% of your total worth(B)?");
   std::string command;
   in >> command;
   game->howToPayTuition(command);
}
