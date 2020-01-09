/*
created by : Geoffrey NORO
date : 09/01/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define cle 314

void erreur(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int pid_p2, pid_3;
	int n, num
	int msgid;

	if (msgid == msgget(cle,IPC_CREAT | IPC_EXECL | 0600) == -1)
	{
		erreur("pb msgget 1....");
	}
	printf("lancement de P1....\n");
	printf("Creation de la file de message.... %d\n", msgid);

	switch(pid_p2 == fork()){
		case -1:
			erreur("fork....");
			break;
		case 0:
			char *arg[3];
			arg[0] = "P2";
			arg[1] = NULL;
			execv("P2", arg);
			exit(2);
		default:
			printf("Creation de P2 (pid = %d \n", pid_p2);
	}
	switch(pid_p3 == fork()){
		case -1:
			erreur("fork....");
			break;
		case 0:
			char *arg[3];
			arg[0] = "P3";
			arg[1] = NULL;
			execv("P3", arg);
			exit(2);
		default:
			printf("Creation de P3 (pid = %d \n", pid_p3);
	}

	for (int i = 0; i <= 1; ++i)
	{
		num = wait(NULL);
		if (num == pid_p2)
		{
			printf("P2 termine \n");
		}
		else{
			printf("P3 termine \n");
		}
	}

	printf("P1 termine \n");

	return 0;
}