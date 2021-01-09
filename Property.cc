#include "Property.h"

Property::Property(std::string name, int position, std::shared_ptr<Player> owner, 
                   unsigned int p, std::string monopoly) : Building(name, position), owner{owner}, purchaseCost{p}, monopoly{monopoly}, mortgage{false} {}

bool Property::Mortgage() {
  return mortgage;
}

void Property::setMortgage(bool m) {
  mortgage = m;
}

Property::~Property() {}

std::shared_ptr<Player> Property::getOwner() {
    return owner;
}

void Property::setOwner(std::shared_ptr<Player> p) {
    owner = p;
}

unsigned int Property::getPurchaseCost() {
    return purchaseCost;
}

std::string Property::getMonopoly() {
    return monopoly;
}

Gym::Gym(std::string name, int position, std::shared_ptr<Player> owner) : Property(name, position, owner, 150, "Gym") {}

unsigned int Gym::getFee(Player & p) {
    unsigned int diceSum = p.roll() + p.roll();
    if (this->getOwner()->getProperties("Gym") == 1) {
        return diceSum * 4;
    } else {
        return diceSum * 10;
    }
}


void Gym::accept(Player & p) {
    if (this->getOwner() == nullptr) {
        throw NoOwner("This property has no owner yet!");
    }
    if (this->getOwner()->getName() != p.getName() && !Mortgage()) {
        unsigned int fee = getFee(p);
        p.giveMoney(this->getOwner(), fee);
    }
}


Residence::Residence(std::string name, int position, std::shared_ptr<Player> owner) : Property(name, position, owner, 200, "Residence") {}

unsigned int Residence::getRent() {
    unsigned int residence = this->getOwner()->getProperties("Residence");
    if (residence == 1) {
        return 25;
    } else if (residence == 2) {
        return 50;
    } else if (residence == 3) {
        return 100;
    } else if (residence == 4) {
        return 200;
    } else {
        return 0;
    }
}
     

void Residence::accept(Player & p) {
    if (this->getOwner() == nullptr) {
        throw NoOwner("This property has no owner yet!");
    }
    if (this->getOwner()->getName() != p.getName() && !Mortgage()) {
        unsigned int rent = getRent();
        p.giveMoney(this->getOwner(), rent);
    }
}

Academic::Academic(std::string name, int position, std::shared_ptr<Player> owner, 
         std::string monopoly, unsigned int p, unsigned int improvementCost, 
         std::vector<unsigned int> tuition) : Property(name, position, owner, p, monopoly), improvement{0}, improvementCost{improvementCost}, tuition{tuition} {}

unsigned int Academic::getImprovement() {
    return improvement;
}


unsigned int Academic::getImprovementCost() {
    return improvementCost;
}

unsigned int Academic::getTuition() {
    int fee = tuition[improvement];
    if ((improvement == 0) && (this->getOwner()->hasFullMonopoly(this->getMonopoly()))) {
        return 2 * fee;
    } else {
        return fee;
    }
}

void Academic::improve(std::string s) {
    if ((s == "buy") && (improvement < 5)) {
        improvement++;
    } else if ((s == "sell") && (improvement > 0)) {
        improvement--;
    } else {
        throw ImprovementException("invalid improvement command!");
    }
}

void Academic::setImprovement(int improve) {
    improvement = improve;
}

void Academic::accept(Player & p) {
    if (this->getOwner() == nullptr) {
        throw NoOwner("This property has no owner yet!");
    }
    if (this->getOwner()->getName() != p.getName() && !Mortgage()) {
        unsigned int tuition = getTuition();
        p.giveMoney(this->getOwner(), tuition);
    }
}


