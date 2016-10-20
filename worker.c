#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h> 

#define ERROR 1

struct mensagem {
	long chave;
	char nome_exec[30];
	char tipo[5];
};

void executa () {
	printf ("WORKER>> EXECUTANDO!!! \n\n");
	sleep(5);
}

int main () {
	
	int queueKey, num_processos;
	//FILE *fp;
	struct mensagem arquivo;

	// OBTER FILA DE MENSAGEM
	if ((queueKey = msgget(602514, 0x124)) < 0 ) {
		printf ("Erro p/ obter a fila de mensagem! \n");
		exit (ERROR);
	}

	arquivo.chave= 4;
	strcpy(arquivo.nome_exec, "ESTOU PRONTO!!! SOLICITANDO TRABALHO!!!");
	strcpy(arquivo.tipo, "00000");
	msgsnd (queueKey, &arquivo, sizeof(arquivo) - sizeof(long), 0);

	msgrcv (queueKey, &arquivo, sizeof(struct mensagem) - sizeof(long), 5, 0);
	printf ("WORKER>> RECEBI MENSAGEM DO PROCESSO MESTRE!!! \n\n");
	//printf("%s\n", arquivo.nome_exec);
	executa ();
	sleep(5);

	arquivo.chave= 7;
	strcpy(arquivo.nome_exec, "EXECUTADO COM SUCESSO!!!\n\n");
	strcpy(arquivo.tipo, "00000");
	msgsnd (queueKey, &arquivo, sizeof(arquivo) - sizeof(long), 0);
	return (0);
}
