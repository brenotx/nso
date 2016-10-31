#include "mestre.h"

typedef struct fila{
    char *valor;
    struct fila *prox;
} Fila;

Fila *nova_fila();
int fila_vazia(Fila *f);
Fila *push(Fila *u, char *valor);
Fila *pop(Fila* f);
int front(Fila *f, char *ret);
