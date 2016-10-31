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
    printf("(MESTRE) ESTOU ESPERANDO SINAL DE ALGUM WORKER\n");
    char buf[200];
    for (i = 0; i < 4; i++){
        pid = fork();
        if (pid == -1) {
            /* error handling here, if needed */
        }
        if (pid == 0){
            //printf("[Worker %d] Meu pid e %d e o pid do meu pai e %d\n", i, getpid(), getppid());
            break;
            // printf ("MESTRE>> WORKER CRIADO COM SUCCESO!!! \n\n");
        }
        strcpy(name_worker, "worker");
        buf[0] = (char) (cont_worker + '0');
        buf[1] = '\0';
        strcat(name_worker, buf);
        execl(name_worker, name_worker, (char *) 0);
        cont_worker++;
    }

    msgrcv (queueKey, &msgbufw, sizeof(struct msgbufworker) - sizeof(long), 5, 0);
    printf("(WORKER) %s\n", msgbufw.mtext);

    Fila *one = NULL;
    Fila *five = NULL;
    Fila *ten = NULL;
    
    printf ("(MESTRE) ESTOU AGUARDANDO MENSAGEM DO CLIENTE: \n\n");
    // RECEBE MENSAGEM DO CLIENTE
    msgrcv (queueKey, (void *) &msgbufrcv, sizeof(struct msgbuf) - sizeof(long), 1, 0);

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
        printf ("(MESTRE) RECEBI O PROCESSO - %s - DO TIPO - %d\n", msgbufrcv.msg_info[i].nome_exec, msgbufrcv.msg_info[i].tipo);
    }

    // printf("Fila 1:\n");
    while(front(one, buf)){
        printf ("Processo na fila one %s\n", buf);
        one = pop(one);
    }
    while(front(five, buf)){
        printf ("Processo na fila five %s\n", buf);
        five = pop(five);
    }
    while(front(ten, buf)){
        printf ("Processo na fila ten %s\n", buf);
        ten = pop(ten);
    }


    // MANDA PARA O WORKER
    printf("(MESTRE) MANDANDO O PROCESSO - %s - DO TIPO - %d PARA WORKER\n\n", msgbufrcv.msg_info[i].nome_exec, msgbufrcv.msg_info[i].tipo);
    // msgbufrcv.msg_info[i].chave = 5;
    // sleep(2);
    // msgsnd (queueKey, &receive, sizeof(receive) - sizeof(long), 0);

    // // RECEBE CONFIRMACAO DO WORKER
    // msgrcv (queueKey, &receive, sizeof(struct mensagem) - sizeof(long), 7, 0);
    // printf ("\n\nMESTRE>> CONFIRMACAO : %s", msgbufrcv.msg_info[i].nome_exec);

    // //MANDA CONFIRMACAO PARA O CLIENTE
    // send.chave = 3;
    // strcpy(receive[i].nome_exec,"RECEBI A MENSAGEM !\n");
    // strcpy(receive[i].tipo,"0");
    // msgsnd (queueKey, &send, sizeof("RECEBI A MENSAGEM !\n") - sizeof(long), 0);

    
    
    return (0);
}
