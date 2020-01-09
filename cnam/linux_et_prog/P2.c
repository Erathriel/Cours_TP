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
	pid_t numPID;
} tMessage;

int main(int argc, char const *argv[])
{
	int msgid, tailleMsg;
	tMessage req, rep;

	tailleMsg = sizeof(tMessage) - sizeof(long);

	if (argc-1 != 0)
	{
		fprintf(stderr, "Appel %s \n", argv[0]);
		exit(1);
	}
	if ((msgid = msget(cle, 0)) == -1)
	{
		erreur("pb msgget dans P2");
	}

	// construction requete message

	// envoi requete message

	// reception requete rep

	printf("P2 mon pid %d, son pid %d \n", getpid(), rep.numPID);
	return 0;
}