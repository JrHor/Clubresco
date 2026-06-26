#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

void user_init(User* target, char* nome, char* senha, int ano_nasc) {
  target->nome = nome;
  target->senha = senha;
  target->ano_nasc = ano_nasc;

}

void cadastrar_usuario(User user){
  FILE* f;
  char caminho[128] = "./";

  strcat(caminho, user.nome);
  strcat(caminho, ".usr");

  f = fopen(caminho, "wb");

  if (f == NULL) {
    printf("Erro ao acessar arquivo\n");
    return;
  }

  fwrite(&user, 1, sizeof(user), f);

  fclose(f);
}

void ler_usuario(User* retorno, char* nome) {
  FILE* f;
  char caminho[128] = "./";

  strcat(caminho, nome);
  strcat(caminho, ".usr");

  fopen(caminho, "rb");

  if (f == NULL) {
    printf("Erro ao acessar arquivo\n");
    return;
  }

  fread(retorno, 1, sizeof(User), f);
  
  fclose(f);
}
