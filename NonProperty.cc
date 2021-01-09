#include "NonProperty.h"
#include <cstdlib>
#include <time.h>
#include <random>

NonProperty::NonProperty (std::string name, int position) : Building(name, position) {}

NonProperty::~NonProperty() {}

void RimCup::giveCup(Player & p) {
  p.addCup();
  ActiveCup++;
}

void RimCup::receiveCup(Player & p) {
  p.removeCup();
  ActiveCup--;
}

Tuition::Tuition(std::string name, int position) : NonProperty{name, position} {}
Tuition::~Tuition() {}

void Tuition::accept(Player & p) {
  throw TuitionException("Tuition");
}

TimHortons::TimHortons(std::string name, int position) : NonProperty{name, position} {}

TimHortons::~TimHortons() {}

void TimHortons::accept(Player & p) {}


GoToTims::GoToTims(std::string name, int position) : NonProperty{name, position} {}

GoToTims::~GoToTims() {}

void GoToTims::accept(Player & p) {
  throw TimHortonsException("Go to Tims");
}

SLC::SLC(std::string name, int position, std::shared_ptr<RimCup> r) : NonProperty{name, position}, rimCup{r} {}

SLC::~SLC(){}

 void SLC::accept(Player & p) {
  // random numebr generation algorithm
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 100);
  int a = uniform_dist(e1);
  
   // models the 1% chance of recieving the Roll Up the rim cup
  if (a == 44) {
    rimCup->giveCup(p);
    throw getRimCup("Got a rim cup");
    // models the variety of consequence when landing on SLC
  } else {
    srand (time(NULL));
    int num = rand() % 24;
    if (num >= 0 && num <= 2) {
      throw SLCException("You reached SLC", -3);
    } else if (num >= 3 && num <= 6) {
      throw SLCException("You reached SLC", -2);
    } else if (num >= 7 && num <= 10) {
      throw SLCException("You reached SLC", -1);
    } else if (num >= 11 && num <= 13) {
      throw SLCException("You reached SLC", 1);
    } else if (num >= 14 && num <= 17) {
      throw SLCException("You reached SLC", 2);
    } else if (num >= 18 && num <= 21) {
      throw SLCException("You reached SLC", 3);
    } else if (num == 22) {
      throw SLCException("You reached SLC", 8);
    } else {
      throw SLCException("You reached SLC", -2);
    }
  }
}

OSAP::OSAP(std::string name, int position) : NonProperty{name, position} {}

OSAP::~OSAP(){}

void OSAP::accept(Player & p) {
  p.addMoney(200);
}

CoopFee::CoopFee(std::string name, int position) : NonProperty{name, position} {}

CoopFee::~CoopFee(){}

void CoopFee::accept(Player & p) {
  p.giveMoney(nullptr, 150);
}

Goose::Goose(std::string name, int position) : NonProperty{name, position} {}

Goose::~Goose(){}

void Goose::accept(Player & p) {
  // prints message
  throw GooseException("Attacked by geese!");
}

NeedlesHall::NeedlesHall(std::string name, int position, std::shared_ptr<RimCup> r) : NonProperty{name, position}, rimCup{r} {}

NeedlesHall::~NeedlesHall(){}

void NeedlesHall::accept(Player & p) {
  // random numebr generation algorithm
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 100);
  int a = uniform_dist(e1);
  
  // models the 1% chance of recieving the Roll Up the rim cup 
  if (a == 44) {
    rimCup->giveCup(p);
    throw getRimCup("Got a rim cup");
    // models the variety of consequences when landing on Needles Hall
  } else {
    srand (time(NULL));
    int num = rand() % 18;
    if (num == 0) {
      throw NeedlesHallException("You reached Needles hall", -200);
    } else if (num >= 1 && num <= 2) {
      throw NeedlesHallException("You reached Needles hall", -100);
    } else if (num >= 3 && num <= 5) {
      throw NeedlesHallException("You reached Needles hall", -50);
    } else if (num >= 6 && num <= 11) {
      throw NeedlesHallException("You reached Needles hall", 25);
    } else if (num >= 12 && num <= 14) {
      throw NeedlesHallException("You reached Needles hall", 50);
    } else if (num >= 15 && num <= 16) {
      throw NeedlesHallException("You reached Needles hall", 100);
    } else {
      throw NeedlesHallException("You reached Needles hall", 200);
    }
  }
}
