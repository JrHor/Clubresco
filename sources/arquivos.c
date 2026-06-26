#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
retorna true para uma arquivo válido, e false para um arquivo inválido
 */
bool verificar_arquivo(char caminho[]){
    if(strchr(caminho,'/') != NULL) {
        return false;
    }

    if(strchr(caminho,'\\') != NULL) {
        return false;
    }

    return true;
}

/*
lê o arquivo com o nome especificado, desde que o arquivo esteja dentro da pasta do executavel
 */
bool ler_arquivo(char caminho[], char* texto_lido, size_t tamanho_texto) {
    char caminho_relativo[100] = "./";
    FILE *arquivo;

    if(!verificar_arquivo(caminho)) {
        printf("O arquivo deve estar dentro da pasta do executável.\nArquivo inválido\n");
        return false; 
    }

    strcat(caminho_relativo,caminho);

    arquivo = fopen(caminho_relativo,"r");

    if(arquivo == NULL) {
        printf("Erro ao ler o arquivo %s\n", caminho);
        fclose(arquivo);
        return false; 
    }

    fread(texto_lido, 1, tamanho_texto - 1, arquivo);
    fclose(arquivo);
    return true;
}

/*
escreve no arquivo com o nome especificado, desde o arquivo esteja dentro da pasta do executavel
*/
void escrever_arquivo(char caminho[], char texto[]) {
    char caminho_relativo[100] = "./";
    FILE *arquivo;

    if(!verificar_arquivo(caminho)) {
        printf("O arquivo deve estar dentro da pasta do executável.\nArquivo inválido\n");
        return;
    }

    strcat(caminho_relativo,caminho);

    arquivo = fopen(caminho_relativo,"w");
    
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", caminho);
        fclose(arquivo);
        return;
    }

    fwrite(texto,1,strlen(texto),arquivo);
    fclose(arquivo);
}

/*
cria um arquivo dentro do diretório do executável
*/
void criar_arquivo(char caminho[]) {
    char caminho_relativo[100] = "./";
    FILE *arquivo;

    if(!verificar_arquivo(caminho)) {
        printf("O arquivo deve estar dentro da pasta do executável.\nArquivo inválido\n");
        return;
    }

    strcat(caminho_relativo,caminho);
    arquivo = fopen(caminho_relativo, "w");
    fprintf(arquivo," ");
    fclose(arquivo);
}

/*
deleta o arquivo com o nome especificado, desde que o arquivo esteja dentro da pasta do executavel
 */
void deletar_arquivo(char caminho[]) {
  char caminho_relativo[100] = "./";

    if(!verificar_arquivo(caminho)) {
        printf("O arquivo deve estar dentro da pasta do executável.\nArquivo inválido\n");
        return;
    }

    strcat(caminho_relativo,caminho);

    if(remove(caminho_relativo)) {
        printf("Ocorreu um erro ao deletar o arquivo");
    }
}

/*
verifica se um arquivo existe, retorna true se sim e false se não
*/
bool existe_arquivo(char caminho[]) {
    char caminho_relativo[100] = "./";
    FILE *arquivo;

    strcat(caminho_relativo,caminho);
    arquivo = fopen(caminho, "r");

    if (arquivo != NULL) {
        fclose(arquivo); // Fecha o arquivo se ele existir
        return true;        // O arquivo existe
    }
    return false; 
}
/*
verifica se um arquivo binkário existe, retorna true se sim e false se não
*/
bool existe_arquivo_bin(char caminho[]) {
    char caminho_relativo[100] = "./";
    FILE *arquivo;

    strcat(caminho_relativo,caminho);
    arquivo = fopen(caminho, "rb");

    if (arquivo != NULL) {
        fclose(arquivo); // Fecha o arquivo se ele existir
        return true;        // O arquivo existe
    }
    return false; 
}
