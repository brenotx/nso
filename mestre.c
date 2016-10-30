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
    // struct mensagem receive[10],send;
    struct msgbuf msgbufrcv;
    pid_t pid;
    char name_worker[10];

    cont_worker = 0;

    if ((queueKey = msgget(60251, IPC_CREAT | 0666)) < 0 ) {
        printf ("Erro na criação da fila de mensagem! \n");
        exit (ERROR);
    }

    // char buf[2];
    // for (int i = 0; i <= 4; i++){
    //     pid = fork();
    //     if (pid == -1) {
    //         /* error handling here, if needed */
    //     }
    //     if (pid == 0){
    //         //printf("[Worker %d] Meu pid e %d e o pid do meu pai e %d\n", i, getpid(), getppid());
    //         strcpy(name_worker, "worker");
    //         buf[0] = (char) (cont_worker + '0');
    //         buf[1] = '\0';
    //         strcat(name_worker, buf);
    //         // execl(name_worker, name_worker, (char *) 0);
    //         cont_worker++;
    //         // printf ("MESTRE>> WORKER CRIADO COM SUCCESO!!! \n\n");
    //     }
    // }
    for (int i = 1; i <= 4; i++) {
        pid = fork();
        if (pid == -1) {
            /* error handling here, if needed */
        }
        if (pid == 0) {
            printf("I am a child: %d PID: %d\n",i, getpid());
            sleep (5);
        }
    }



    Fila *one = NULL;
    Fila *five = NULL;
    Fila *ten = NULL;

    printf ("MESTRE>> ESTOU AGUARDANDO MENSAGEM DO CLIENTE: \n\n");
    // RECEBE MENSAGEM DO CLIENTE
    msgrcv (queueKey, (void *) &msgbufrcv, sizeof(struct msgbuf) - sizeof(long), 1, 0);
    printf("%d\n", msgbufrcv.num_process);      

    for (int i = 0; i < msgbufrcv.num_process; i++) {
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

        printf ("MESTRE>> RECEBI O PROCESSO <%s> DO TIPO <%d>\n\n", msgbufrcv.msg_info[i].nome_exec, msgbufrcv.msg_info[i].tipo);
    }

    Fila *aux = one;
    printf("Fila 1:\n");
    while(aux != NULL){
        printf ("Processo %s\n", aux->valor);
        aux = aux->prox;
    }
    aux = five;
    printf("Fila 5:\n");
    while(aux != NULL){
        printf ("Processo %s\n", aux->valor);
        aux = aux->prox;
    }
    aux = ten;
    printf("Fila 10:\n");
    while(aux != NULL){
        printf ("Processo %s\n", aux->valor);
        aux = aux->prox;
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

    
    
    return (0);
}