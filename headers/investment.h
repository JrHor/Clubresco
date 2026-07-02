#ifndef INVEST_H
#define INVEST_H

// Macros
#define ACTION\
  X(1, Clubresco, 0.5)\
  X(2, McNTraficante, 5.67)\
  X(3, ZeLojas, 1.11)\
  X(4, PeB, 1.2)

// Helpers

/*
dayskip: skipa os day tlg
 */ 
time_t dayskip(int days);

// Main

bool investment_main(User* acc);

#endif // !INVEST_H
