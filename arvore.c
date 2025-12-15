#include "estruturas.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//funcao da lista.c para implementar a criacao de lista dentro da insere arvore
void adicionar_linha_lista(NoIndice *no, int linha);

void insere_arvore(NoIndice **raiz, char *palavra, int linha, int *comparacoes) {
    if (*raiz == NULL) {
        NoIndice *novo = (NoIndice*) malloc(sizeof(NoIndice));
        if (!novo) {
            perror("Erro de memoria");
            exit(1);
        }
        novo->palavra = strdup(palavra);
        novo->ocorrencias = 0;
        novo->lista_linhas = NULL;
        novo->prox = NULL;
        novo->esq = NULL;
        novo->dir = NULL;
        
        // Usa a funcao do arquivo lista.c para adicionar a linha
        adicionar_linha_lista(novo, linha);
        
        *raiz = novo;
        return;
}

 if (comparacoes) (*comparacoes)++;

    int cmp = strcmp(palavra, (*raiz)->palavra);

    if (cmp == 0) {
        adicionar_linha_lista(*raiz, linha);
    } else if (cmp < 0) {
        insere_arvore(&((*raiz)->esq), palavra, linha, comparacoes);
    } else {
        insere_arvore(&((*raiz)->dir), palavra, linha, comparacoes);
    }
}


NoIndice* busca_arvore(NoIndice *raiz, char *palavra, int *comparacoes) {
     if (raiz == NULL) {
        return NULL;
    }
    if (comparacoes) (*comparacoes)++;

    int cmp = strcmp(palavra, raiz->palavra);
    if (cmp == 0) {
        return raiz;
    } else if (cmp < 0) {
        return busca_arvore(raiz->esq, palavra, comparacoes);
    } else {
        return busca_arvore(raiz->dir, palavra, comparacoes);
    }
}


int altura_arvore(NoIndice *raiz) {
    t altura_arvore(NoIndice *raiz) {
    if (raiz == NULL) {
        return -1; // Retorna -1 pra folha ter altura 0
    }

    int h_esq = altura_arvore(raiz->esq);
    int h_dir = altura_arvore(raiz->dir);

    if (h_esq > h_dir) {
        return 1 + h_esq;
    }
    else {
        return 1 + h_dir;
    }
 }
    
}
