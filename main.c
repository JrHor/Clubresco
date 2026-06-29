#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sources/arquivos.c" // maldito adolfo
#include "user.h"
#include "signin.h"
#include "signup.h"
#include "deposit.h"
#include "saco.h"

typedef enum {
  COM_SIGNIN = 1,
  COM_SIGNUP,
  COM_EXIT
} commands_init;

typedef enum {
  COM_MENU_EXIT,
  COM_SAQUE,
  COM_DEPOSITO,
  COM_EMPRESTIMO,
  COM_INVESTIR
} commands_main;

int main(void)
{
  User user;
  commands_init i;
init:
  printf("======================\n"\
         "       Clubresco      \n"\
         "1. Entrar\n"\
         "2. Cadastre-se\n"\
         "3. Sair\n>>> ");
  scanf("%d", (int*) &i);

  switch (i) {
    case COM_SIGNIN :{
      signin_main(&user);
      break;         }
    case COM_SIGNUP :{
      signup_main();
      goto init;
      break;         }
    case COM_EXIT   :{
      return EXIT_SUCCESS;
      break;         }
    default         :{
      printf("Opção inexistente\n");
      goto init;
      break;         }
  }
  
  bool active = true;

  while (active) {
    commands_main inp = -1;
    printf("\nBem vindo(a) %s\n"\
           "Clubecoins: %lf\n"\
           "1. Sacar\n"\
           "2. Depositar\n"\
           "3. Empréstimo\n"\
           "4. Investir\n"\
           "0. Sair\n"\
           ">>> ", user.nome, user.coin);
    scanf("%1d", (int*) &inp);

    switch (inp) {
      case COM_MENU_EXIT :{
        printf("bye bye\n");
        cadastrar_usuario(user); 
        active = false;
        break;
      }
      case COM_SAQUE :{
        saco_main(&user.coin);
        break;
      }
      case COM_DEPOSITO :{
        deposit_main(&user.coin);
        break;
      }

      default :{
        printf("Opção não implementada\n");
        break;
      }
    }

  }

  return EXIT_SUCCESS;
}
