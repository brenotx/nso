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

int main () {
	
	int queueKey, num_processos, i, j;
	FILE *fp;
	struct mensagem arquivo[1000], aux;
	char * pch;

	i = 0;
	j = 0;

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
	while((fscanf(fp,"%s\n", arquivo[i].nome_exec)!=EOF)) {
		pch = strtok (arquivo[i].nome_exec," <>");
		strcpy (arquivo[i].nome_exec, pch);
		pch = strtok (NULL," <>");
		strcpy (arquivo[i].tipo, pch);
    	
		i++;
	}
	fclose(fp);
	while (j < i) {
		arquivo[j].chave = 2;
		//strcpy(arquivo[i].nome_exec, "IURI");
		//strcpy(arquivo[i].tipo, "10");
		printf ("[%d] --> %s %s\n", j, arquivo[j].nome_exec, arquivo[j].tipo);
		msgsnd (queueKey, &arquivo[j], sizeof(struct mensagem) - sizeof(long), 0);
		printf ("CLIENTE>> Mandei %s, estou aguardando .. \n\n", arquivo[j].nome_exec);
		msgrcv (queueKey, &aux, sizeof(struct mensagem) - sizeof(long), 3, 0);
		//printf("%s\n", arquivo[j].nome_exec);
		j++;
	}
	 
	return (0);
}
