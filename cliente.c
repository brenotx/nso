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
	long mtype;       				/* message type, must be > 0 */
	struct msg_info msg_info[10];    	/* message data */
	int num_process;
};

int main () {
	
	int queueKey, num_processos, i, j, k;
	FILE *fp;
	// struct mensagem arquivo, aux, mostra[80];
	struct msgbuf msgbuf;
	char * pch, str[80];

	i = 0;
	j = 0;
	k = 0;

	// OBTER FILA DE MENSAGEM
	if ((queueKey = msgget(60251, 0666)) < 0 ) {
		printf ("Erro p/ obter a fila de mensagem! \n");
		exit (ERROR);
	}

	fp = fopen("arquivo.txt","r");
	if(!fp){
    	printf( "Erro ao abrir o arquivo\n");
    	exit(0);
	}

	msgbuf.num_process = 0;
	char input_file[1000];
	while((fscanf(fp,"%s\n", input_file)!=EOF)) {
		pch = strtok (input_file," <>");
		strcpy (msgbuf.msg_info[i].nome_exec, pch);
		pch = strtok (NULL," <>");
		msgbuf.msg_info[i].tipo = atoi(pch);
		// strcpy (msgbuf.msg_info[i].tipo, pch);
		msgbuf.num_process++;
		i++;
	}
/*	//Abre o arquivo apontado por arq e lê do primeiro caractér ate um newLine e armazena na string str. 
  	while(fgets(str, 80, fp) != NULL){

  	//Imprime em cada repetição a linha que foi armazenada em str.     
      printf("%s", str);
      //file.mtype = 1;
      strcpy(mostra.recebe[k], str);
      k++;
  	}
*/
	fclose(fp);
	//while (j < i) {
		// arquivo[j].chave = 2;
		msgbuf.mtype = 1;
		//strcpy(arquivo[i].nome_exec, "IURI");
		//strcpy(arquivo[i].tipo, "10");
		printf ("[%d] --> %s %d\n", j, msgbuf.msg_info[i].nome_exec, msgbuf.msg_info[i].tipo);
		msgsnd (queueKey, &msgbuf, sizeof(struct msgbuf) - sizeof(long), 0);
		printf ("CLIENTE>> Mandei %s, estou aguardando .. \n\n", msgbuf.msg_info[i].nome_exec);
		// msgrcv (queueKey, &aux, sizeof("RECEBI A MENSAGEM !\n") - sizeof(long), 3, 0);
		//printf("%s\n", arquivo[j].nome_exec);
		j++;
	//}
	 
	return (0);
}