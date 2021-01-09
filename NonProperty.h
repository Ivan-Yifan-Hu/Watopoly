#ifndef NONPROPERTY_H
#define NONPROPERTY_H
#include "Building.h"
#include "Player.h"
#include "Exception.h"
#include <vector>
#include <memory>


// RimCup class that stores and maintains the number of active cups
class RimCup {
  int ActiveCup;
  public:
  // give a cup to player
  void giveCup(Player & p);
  // allows player to use a cup
  void receiveCup(Player & p);
};

// abstract base class for all Non-Property buildings
class NonProperty : public Building {
  public:
    NonProperty(std::string name, int position);
    virtual ~NonProperty() = 0;
};

// Tuition
class Tuition : public NonProperty {
  public:
    Tuition(std::string name, int position);
    virtual ~Tuition() override;
    virtual void accept(Player & p) override;
};

// Tim Hortons
class TimHortons : public NonProperty {
  public:
    TimHortons(std::string name, int position);
    virtual ~TimHortons() override;
    virtual void accept(Player & p) override;
};

// GoToTims
class GoToTims : public NonProperty {
  public:
    GoToTims(std::string name, int position);
    virtual ~GoToTims() override;
    virtual void accept(Player & p) override;
};

// SLC
class SLC : public NonProperty {
  std::shared_ptr<RimCup> rimCup;
  public:
    SLC(std::string name, int position, std::shared_ptr<RimCup> r);
    virtual ~SLC() override;
    virtual void accept(Player & p) override;
};

// OSAP
class OSAP : public NonProperty {
  public:
    OSAP(std::string name, int position);
    virtual ~OSAP() override;
    virtual void accept(Player & p) override;
};

// Coop Fee
class CoopFee : public NonProperty {
  public:
    CoopFee(std::string name, int position);
    virtual ~CoopFee() override;
    virtual void accept(Player & p) override;
};

// Goose nesting
class Goose : public NonProperty {
  public:
    Goose(std::string name, int position);
    virtual ~Goose() override;
    virtual void accept(Player & p) override;
};

// Needles Hall
class NeedlesHall : public NonProperty {
  std::shared_ptr<RimCup> rimCup;
  public:
    NeedlesHall(std::string name, int position, std::shared_ptr<RimCup> r);
    virtual ~NeedlesHall() override;
    virtual void accept(Player & p) override;
};
  
  
  

#endif
