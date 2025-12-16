#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"

// Variaveis globais para persistencia do texto
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

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    // 1. Verifica argumentos
    if (argc < 3) { 
        printf("Uso: %s <arquivo> <tipo_indice>\n", argv[0]); 
        return 1; 
    }

    int modo_arvore = (strcmp(argv[2], "arvore") == 0);
    NoIndice *inicio = NULL; // Lista
    NoIndice *raiz = NULL;   // Arvore

    int comparacoes_construcao = 0;
    
    // 2. Carrega o texto na memória
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

    char buffer[10000]; // Armazenamento temporario para leitura
    

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
        
        // Loop de tokenizacao
        char *copia = strdup(buffer);
        char *token;
        
        // Delimitadores: espaço, vírgula, ponto, traço, exclamação, interrogação
        token = strtok(copia, " ,.-!?\n\r:;\"'()[]{}/");
        while (token != NULL) {
            if (strlen(token) > 0) {
                limpa_palavra(token);
                if (strlen(token) > 0) {
                    if (modo_arvore) {
                        insere_arvore(&raiz, token, total_linhas + 1, &comparacoes_construcao);
                    } else {
                        insere_lista(&inicio, token, total_linhas + 1, &comparacoes_construcao);
                    }
                }
            }
            token = strtok(NULL, " ,.-!?\n\r:;\"'()[]{}/");
        }
        free(copia);
        total_linhas++;
    }
    fclose(f);
    printf("Arquivo: '%s'\n", argv[1]);
    printf("Tipo de indice: '%s'\n", argv[2]);
    printf("Numero de linhas no arquivo: %d\n", total_linhas);
    int total_palavras = 0;
    if (modo_arvore) {
        total_palavras = conta_nos_arvore(raiz);
    } else {
        total_palavras = conta_nos_lista(inicio);
    }
    printf("Total de palavras unicas indexadas: %d\n", total_palavras); 

    if (modo_arvore) {
        printf("Altura da arvore: %d\n", altura_arvore(raiz)); 
    }
    printf("Numero de comparacoes realizadas para a construcao do indice: %d\n", comparacoes_construcao);

    // Interface de Usuário (CLI) e Busca
    char comando[100];
    char termo[100];
    
    
    while (1) {
        printf("> ");
        if (scanf("%99s", comando) != 1) break;
        
        if (strcmp(comando, "fim") == 0) break;
        
        if (strcmp(comando, "busca") == 0) {
            if (scanf("%99s", termo) != 1) break;
            
            limpa_palavra(termo);

            int comparacoes_busca = 0;
            NoIndice *resultado = NULL;
            if (modo_arvore) {
                resultado = busca_arvore(raiz, termo, &comparacoes_busca);
            } else {
                resultado = busca_lista(inicio, termo, &comparacoes_busca);
            }
            
            if (resultado) {
                printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", resultado->ocorrencias, termo);
                NoLinha *atual = resultado->lista_linhas;
                while(atual != NULL) {
                    // Imprime a linha original (linhas começam em 1, mas o array começa em 0)
                    if (atual->linha > 0 && atual->linha <= total_linhas) {
                        printf("%05d: %s\n", atual->linha, todas_as_linhas[atual->linha - 1]);
                    }
                    atual = atual->prox;
                }
            } else {
                printf("Palavra '%s' nao encontrada.\n", termo);
            }
            printf("Numero de comparacoes: %d\n", comparacoes_busca);
        } else {
            printf("Opcao invalida!\n");
        }
    }

    // Limpeza e liberacao da memoria
    for (int i = 0; i < total_linhas; i++) {
        free(todas_as_linhas[i]);
    }
    free(todas_as_linhas);

    return 0;
}