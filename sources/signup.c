#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "signup.h"
#include "arquivos.c"


int main(void) {
  // coletar informação de nome e Senha
init:
  char nome[53] = "";
  char senha[53] = "";

  printf("Cadastre-se no Clubresco ou 'q' para sair\n" \
         "Nome (26 chars): ");
  scanf(" %26s", nome);
  if (!strcmp(nome, "q")) return EXIT_SUCCESS;

  printf("Senha (26 chars): ");
  scanf(" %26s", senha);
  if (!strcmp(senha, "q")) return EXIT_SUCCESS;

  //verificação
  if (existe_arquivo(nome)) {
    printf("O Usuário de nome %s já está cadastrado!\n", nome);
    goto init;
  }

  // cadastrar Usuário
  criar_arquivo(nome);
  escrever_arquivo(nome, strcat(senha, "\n"));
  printf("Boas vindas ao Clubresco %s!\n", nome);  
  return EXIT_SUCCESS;
}
