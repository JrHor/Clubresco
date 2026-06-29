#ifndef USER_H
#define USER_H

#include <time.h>

// Types
typedef struct {
  time_t data_ven;
  double pagamento;
} Emprestimos;

typedef struct {
  time_t data_inv;
  double coin;
  float rendimento;
} Investimentos;

typedef struct {
  char nome[56];
  char senha[56];
  int ano_nasc;
  double coin;
  Emprestimos emprestimos;
  Investimentos investimento;
} User;

// Functions

/*
user_init: inicia a estrutura User em TARGET
 */
void user_init(User* target, char* nome, char* senha, int ano_nasc);

/*
cadastrar_usuario: Salva o usuario USER no armazenamento
 */ 
void cadastrar_usuario(User user);

/*
ler_usuario: Procura o usuario de nome NOME e retorna seus dados em RETORNO
 */ 
void ler_usuario(User* retorno, char* nome);

#endif // !USER_H


