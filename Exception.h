#ifndef _Exception_H_
#define _Exception_H_

#include <string>

// base class for different exceptions
class WatopolyException {
  public:
  std::string message;
  WatopolyException(std::string m);
};

class NoOwner : public WatopolyException {
  public:
  NoOwner(std::string m);
};

class NoEnoughMoney : public WatopolyException {
  public:
  int needAmount;
  std::string playerName;
  std::string receiver;
  NoEnoughMoney(std::string m, int a, std::string playerName, std::string receiver);
};

class giveMoneyAlert : public WatopolyException {
  public:
  giveMoneyAlert(std::string m);
};

class NoEnoughCup : public WatopolyException {
  public:
  NoEnoughCup(std::string m);
};

class TuitionException : public WatopolyException {
  public:
  TuitionException(std::string m);
};

class TimHortonsException : public WatopolyException {
  public:
  TimHortonsException(std::string m);
};

class getRimCup : public WatopolyException {
  public:
  getRimCup(std::string m);
};

class SLCException : public WatopolyException {
  public:
  int steps;
  SLCException(std::string m, int s);
};

class GooseException : public WatopolyException {
  public:
  GooseException(std::string m);
};

class NeedlesHallException : public WatopolyException {
  public:
  int amount;
  NeedlesHallException(std::string m, int a);
};

class ImprovementException : public WatopolyException {
  public:
  ImprovementException(std::string m);
};

class WrongBuildingException : public WatopolyException {
  public:
  WrongBuildingException(std::string m);
};

class WrongPlayerException : public WatopolyException {
  public:
  WrongPlayerException(std::string m);
};

class MortgageException : public WatopolyException {
  public:
  MortgageException(std::string m);
};

class hasWon : public WatopolyException {
  public:
  hasWon(std::string m);
};

class bankruptException : public WatopolyException {
  public:
  bankruptException(std::string m);
};

#endif
