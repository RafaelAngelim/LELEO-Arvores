#include "ficha.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct no No;


int pares(No* raiz) {
    if (raiz == NULL) return 0;
    int count = (raiz->info % 2 == 0) ? 1 : 0;
    No* filho = raiz->primeiro_filho;
    while (filho != NULL) {
        count += pares(filho);
        filho = filho->proximo_irmao;
    }
    return count;
}

int folhas(No* raiz) {
    if (raiz == NULL) return 0;
    if (raiz->primeiro_filho == NULL) return 1;

    int count = 0;
    No* filho = raiz->primeiro_filho;
    while (filho != NULL) {
        count += folhas(filho);
        filho = filho->proximo_irmao;
    }
    return count;
}

int um_filho(No* raiz) {
    if (raiz == NULL) return 0;
    
    int count = 0;
    if (raiz->primeiro_filho != NULL && raiz->primeiro_filho->proximo_irmao == NULL) {
        count = 1;
    }

    No* filho = raiz->primeiro_filho;
    while (filho != NULL) {
        count += um_filho(filho);
        filho = filho->proximo_irmao;
    }
    return count;
}

int igual(No* a, No* b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    if (a->info != b->info) return 0;

    No* filho_a = a->primeiro_filho;
    No* filho_b = b->primeiro_filho;
    while (filho_a != NULL && filho_b != NULL) {
        if (!igual(filho_a, filho_b)) return 0;
        filho_a = filho_a->proximo_irmao;
        filho_b = filho_b->proximo_irmao;
    }
    return (filho_a == NULL && filho_b == NULL);
}

No* copia(No* raiz) {
    if (raiz == NULL) return NULL;

    No* nova_raiz = (No*)malloc(sizeof(No));
    nova_raiz->info = raiz->info;
    nova_raiz->primeiro_filho = copia(raiz->primeiro_filho);
    nova_raiz->proximo_irmao = copia(raiz->proximo_irmao);

    return nova_raiz;
}

No* novoNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->info = valor;
    novo->primeiro_filho = NULL;
    novo->proximo_irmao = NULL;
    return novo;
}

void adicionaFilho(No* pai, No* filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        No* irmao = pai->primeiro_filho;
        while (irmao->proximo_irmao != NULL) {
            irmao = irmao->proximo_irmao;
        }
        irmao->proximo_irmao = filho;
    }
}

int main() {
    No* raiz = novoNo(1);
    No* filho1 = novoNo(2);No* filho2 = novoNo(3);
    No* filho3 = novoNo(4);No* filho4 = novoNo(5);
    No* filho5 = novoNo(6);

    adicionaFilho(raiz, filho1);
    adicionaFilho(raiz, filho2);
    adicionaFilho(filho1, filho3);
    adicionaFilho(filho1, filho4);
    adicionaFilho(filho2, filho5);

    printf("qtd de nos pares: %d\n", pares(raiz));
    printf("qtd de folhas: %d\n", folhas(raiz));
    printf("qtd de nos com um filho: %d\n", um_filho(raiz));

    No* copia_arvore = copia(raiz);
    printf("as arv sao iguais? %s\n", igual(raiz, copia_arvore) ? "Sim" : "Não");

    return 0;
}