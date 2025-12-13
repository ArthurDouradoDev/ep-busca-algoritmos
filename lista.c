#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

NoIndice* criar_no_lista(char *palavra) {
    NoIndice *novo = (NoIndice*) malloc(sizeof(NoIndice));
    novo->palavra = strdup(palavra); 
    novo->ocorrencias = 0;
    novo->lista_linhas = NULL;
    novo->prox = NULL;
    novo->esq = NULL; // Não usado na lista
    novo->dir = NULL; // Não usado na lista
    return novo;
}

void adicionar_linha_lista(NoIndice *no, int linha) {
    no->ocorrencias++;
    
    NoLinha *nova_linha = (NoLinha*) malloc(sizeof(NoLinha));
    nova_linha->linha = linha;
    nova_linha->prox = NULL;

    if (no->lista_linhas == NULL) {
        no->lista_linhas = nova_linha;
    } else {
        NoLinha *atual = no->lista_linhas;
        
        // Verifica se a última linha inserida é a mesma da atual para nao duplicar na hora de listar

        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        
        if (atual->linha != linha) { 
            atual->prox = nova_linha;
        } else {
            // Se já adicionou esta linha para esta palavra, mantém só o incremento feito antes
            free(nova_linha);
        }
    }
}

void insere_lista(NoIndice **inicio, char *palavra, int linha, int *comparacoes) {
    NoIndice *atual = *inicio;

    while (atual != NULL) {
        if (comparacoes) (*comparacoes)++; 
        
        int cmp = strcmp(atual->palavra, palavra);
        
        if (cmp == 0) {
            adicionar_linha_lista(atual, linha);
            return;
        }
        
        atual = atual->prox;
    }

    // Se saiu do loop tem que criar um novo nó
    NoIndice *novo = criar_no_lista(palavra);
    adicionar_linha_lista(novo, linha);

    novo->prox = *inicio;
    *inicio = novo;
}

NoIndice* busca_lista(NoIndice *inicio, char *palavra, int *comparacoes) {
    NoIndice *atual = inicio;

    while (atual != NULL) {
        // Conta a comparação do strcmp abaixo
        if (comparacoes) (*comparacoes)++;

        if (strcmp(atual->palavra, palavra) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL;
}