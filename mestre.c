#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h> 

#define ERROR 1

// struct mensagem {
// 	long chave;
// 	char nome_exec[30];
// 	char tipo[5];
// };

struct msg_info {
	char nome_exec[30];
	int tipo;
};

struct msgbuf {
	long mtype;       					/* message type, must be > 0 */
	struct msg_info msg_info[10];    	/* message data */
	int num_process;
};

int main(int argc,char *argv[]) {

	int queueKey, i, cont_worker;
	// struct mensagem receive[10],send;
	struct msgbuf msgbufrcv;
	pid_t pid;
	char name_worker[8], ccont_worker;

	// cont_worker = 0;

	if ((queueKey = msgget(60251, IPC_CREAT | 0666)) < 0 ) {
		printf ("Erro na criação da fila de mensagem! \n");
		exit (ERROR);
	}

/*	for (int i = 0; i < 4; i++){
    	if (fork() == 0){
    		//printf("[Worker %d] Meu pid e %d e o pid do meu pai e %d\n", i, getpid(), getppid());
    		strcpy(name_worker, "worker");
    		ccont_worker = (char) cont_worker;
    		strcat(name_worker, ccont_worker);
    		execl(name_worker, name_worker, (char *) 0);
    		cont_worker++;
    	}
    }
*/
    /*if ((pid = fork()) < 0) {
        perror("Erro no fork");
        exit(ERROR);
    }
    if (pid == 0) {
    	execl("worker1", "worker1", (char *) 0);
    	
    }
    printf ("MESTRE>> WORKER CRIADO COM SUCCESO!!! \n\n");*/


	// while (1) {
		printf ("MESTRE>> ESTOU AGUARDANDO MENSAGEM DO CLIENTE: \n\n");
		// RECEBE MENSAGEM DO CLIENTE
		msgrcv (queueKey, (void *) &msgbufrcv, sizeof(struct msgbuf) - sizeof(long), 1, 0);
		printf("%d\n", msgbufrcv.num_process);		

		for (int i = 0; i < msgbufrcv.num_process; i++) {
			printf ("MESTRE>> RECEBI O PROCESSO <%s> DO TIPO <%d>\n\n", msgbufrcv.msg_info[i].nome_exec, msgbufrcv.msg_info[i].tipo);
		}

		// i++;
		/*// MANDA PARA O WORKER
		printf("MESTRE>> MANDANDO O PROCESSO <%s> DO TIPO <%s> PARA WORKER\n\n", receive.nome_exec, receive.tipo);
		receive.chave = 5;
		sleep(2);
		msgsnd (queueKey, &receive, sizeof(receive) - sizeof(long), 0);

		// RECEBE CONFIRMACAO DO WORKER
		msgrcv (queueKey, &receive, sizeof(struct mensagem) - sizeof(long), 7, 0);
		printf ("\n\nMESTRE>> CONFIRMACAO : %s", receive.nome_exec);*/

		//MANDA CONFIRMACAO PARA O CLIENTE
		// send.chave = 3;
		//strcpy(receive[i].nome_exec,"RECEBI A MENSAGEM !\n");
		//strcpy(receive[i].tipo,"0");
		// msgsnd (queueKey, &send, sizeof("RECEBI A MENSAGEM !\n") - sizeof(long), 0);

		
		
	// }
	return (0);
}