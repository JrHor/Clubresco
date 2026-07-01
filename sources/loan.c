#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "loan.h"
#include "user.h"

time_t timefoward(int seconds_add){ time_t time_now = time(NULL);
  time_now += seconds_add;
  return time_now;
}

bool loan_main(User* acc, double val)
{
  time_t tempo = timefoward((int) val*10);
  double diff = difftime(tempo, time(NULL));

  int inp;
init:
  printf("Você está prestes a pedir um empréstimo no valor de %lf, 50%% de juros e vencimento em %.2lf minutos \nDeseja continuar?[y/n]: ", val, diff/60);
  scanf("%lc", &inp);

  if (inp == 'Y' || inp == 'y') {
    printf("Empréstimo realizado!\n");
    acc->emprestimos.data_ven = tempo;
    acc->emprestimos.pagamento = val * -1.5;
    acc->coin += val;
    return true;
  }
  else if (inp == 'n' || inp == 'N') {
    return false;
  }
  printf("Digite Y para sim ou N para não\n");
  goto init;
}
