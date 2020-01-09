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

typedef struct 
{
	long type;
	int valeur;
} tMessage;

void erreur(const char *msg){
	perror(msg);
	exit(1);
}

int addition(int valeur1, int valeur2){
	return valeur1 + valeur2;
}

int main(int argc, char const *argv[])
{
	int pid_p2, pid_p3;
	int n, num;
	int msgid;
	int v1, v2;
	tMessage req;
	int tailleMessage = sizeof(tMessage) - sizeof(long);

	if ((msgid = msgget(cle,IPC_CREAT | IPC_EXCL | 0600)) == -1)
	{
		erreur("pb msgget 1....");
	}
	printf("lancement de P1....\n");
	printf("Creation de la file de message.... %d\n", msgid);

	switch(pid_p2 = fork()){
		case -1:{			
			erreur("fork....");
			break;
		}
		case 0:
		{	
			char *arg[3];
			arg[0] = "P2";
			arg[1] = NULL;
			execv("P2", arg);
			exit(2);
		}
		default:
		{			
			printf("Creation de P2 (pid = %d )\n", pid_p2);
			printf("msgid : %d \n", msgid);
			wait(NULL);
			if(msgrcv(msgid,&req,tailleMessage,pid_p2,0) == -1){
				perror("Erreur de lecture P2 requete \n");
				exit(1);
			}
			v1 = req.valeur;
		}
	}
	switch(pid_p3 = fork()){
		case -1:{
			erreur("fork....");
			break;
		}
		case 0:
		{
			char *arg[3];
			arg[0] = "P3";
			arg[1] = NULL;
			execv("P3", arg);
			exit(2);
		}
		default:
		{
			//printf("Creation de P3 (pid = %d )\n", pid_p3);
			if(msgrcv(msgid,&req,tailleMessage,pid_p3,0) == -1){
				perror("Erreur de lecture P3 requete \n");
				exit(1);
			}
			v2 = req.valeur;
		}
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
	printf("Le resultat de %d + %d = %d\n",v1,v2,addition(v1,v2));
	msgctl(msgid, IPC_RMID, NULL);
	printf("P1 termine \n");

	return 0;
}