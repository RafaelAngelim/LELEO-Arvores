#ifndef ARVORE_NARIA_H
#define ARVORE_NARIA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no* primeiro_filho;  
    struct no* proximo_irmao;   
} No;

No* novoNo(int valor);

void adicionaFilho(No* pai, No* filho);
int pares(No* raiz);
int folhas(No* raiz);
int um_filho(No* raiz);

int igual(No* a, No* b);

No* copia(No* raiz);

#endif 
