#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "fila.h"

// —————————— //
// Inicia uma fila
// —————————– //

Fila *nova_fila(){
    return NULL;
}

// —————————— //
// Verificar se uma fila está vazia
// —————————– //

int fila_vazia(Fila *f){ /* verifica se a fila esta vazia */
    if(f==NULL)
        return 1;
    else
        return 0;
}

// —————————— //
// Inserir elementos na fila
// —————————– //

Fila *push(Fila *u, char *valor)
{

   Fila *temp = u;
   Fila *novo = (Fila*)malloc(sizeof(Fila));
   novo -> valor = malloc((sizeof (char)) * (strlen(valor)+1));
   strcpy(novo->valor, valor);
   novo -> prox = NULL;

   if(fila_vazia(u))
   return novo; 

   while(temp -> prox != NULL)
   {
    temp = temp -> prox;
   }

   temp->prox = novo;

    return u;         
}

// ------------------------------ //
//   Remover elementos da fila
// ----------------------------- //

Fila* pop(Fila* f)
{
    if(fila_vazia(f))
       return NULL;
    Fila *temp = f -> prox;
    free(f);
    return temp;
}