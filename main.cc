#include "commandInput.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

void usage() {
    std::cerr << "Too many arguments!" << std::endl;
    std::cerr << "Command Line Options:" << std::endl;
    std::cerr << "A: -load file" << std::endl;
    std::cerr << "B: -testing" << std::endl;
} // usage


int main(int argc, char ** argv) {
    std::map<std::string, std::string> players;
      /*players["Andrew"] = "A";
      players["Ivan"] = "I";
      players["Fatday"] = "F";
      players["Klaus"] = "K";
      players["Lingwei"] = "L";
      players["Steven"] = "S";*/
    if (argc > 4) {
      usage();
      return 1;
    } else if ((argc == 1) && (std::strcmp(argv[0], "./Watopoly"))) {
      int numPlayers;
      std::string line;
      std::cout << "Welcome to Watopoly! Please type \"add Player_name Player_symbol\" to add an player. After adding players, type begin to begin the game.\n";
      
      while (getline(std::cin, line)) {
          std::istringstream ss1{line};
          std::string command;
          std::string name;
          std::string symbol;
          ss1 >> command;
          if (command == "add") {
              ss1 >> name;
              if (ss1.fail()) {
                  std::cout << "Please type \"add Player_name Player_symbol\" to add an player.\n";
                  continue;
              }
              ss1 >> symbol;
              if (ss1.fail()) {
                  std::cout << "Please type \"add Player_name Player_symbol\" to add an player.\n";
                  continue;
              }
              players[name] = symbol;
          } else if (command == "begin") {
              break;
          } else {
              std::cout << "Invalid command. Please type \"add Player_name Player_symbol\" to add an player. After adding players, type begin to begin the game.\n";
              continue;
          }
      }
      CommandInput input{std::make_shared<Game>(players)};
      input.readInput(std::cin, false);
      return 0;
    } else if (argc == 3) {
      std::ifstream infile{argv[2]};
      CommandInput input{std::make_shared<Game>(infile)};
      input.readInput(std::cin, false);
      return 0;
    } else if (argc == 2) {
      //testing mode
        int numPlayers;
      std::string line;
      std::cout << "Welcome to Watopoly! Please type \"add Player_name Player_symbol\" to add an player. After adding players, type begin to begin the game.\n";
      
      while (getline(std::cin, line)) {
          std::istringstream ss1{line};
          std::string command;
          std::string name;
          std::string symbol;
          ss1 >> command;
          if (command == "add") {
              ss1 >> name;
              if (ss1.fail()) {
                  std::cout << "Please type \"add Player_name Player_symbol\" to add an player.\n";
                  continue;
              }
              ss1 >> symbol;
              if (ss1.fail()) {
                  std::cout << "Please type \"add Player_name Player_symbol\" to add an player.\n";
                  continue;
              }
              players[name] = symbol;
          } else if (command == "begin") {
              break;
          } else {
              std::cout << "Invalid command. Please type \"add Player_name Player_symbol\" to add an player. After adding players, type begin to begin the game.\n";
              continue;
          }
      }
      CommandInput input{std::make_shared<Game>(players)};
      input.readInput(std::cin, true);
      return 0;
    } else {
      std::string command1 = argv[1];
      if (command1 == "-load") {
          std::string fileName = argv[2];
          std::ifstream infile{fileName};
          CommandInput input{std::make_shared<Game>(infile)};
          input.readInput(std::cin, true);
      } else {
          std::string fileName = argv[3];
          std::ifstream infile{fileName};
          CommandInput input{std::make_shared<Game>(infile)};
          input.readInput(std::cin, true);
      }
      return 0;
    }
}
   




      

