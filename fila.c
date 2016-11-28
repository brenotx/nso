/*
Alunos: Breno Teixeira - 10/0026087, Iuri Batista Beserra - 11/0013620

Sistema Operacional : OS X Yosemite - v10.10.5

Versão do Compilador: Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 7.0.2 (clang-700.1.81)
Target: x86_64-apple-darwin14.5.0
Thread model: posix

Ordem de execução dos processos: Executar primeiro o Mestre e em seguida execute o Cliente. Compile o worker.c para criar 4 executáveis,
como exemplo: gcc worker.c -o worker0 worker.c

Mecanismos IPCS utilizados : Fila de mensagens.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Inicia uma fila
Fila *nova_fila() {
    return NULL;
}

// Verificar se uma fila está vazia
int fila_vazia(Fila *f) {
    if(f==NULL)
        return 1;
    else
        return 0;
}

// Inserir elementos na fila
Fila *push(Fila *u, char *valor) {
    Fila *temp = u;
    Fila *novo = (Fila*)malloc(sizeof(Fila));
    novo -> valor = malloc((sizeof (char)) * (strlen(valor)+1));
    strcpy(novo->valor, valor);
    novo -> prox = NULL;

    if(fila_vazia(u))
    return novo; 

    while(temp -> prox != NULL) {
        temp = temp -> prox;
    }
    temp->prox = novo;

    return u;         
}

//   Remover elementos da fila
Fila* pop(Fila* f) {
    if(fila_vazia(f))
       return NULL;
    Fila *temp = f -> prox;
    free(f);
    return temp;
}

int front(Fila *f, char *ret) {
    if(fila_vazia(f)) {
      return 0;
    }
    strcpy(ret, f->valor);
    return 1;
}
