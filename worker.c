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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h> 

#define ERROR 1

struct msgbufworker {
	long mtype;
	char mtext[100];
};

void executa () {
	printf ("WORKER>> EXECUTANDO!!! \n\n");
	sleep(5);
}

int main () {

	int queueKey, i = 0;
	struct msgbufworker msgbufw;

	if ((queueKey = msgget(60251, 0666)) < 0 ) {
		printf ("Erro p/ obter a fila de mensagem! \n");
		exit (ERROR);
	}

	while(i < 10) {
		msgrcv (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 7, 0);
		printf ("(WORKER) RECEBI MENSAGEM DO PROCESSO MESTRE!!! \n\n");
		executa ();
		msgbufw.mtype = 5;
		strcpy(msgbufw.mtext, "ESTOU PRONTO!!!");
		msgsnd (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 0);
		sleep(5);
		i++;
	}

	return (0);
}