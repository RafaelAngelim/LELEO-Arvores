#ifndef FICHA_H
#define FICHA_H

#include <stdio.h>
#include <stdlib.h>


typedef struct arv {
    int info;
    struct arv* esq;
    struct arv* dir;
} Arv;


Arv* arv_criaVazia();
Arv* arv_cria(int c, Arv* e, Arv* d);
int arv_vazia(Arv* a);
int pares(Arv* a);
int folhas(Arv* a);
int um_filho(Arv* a);
int igual(Arv* a, Arv* b);
Arv* copia(Arv* a);

#endif 