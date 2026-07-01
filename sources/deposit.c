#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "deposit.h"
/*
 --------------------------
 valor: 00,00
 criação: 00/00/0000 00:00
 código: abcd-1234
 --------------------------
*/

void getsubs(size_t size, size_t* start, char* texto, char* dest){
  int i = 0;
  int j;
  for (j = *start; i < size && texto[j] != '\n'; i++, j++) {
    dest[i] = texto[j];
  }
  dest[i] = '\0';
  *start = j;
}

bool ler_coin(char* texto, double* valor) {
  // verificar integridade: header com '---'
  size_t i;
  for (i = 0; texto[i] == '-' && i <= 25; i++);
  if (i < 25) {
    printf("Clubecoin não é válida\nheader error 00 <i = %ld>\n", i);
    return false;
  }
  if (texto[i++] != '\n') {
    printf("A Clubecoin não é válida\nheader error 01 < i = %c>\n", texto[i]);
    return false;
  }

  // verificar integridade: "valor: "
  char txt_valor[8];
  getsubs(7, &i, texto, txt_valor);
  if (strcmp(txt_valor, "valor: ")) {
    printf("A Clubecoin não é válida\nvalor error 00 <valor diff>\n");
    return false;
  }
  

  // coletar valor
  char txt_coin[6];
  getsubs(5, &i, texto, txt_coin);
  for (int tl = 0; tl < 5; tl++){
    if (!isdigit(txt_coin[tl]) && txt_coin[tl] != '.') {
      printf("A Clubecoin não é válida\nNaN error 00 <i = %c\n",txt_coin[tl]);
      return false;
    }
  } 

  char *ptr;
  *valor = strtod(txt_coin, &ptr);

  // verificar integridadekk
  if (*ptr != '\n' && *ptr != '\0') {
    printf("A Clubecoin não é válida\ncoin error 00 <%c>\ndica: tente usar '.' ao invés de ','\n", *txt_coin);
    return false;
  }
  if (texto[i] != '\n') {
    printf("A Clubecoin não é válida\nvalor error 03 <i = %c>\n", texto[i]);
    return false;
  }
  i++;

  // verificar integridade: "criação: "
  char txt_create[12];
  getsubs(11, &i, texto, txt_create);
  if (strcmp("criação: ", txt_create)) {
    printf("A Clubecoin não é válida\ncriação error 00 <criação diff>\n");
    return false;
  }
  
  // verificar integridade: data
  for (int tj = 0; tj < 16; i++, tj++ ) {
    if(texto[i] == '\n' || texto[i] == '\0' || (!isdigit(texto[i]) && texto[i] != '/' && texto[i] != ':' && texto[i] != ' ')) {
    printf("A Clubecoin não é válida\ndate error 00 <i = %c tj = %d>\n", texto[i], tj);
    return false;
    }
  }
  if (texto[i++] != '\n') {
    printf("A Clubecoin não é válida\ndate error 01 <i = %c>\n", texto[i]);
    return false;
  }
  //verificar integridade: "código: abcd 1234"
  char txt_code[19];
  getsubs(18, &i, texto, txt_code);
  if (strcmp("código: abcd-1234", txt_code)) {
    printf("A Clubecoin não é válida\ncode error 00 <code diff>\n");
    return false;
  }
  if (texto[i++] != '\n') {
    printf("A Clubecoin não é válida\ncode error 01 <i = %c>\n", texto[i]);
    return false;
  }
  
  //verificar integridade: footer ---
  for (int tk = 0; tk < 26; tk++, i++) {
    if (texto[i] == '\n' || (texto[i] == '\0' && tk != 25)) {
    printf("A Clubecoin não é válida\nfooter error 00\n");
    return false;
  }
  }
  if (texto[i] == '\0' || texto[i] == '\n') {
    printf("A sua Clubecoin é integra!\n");
    return true;
  }
  printf ("erro desvonhecido <i = %ld '%c'>\n", i, texto[i]);
  return false;
}

bool deposit_main(double* conta)
{

  printf("Procurando moedas\n");
  if (!existe_arquivo("coin.txt")) {
    printf("Você não pode depositar nada!\nInsira um arquivo coin.txt na pasta do programa\n");
    return false;
  }
  
  char* texto = malloc(512 * sizeof(char));
  if (!ler_arquivo("coin.txt", texto, (size_t) 512)) return EXIT_SUCCESS;
  
  // ler o valor
  double valor;
  if (!ler_coin(texto, &valor)) {
    return false;
  }
  *conta += valor;

  //finalizar
  
  free(texto);
  deletar_arquivo("coin.txt");
  return true;
}

