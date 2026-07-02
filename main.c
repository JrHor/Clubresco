#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sources/arquivos.c" // maldito adolfo
#include "user.h"
#include "signin.h"
#include "signup.h"
#include "deposit.h"
#include "saco.h"
#include "loan.h"
#include "investment.h"

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
    time_t timenow = time(NULL);

    if (timenow >= user.emprestimos.data_ven && user.emprestimos.data_ven != 0){
     if (deposit_main(&user.emprestimos.pagamento)){
        if (user.emprestimos.pagamento < 0) continue;
        user.emprestimos.data_ven = 0;

        if (user.emprestimos.pagamento > 0) {
          user.coin = user.emprestimos.pagamento;
          user.emprestimos.pagamento = 0.0;
          printf("O Clubresco agradece por pagar sua dívida\n");
          continue;
        }
      } 
      printf("Paga tua divida vagabundo!");
      break;
    }

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
        saco_main(&user);
        break;
      }
      case COM_DEPOSITO :{
        deposit_main(&user.coin);
        break;
      }
      case COM_EMPRESTIMO :{
        char valor[250];
        printf("digite o valor do emprestimo: ");
        scanf("%s", valor);

        double emprestimo = strtod(valor, NULL);

        loan_main(&user, emprestimo);
        break;
      }
      case COM_INVESTIR :{
        if (user.investimento.data_inv != 0){
          if (user.investimento.data_inv > timenow ) {
            printf("Faltam %ld dias para você resgatar seu investimento\n", (user.investimento.data_inv - timenow) / (60*60*24));
            continue;
          }
          
          printf("Seu retorno foi de %lf em 30 dias com um crescimento de %d%%",user.investimento.coin,(int) (user.investimento.rendimento-1)*100);

          user.investimento.coin += user.coin;
          user.investimento.coin = 0;
          user.investimento.rendimento = 0;
          user.investimento.data_inv = 0;
          continue;
        }
        investment_main(&user);
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
