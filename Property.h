#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Building.h"
#include "Player.h"
#include "Exception.h"


// base class for all Property buildings
class Property: public Building {
  // basic information of the building
  std::shared_ptr<Player> owner;
  unsigned int purchaseCost;
  std::string monopoly;
  bool mortgage;
  
  public:
  // constructor
    Property(std::string name, int position, std::shared_ptr<Player> owner, unsigned int p, std::string monopoly);
  // destructor
    virtual ~Property() = 0;
  // accessor
    std::shared_ptr<Player> getOwner();
  // mutator
    void setOwner(std::shared_ptr<Player> owner);
  // accessor 
    unsigned int getPurchaseCost();
  // accessor
    std::string getMonopoly();
  // mutator
    void setMortgage(bool m);
  // determines if the building has been mortgaged
    bool Mortgage();
};

// Academic
class Academic : public Property {
  // basic information
  private:
    unsigned int improvement;
    unsigned int improvementCost;
    std::vector<unsigned int> tuition;
  public:
    Academic(std::string name, int position, std::shared_ptr<Player> owner, std::string monopoly, 
                     unsigned int p, unsigned int improvementCost, std::vector<unsigned int > tuition);
    unsigned int getImprovement();
    unsigned int getImprovementCost();
    unsigned int getTuition();
    virtual void accept(Player & p) override;
    void improve(std::string s);
    void setImprovement(int improvement);
};

// Gym
class Gym: public Property {
  public:
  Gym(std::string name, int position, std::shared_ptr<Player> owner);
  unsigned int getFee(Player & p);
  virtual void accept(Player & p) override;
};
  
// Residence
class Residence: public Property {
  public:
  Residence(std::string name, int position, std::shared_ptr<Player> owner);
  unsigned int getRent();
  virtual void accept(Player & p) override;
};
  


#endif
