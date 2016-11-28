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
#include "fila.h"

int main(int argc,char *argv[]) {

    int queueKey, i, cont_worker;
    struct msgbuf msgbufrcv;
    struct msgbufworker msgbufw;
    pid_t pid;
    char name_worker[10];

    cont_worker = 0;

    if ((queueKey = msgget(60251, IPC_CREAT | 0666)) < 0 ) {
        printf ("Erro na criação da fila de mensagem! \n");
        exit (ERROR);
    }

    printf("(MESTRE) ESTOU EXECUTANDO\n");
    printf("(MESTRE) CRIANDO PROCESSOS PARA OS WORKERS:\n");
    char buf[200];
    for (i = 0; i < 4; i++){
        pid = fork();
        if (pid == -1) {
            printf("Erro ao criar o processo!\n");
        }
        if (pid == 0){
            printf("\t[Worker %d] Meu pid e %d e o pid do meu pai e %d\n", i, getpid(), getppid());
            break;
        }
        strcpy(name_worker, "worker");
        buf[0] = (char) (cont_worker + '0');
        buf[1] = '\0';
        strcat(name_worker, buf);
        execl(name_worker, name_worker, (char *) 0);
        cont_worker++;
    }

    Fila *one = NULL;
    Fila *five = NULL;
    Fila *ten = NULL;

    // RECEBE MENSAGEM DO CLIENTE
    msgrcv (queueKey, (void *) &msgbufrcv, sizeof(struct msgbuf) - sizeof(long), 1, 0);
    printf ("(MESTRE) RECEBI MENSAGEM DO CLIENTE \n");

    for (i = 0; i < msgbufrcv.num_process; i++) {
        switch(msgbufrcv.msg_info[i].tipo) {
            case 1:
                one = push(one, msgbufrcv.msg_info[i].nome_exec);
                break;
            case 5:
                five = push(five, msgbufrcv.msg_info[i].nome_exec);
                break;
            case 10:
                ten = push(ten, msgbufrcv.msg_info[i].nome_exec);
                break;
        }
        printf ("\tPROCESSO - %s - DO TIPO - %d\n", msgbufrcv.msg_info[i].nome_exec, msgbufrcv.msg_info[i].tipo);
    }

    while(front(one, buf)){
        printf("(MESTRE) MANDANDO O PROCESSO - %s - DO TIPO - 1 PARA WORKER\n", buf);
        msgbufw.mtype = 7;
        msgsnd (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 0);
        one = pop(one);
        msgrcv (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 5, 0);
        printf("(WORKER) %s\n", msgbufw.mtext);

    }
    while(front(five, buf)){
        printf("(MESTRE) MANDANDO O PROCESSO - %s - DO TIPO - 5 PARA WORKER\n", buf);
        msgbufw.mtype = 7;
        msgsnd (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 0);
        five = pop(five);
        msgrcv (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 5, 0);
        printf("(WORKER) %s\n", msgbufw.mtext);

    }
    while(front(ten, buf)){
        printf("(MESTRE) MANDANDO O PROCESSO - %s - DO TIPO - 10 PARA WORKER\n", buf);
        msgbufw.mtype = 7;
        msgsnd (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 0);
        ten = pop(ten);
        msgrcv (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 5, 0);
        printf("(WORKER) %s\n", msgbufw.mtext);

    }
    return (0);
}
