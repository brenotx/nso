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
	
	int queueKey, num_processos;
	//FILE *fp;
	struct mensagem arquivo;


	// OBTER FILA DE MENSAGEM
	if ((queueKey = msgget(602514, 0x124)) < 0 ) {
		printf ("Erro p/ obter a fila de mensagem! \n");
		exit (ERROR);
	}


	//fp = fopen (argv[1], "r");
    	//while ((c = fgetc(fp)) != EOF) {
	     //   if((char) c != ',' && (char) c != ' ' ) {
	        //	caracter[0] = (char) c;
	        	arquivo.chave= 2;
	        	strcpy(arquivo.nome_exec, "IURI");
				strcpy(arquivo.tipo, "10");
				msgsnd (queueKey, &arquivo, sizeof(arquivo) - sizeof(long), 0);
				printf ("CLIENTE>> Mandei %s, estou aguardando .. \n\n", arquivo.nome_exec);
				msgrcv (queueKey, &arquivo, sizeof(struct mensagem) - sizeof(long), 3, 0);

				printf("%s\n", arquivo.nome_exec);

	 //   fclose(fp);
	return (0);
}
