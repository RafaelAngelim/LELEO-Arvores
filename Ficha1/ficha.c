#include "ficha.h"

Arv* arv_criaVazia() {
    return NULL;
}

Arv* arv_cria(int c, Arv* e, Arv* d) {
    Arv* a = (Arv*) malloc(sizeof(Arv));
    a->info = c;
    a->esq = e;
    a->dir = d;
    return a;
}

int arv_vazia(Arv* a) {
    return a == NULL;
}

// Questão 1
int pares(Arv* a) {
    if (arv_vazia(a)) return 0;
    int conta = (a->info % 2 == 0) ? 1 : 0; 
    return conta + pares(a->esq) + pares(a->dir);
}

// Questão 2
int folhas(Arv* a) {
    if (arv_vazia(a)) return 0;
    if (a->esq == NULL && a->dir == NULL) return 1;
    return folhas(a->esq) + folhas(a->dir);
}

// Questão 3
int um_filho(Arv* a) {
    if (arv_vazia(a)) {
        return 0;
    }
    int cont = 0;
    if ((a->esq == NULL && a->dir != NULL) || (a->esq != NULL && a->dir == NULL)) {
        cont = 1;
    }
    return cont + um_filho(a->esq) + um_filho(a->dir);
}

// Questão 4
int igual(Arv* a, Arv* b) {
    if (arv_vazia(a) && arv_vazia(b)) return 1; 
    if (arv_vazia(a) || arv_vazia(b)) return 0; 
    return (a->info == b->info) && igual(a->esq, b->esq) && igual(a->dir, b->dir);
}

// Questão 5
Arv* copia(Arv* a) {
    if (arv_vazia(a)) {
        return NULL;
    }
    Arv* nova = (Arv*) malloc(sizeof(Arv));
    if (nova == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    nova->info = a->info;
    nova->esq = copia(a->esq);
    nova->dir = copia(a->dir);
    return nova;
}

int main() {
    Arv* a1 = arv_cria(1, NULL, NULL);
    Arv* a4 = arv_cria(4, NULL, NULL);
    Arv* a6 = arv_cria(6, NULL, NULL);
    Arv* a7 = arv_cria(7, a6, NULL);
    Arv* a10 = arv_cria(10, NULL, NULL);

    Arv* a3 = arv_cria(3, a1, a4);
    Arv* a8 = arv_cria(8, a7, a10);
    
    Arv* raiz = arv_cria(5, a3, a8);

    printf("arvore esta vazia? %d\n", arv_vazia(raiz)); 

    int num_pares = pares(raiz);
    printf("Quantidade de nos pares: %d\n", num_pares); 

    int num_folhas = folhas(raiz);
    printf("Quantidade de folhas: %d\n", num_folhas); 

    int num_um_filho = um_filho(raiz);
    printf("Quantidade de nos com um filho: %d\n", num_um_filho);

    Arv* copia_raiz = copia(raiz);
    printf("arvore copiada e igual? %d\n", igual(raiz, copia_raiz)); 

    
    free(a1);
    free(a4);
    free(a6);
    free(a7);
    free(a10);
    free(a3);
    free(a8);
    free(raiz);
    free(copia_raiz);

    return 0;
}
