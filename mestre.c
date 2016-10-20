#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h> 

#define ERROR 				1

struct mensagem {
	long chave;
	char nome_exec[30];
	char tipo[5];
};

int main(int argc,char *argv[]) {

	int queueKey;
	struct mensagem receive;
	pid_t pid;

		
	if ((queueKey = msgget(602514, IPC_CREAT | 0x1FF)) < 0 ) {
		printf ("Erro na criação da fila de mensagem! \n");
		exit (ERROR);
	}



    if ((pid = fork()) < 0) {
        perror("Erro no fork");
        exit(ERROR);
    }
    if (pid == 0) {
    	execl("worker1", "worker1", (char *) 0);
    	
    }
    printf ("MESTRE>> WORKER CRIADO COM SUCCESO!!! \n\n");



	while (1) {
		printf ("MESTRE>> ESTOU AGUARDANDO MENSAGEM DO CLIENTE: \n\n");
		// RECEBE MENSAGEM DO CLIENTE
		msgrcv (queueKey, &receive, sizeof(struct mensagem) - sizeof(long), 2, 0);
		printf ("MESTRE>> RECEBI O PROCESSO <%s> DO TIPO <%s>\n\n", receive.nome_exec, receive.tipo);
		sleep(5);

		// MANDA PARA O WORKER
		printf("MESTRE>> MANDANDO O PROCESSO <%s> DO TIPO <%s> PARA WORKER\n\n", receive.nome_exec, receive.tipo);
		receive.chave = 5;
		sleep(2);
		msgsnd (queueKey, &receive, sizeof(receive) - sizeof(long), 0);

		// RECEBE CONFIRMACAO DOOO WORKER
		msgrcv (queueKey, &receive, sizeof(struct mensagem) - sizeof(long), 7, 0);
		printf ("\n\nMESTRE>> CONFIRMACAO : %s", receive.nome_exec);

		//MANDA CONFIRMACAO PARA O CLIENTE
		receive.chave = 3;
		strcpy(receive.nome_exec,"RECEBI A MENSAGEM !\n");
		strcpy(receive.tipo,"0");
		sleep(2);
		msgsnd (queueKey, &receive, sizeof(receive) - sizeof(long), 0);
		
	}
	return (0);
}
