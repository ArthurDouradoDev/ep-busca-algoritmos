#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

// Forward declarations for functions to be implemented by colleagues
void insere_lista(NoIndice **inicio, char *palavra, int linha);
void insere_arvore(NoIndice **raiz, char *palavra, int linha);
NoIndice* busca_lista(NoIndice *inicio, char *palavra);
NoIndice* busca_arvore(NoIndice *raiz, char *palavra);

// Global variables for text persistence
char **todas_as_linhas = NULL;
int total_linhas = 0;
int capacidade_maxima = 1000;

// Task 3: Sanitizer
void limpa_palavra(char *palavra) {
    char *src = palavra;
    char *dst = palavra;
    
    while (*src) {
        if (isalpha((unsigned char)*src) || isdigit((unsigned char)*src)) {
            *dst = tolower((unsigned char)*src);
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(int argc, char *argv[]) {
    // 1. Verifica argumentos
    if (argc < 3) { 
        printf("Uso: %s <arquivo> <tipo_indice>\n", argv[0]); 
        return 1; 
    }

    int modo_arvore = (strcmp(argv[2], "arvore") == 0);
    NoIndice *inicio = NULL; // Lista
    NoIndice *raiz = NULL;   // Arvore

    // 2. Carrega o texto na memória (Task 2)
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    todas_as_linhas = (char **)malloc(capacidade_maxima * sizeof(char *));
    if (!todas_as_linhas) {
        perror("Erro de memoria");
        return 1;
    }

    char buffer[10000]; // Buffer temporario para leitura
    
    printf(">>>>> Carregando arquivo...\n");

    while (fgets(buffer, sizeof(buffer), f)) {
        // Remove \n
        buffer[strcspn(buffer, "\n")] = 0;

        // Verifica capacidade
        if (total_linhas >= capacidade_maxima) {
            capacidade_maxima *= 2;
            char **novo_ptr = (char **)realloc(todas_as_linhas, capacidade_maxima * sizeof(char *));
            if (!novo_ptr) {
                perror("Erro ao redimensionar memoria");
                return 1;
            }
            todas_as_linhas = novo_ptr;
        }

        // Persistencia
        todas_as_linhas[total_linhas] = strdup(buffer);
        
        // Task 4: Tokenization Loop
        char *copia = strdup(buffer);
        char *token;
        
        // Delimiters: space, comma, dot, dash, exclamation, question
        token = strtok(copia, " ,.-!?\n\r");
        while (token != NULL) {
            if (strlen(token) > 0) {
                limpa_palavra(token);
                if (strlen(token) > 0) {
                    if (modo_arvore) {
                        insere_arvore(&raiz, token, total_linhas + 1);
                    } else {
                        insere_lista(&inicio, token, total_linhas + 1);
                    }
                }
            }
            token = strtok(NULL, " ,.-!?\n\r");
        }
        free(copia);
        total_linhas++;
    }
    fclose(f);
    printf(">>>>> Arquivo carregado! Total de linhas: %d\n", total_linhas);

    // Task 5: Interface de Usuário (CLI) e Busca
    char comando[100];
    char termo[100];
    
    printf("Tipo de indice: '%s'.\n", argv[2]);
    
    while (1) {
        printf("> ");
        if (scanf("%99s", comando) != 1) break;
        
        if (strcmp(comando, "fim") == 0) break;
        
        if (strcmp(comando, "busca") == 0) {
            if (scanf("%99s", termo) != 1) break;
            
            limpa_palavra(termo);
            
            NoIndice *resultado = NULL;
            if (modo_arvore) {
                resultado = busca_arvore(raiz, termo);
            } else {
                resultado = busca_lista(inicio, termo);
            }
            
            if (resultado) {
                printf("Existem %d ocorrências da palavra '%s' nas seguintes linhas:\n", resultado->ocorrencias, termo);
                NoLinha *atual = resultado->lista_linhas;
                while(atual != NULL) {
                    // Imprime a linha original usando o vetor persistente
                    // Note: atual->linha is 1-based, array is 0-based
                    if (atual->linha > 0 && atual->linha <= total_linhas) {
                        printf("%05d: %s\n", atual->linha, todas_as_linhas[atual->linha - 1]);
                    }
                    atual = atual->prox;
                }
            } else {
                printf("Palavra '%s' nao encontrada.\n", termo);
            }
        } else {
            printf("Opcao invalida!\n");
        }
    }

    // Cleanup (Optional but good practice)
    for (int i = 0; i < total_linhas; i++) {
        free(todas_as_linhas[i]);
    }
    free(todas_as_linhas);

    return 0;
}