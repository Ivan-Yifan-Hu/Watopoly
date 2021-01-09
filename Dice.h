#ifndef _DICE_H_
#define _DICE_H_


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>


// Dice class 
class Dice {
  
  public:
  // returns a random number of uniform distribution in the range of 1 to 6
  // mimics the function of the dice
  unsigned int roll();
};

#endif
