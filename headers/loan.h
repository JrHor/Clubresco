#ifndef LOAN_H
#define LOAN_H

#include "user.h"
#include <time.h>
#include <stdbool.h>

//helper
/*
timefoward: avança SECONDS_ADD segundos e retorna esse tempo
*/
time_t timefoward(int seconds_add);

// main
bool loan_main(User* acc, double val);

#endif // !LOAN_H
