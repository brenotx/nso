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

	int queueKey;
	struct msgbufworker msgbufw;

	if ((queueKey = msgget(60251, 0666)) < 0 ) {
		printf ("Erro p/ obter a fila de mensagem! \n");
		exit (ERROR);
	}

	msgbufw.mtype = 5;
	strcpy(msgbufw.mtext, "ESTOU PRONTO!!!");
	msgsnd (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 0);

	msgrcv (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 100, 0);
	printf ("(WORKER) RECEBI MENSAGEM DO PROCESSO MESTRE!!! \n\n");
	executa ();
	sleep(5);

	// msgbufw.mtype = 7;
	// strcpy(msgbufw.mtext, "EXECUTADO COM SUCESSO!!!\n\n");
	// msgsnd (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 0);
	return (0);
}