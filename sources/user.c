#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

void user_init(User* target, char* nome, char* senha, int ano_nasc) {
  strcpy(target->nome, nome);
  strcpy(target->senha, senha);
  target->ano_nasc = ano_nasc;
  target->coin = 0.0;
  target->emprestimos.data_ven = 0;
  target->emprestimos.pagamento = 0.0;
  target->investimento.data_inv = 0;
  target->investimento.coin = 0.0;
  target->investimento.rendimento = 0.0;
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
  FILE* f = NULL;
  char caminho[128] = "./";

  strcat(caminho, nome);
  strcat(caminho, ".usr");

  f = fopen(caminho, "rb");

  if (f == NULL) {
    printf("Erro ao acessar arquivo\n");
    return;
  }

  fread(retorno, 1, sizeof(User), f);
  
  fclose(f);
}
