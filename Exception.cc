#include "Exception.h"

WatopolyException::WatopolyException(std::string m) : message{m} {}

NoOwner::NoOwner(std::string m) : WatopolyException(m) {}

NoEnoughMoney::NoEnoughMoney(std::string m, int a, std::string playerName, std::string receiver) : WatopolyException(m), needAmount{a}, playerName{playerName}, receiver{receiver} {}

giveMoneyAlert::giveMoneyAlert(std::string m) : WatopolyException(m) {}

NoEnoughCup::NoEnoughCup(std::string m) : WatopolyException(m) {}

TuitionException::TuitionException(std::string m): WatopolyException(m) {}

TimHortonsException::TimHortonsException(std::string m) : WatopolyException(m) {}

getRimCup::getRimCup(std::string m) : WatopolyException(m) {}

SLCException::SLCException(std::string m, int s) : WatopolyException(m), steps{s} {}

GooseException::GooseException(std::string m) : WatopolyException(m) {}

NeedlesHallException::NeedlesHallException(std::string m, int a) : WatopolyException(m), amount{a} {}

ImprovementException::ImprovementException(std::string m) : WatopolyException(m) {}

WrongBuildingException::WrongBuildingException(std::string m) : WatopolyException(m) {}

WrongPlayerException::WrongPlayerException(std::string m) : WatopolyException(m) {}

MortgageException::MortgageException(std::string m) : WatopolyException(m) {}

hasWon::hasWon(std::string m) : WatopolyException(m) {}

bankruptException::bankruptException(std::string m) : WatopolyException(m) {}
