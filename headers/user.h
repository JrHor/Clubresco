#ifndef USER_H

// Types

typedef struct {
  const char* nome;
  const char* senha;
  int ano_nasc;
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


