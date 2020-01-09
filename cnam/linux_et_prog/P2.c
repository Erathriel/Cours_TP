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

typedef struct 
{
	long type;
	int valeur;
} tMessage;

int main(int argc, char const *argv[])
{
	int msgid, tailleMsg;
	tMessage req;

	tailleMsg = sizeof(tMessage) - sizeof(long);

	if (argc-1 != 0)
	{
		fprintf(stderr, "Appel %s \n", argv[0]);
		exit(1);
	}
	if ((msgid = msgget(cle,0)) == -1)
	{
		erreur("pb msgget dans P2");
	}

	// construction requete message
	printf("PID du fils : %d\n",getpid() );
	req.type=getpid();
	req.valeur=2;

	// envoi requete message
	if (msgsnd(msgid,&req,tailleMsg,0) == -1){
		perror("Erreur de ecriture P2 requete \n");
		exit(1);
	}
	printf("msgid : %d \n", msgid);
	printf("Valeur envoyé par P2\n");

	// reception requete rep

	//printf("P2 mon pid %d, son pid %d \n", getpid(), rep.numPID);
	return 0;
}