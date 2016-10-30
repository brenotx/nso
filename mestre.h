#define ERROR 1

typedef struct msg_info {
	char nome_exec[30];
	int tipo;
} Info;

struct msgbuf {
	long mtype;       		/* message type, must be > 0 */
	Info msg_info[10];    	/* message data */
	int num_process;
};