#ifndef _BUILDING_H_
#define _BUILDING_H_
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

class Player; // forward declaration

// abstract class of buildings
class Building {
  // basic information of the building
  private:
    std::string name;
    int position;
  public:
  // constructor
    Building(std::string name, int position);
  // accessor
    std::string getName();
  // accessor
    int getPosition();
  // virtual method for visitor pattern
    virtual void accept(Player & p) = 0;
};

#endif
