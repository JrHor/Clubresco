#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "signup.h"
#include "arquivos.c"
#include "user.h"

int signup_main(void) {
  // coletar ano e data atual 
  struct tm *data;
  time_t tempo;

  tempo = time(NULL);
  data = localtime(&tempo);
  data->tm_year += 1900;

  // coletar informação de nome e Senha
init:
  char nome[53] = "";
  char senha[53] = "";
  int ano;

  printf("Cadastre-se no Clubresco ou 'q' para sair\n" \
         "Nome (26 chars): ");
  scanf(" %26s", nome);
  if (!strcmp(nome, "q")) return EXIT_SUCCESS;

  printf("Senha (26 chars): ");
  scanf(" %26s", senha);
  if (!strcmp(senha, "q")) return EXIT_SUCCESS;

  printf("Ano de nascimento: ");
  scanf(" %d", &ano);
  if (ano == 'q') return EXIT_SUCCESS;

  //verificação
  if ((data->tm_year - ano) < 16) {
    printf("Idade abaixo do permitido\n");
    return EXIT_SUCCESS;
  }

  char nome_usr[61] = "";
  strcat(nome_usr, nome);
  strcat(nome_usr, ".usr");

  if (existe_arquivo(nome_usr)) {
    printf("O Usuário de nome %s já está cadastrado!\n", nome);
    goto init;
  }

  // cadastrar Usuário
  User user;
  user_init(&user, nome, senha, ano);

  cadastrar_usuario(user);
  printf("Boas vindas ao Clubresco %s!\n", nome);  
  return EXIT_SUCCESS;
}
