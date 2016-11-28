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
#include "mestre.h"

int main () {
	
	int queueKey, i;
	FILE *fp;
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
		msgbuf.num_process++;
		i++;
	}

	fclose(fp);
	msgbuf.mtype = 1;
	//printf ("[0] --> %s %d\n", msgbuf.msg_info[i].nome_exec, msgbuf.msg_info[i].tipo);
	msgsnd (queueKey, &msgbuf, sizeof(struct msgbuf) - sizeof(long), 0);
	printf ("CLIENTE>> Mandei %s, estou aguardando .. \n\n", msgbuf.msg_info[i].nome_exec);
	 
	return (0);
}