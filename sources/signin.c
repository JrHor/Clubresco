#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "signin.h"

void signin_main(User* retorno)
{
  printf("Bem vindo novamente ao Clubresco!\nDigite 'q' para sair\n");
init:
  // Receber dados 
  User user;
  char nome[56] = {0};
  char senha[56] = {0};

  printf("Nome: ");
  scanf("%s", nome);
  if(!strcmp(nome, "q")) return;

  // verificações
  char nome_usr[61] = {0};
  strcat(nome_usr, nome);
  strcat(nome_usr, ".usr");

  if (!existe_arquivo_bin(nome_usr)) {
    printf("Usuário não cadastrado, tente novamente ou cadastre-se\n");
    goto init;
  }
  ler_usuario(&user, nome);

  int c;
  while((c = getchar()) != '\n' && c != EOF);

  // coletar e verificar senha
  printf("Senha: ");
  scanf("%s", senha);
  if(!strcmp(senha, "q")) return;

  if(strcmp(senha, user.senha)) {
    printf("senha incorreta, tente novamente");
    goto init;
  }
  
  printf("Bem vindo(a) %s!", nome);
  *retorno = user;
}
