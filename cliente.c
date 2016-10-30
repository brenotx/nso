#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h> 
#include "mestre.h"

int main () {
	
	int queueKey, i;
	FILE *fp;
	// struct mensagem arquivo, aux, mostra[80];
	struct msgbuf msgbuf;
	struct msgbuf msgbufrcv;
	char * pch, str[80];

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

	i = 0;
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
	msgbuf.mtype = 1;
	printf ("[0] --> %s %d\n", msgbuf.msg_info[i].nome_exec, msgbuf.msg_info[i].tipo);
	msgsnd (queueKey, &msgbuf, sizeof(struct msgbuf) - sizeof(long), 0);
	printf ("CLIENTE>> Mandei %s, estou aguardando .. \n\n", msgbuf.msg_info[i].nome_exec);
	// msgrcv (queueKey, (void *) &msgbufrcv, sizeof(struct msgbuf) - sizeof(long), 1, 0);
	// msgrcv (queueKey, &msgbuf, sizeof("RECEBI A MENSAGEM !\n") - sizeof(long), 1, 0);
	//printf("%s\n", arquivo[j].nome_exec);
	 
	return (0);
}