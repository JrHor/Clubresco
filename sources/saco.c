#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "saco.h"

bool gerar_coin(double valor) {
  // receber data no formato
  time_t tempo;
  char data_formatada[20];

  time(&tempo);
  struct tm *tempo_local = localtime(&tempo);
  strftime(data_formatada, sizeof(data_formatada), "%d/%m/%Y %H:%M", tempo_local);

  // criar coin nos padrões
  FILE *f = fopen("coin.txt", "w");
  if (f == NULL) {
    printf ("Erro ao gerar arquivo, cancelando operação\n");
    return false;
  }

  fprintf(f, "--------------------------\n"\
             "valor: %2.2lf\n"\
             "criação: %s\n"\
             "código: abcd-1234\n"\
             "--------------------------\0", valor, data_formatada);
  return true;
}

bool saco_main(double* moedas)
{
  char valor[6];
init:
  printf("Qual o valor do saque?\n >>> 00.00");
  printf("\x1b[5D"); // move cursor para a esquerda 5 char
  scanf("%5s", valor);

  // gettar o bglh tlg
  char* ptr;
  double valor_conv;
  
  valor_conv = strtod(valor, &ptr);
  if (*ptr == valor[0]){
    printf("Digite um valor numérico válido!\n");
    goto init;
  }

  // vê se é grande ou não
  if (valor_conv > *moedas) {
    // faz aquela brincadeira né kk
    char inp;
    printf("O valor de saque é maior que sua quantia em dinheiro!\nDeseja fazer um Empréstimo no valor de %lf? [Y/ N] ", valor_conv - *moedas);
    if ((inp = getchar()) == 'y' || inp == 'Y'){
      // Empréstimo
      //...
    }
    
    printf("cancelando operação\n");
    return false;
  }

  if (!gerar_coin(valor_conv)){
    return false;
  }
  *moedas -= valor_conv;
  return true;
}
