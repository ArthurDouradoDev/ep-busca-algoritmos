#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>

// Nó da lista de ocorrências (linhas onde a palavra aparece)
typedef struct NoLinha {
    int linha;
    struct NoLinha *prox;
} NoLinha;

// Nó do índice (A palavra e seus dados)
typedef struct NoIndice {
    char *palavra;
    int ocorrencias;
    NoLinha *lista_linhas; // Cabeça da lista de linhas

    // Ponteiros para as estruturas de dados
    struct NoIndice *prox; // Usado se for Lista Ligada
    struct NoIndice *esq;  // Usado se for Árvore
    struct NoIndice *dir;  // Usado se for Árvore
} NoIndice;

#endif