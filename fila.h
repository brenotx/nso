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
