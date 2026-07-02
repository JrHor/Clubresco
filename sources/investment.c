#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "user.h"
#include "investment.h"

time_t dayskip(int days){
  int dia = 60*60*24;
  time_t tempo = time(NULL);

  return (time_t)(days*dia + tempo);
}

bool investment_main (User* acc)
{
  int inp;
  printf("Ações\n"\
         "\n"\
         "1. Clubresco - 50%% de retorno\n"\
         "2. MC Não traficante - 567%% de retorno\n"\
         "3. Loja do seu zé - 111%% de retorno\n"\
         "4. Construtora P&B - 120%% de retorno\n"\
         ">>> ");
  scanf("%d", &inp);
  

  float percentual;
  switch (inp) {
    #define X(val, name, inv) case val:\
    percentual = inv;\
    printf("Digite o valor a invetir em " #name ": ");\
    break;
    
    ACTION
    #undef X
    default:
      printf("Ação inexistente\n");
      break;
  }
  
  char valor[255];
  scanf("%s", valor);
  float coin = strtod(valor, NULL);
  
  if (coin > acc->coin){
    printf("Saldo insuficiente\n");
    return false;
  }

  printf("investidos %lf que renderão %d%% em 30 dias!\n", coin, (int)percentual*100);

  acc->coin -= coin;
  acc->investimento.data_inv = dayskip(30);
  acc->investimento.coin = coin * percentual;
  acc->investimento.rendimento = percentual;
  return true;
}
