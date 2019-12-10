/****************************************************
|													|
|			Fichier : sig4.c						|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void message1(int n){
	printf("SIGINT: Signal %d : recu\n", n);
	printf("mess recu\n");
	printf("Entree attente2 \n");
	sleep(10);
	printf("Sortie attente2 \n");
	signal(SIGINT,message1);
	return;
}

int main(int argc, char const *argv[])
{
	extern int errno;
	extern int *sys_errlist[];
	int n = 0;
	pid_t pid;

	//signal(SIGINT,message1);
	struct sigaction action; // struct qui remplace signal(SIGINT,message1);

	action.sa_handler = message1; // init du traitant
	sigemptyset(&(action.sa_mask));	// masque de traitant
	action.sa_flag=0; // pas de flag
	sigaction(SIGINT, &action,NULL); // installation du traitant pour le signal SIGINT

	pid=fork();

	switch(pid){
		case -1:
			fprintf(stderr,"Error %d in fork: %s\n", errno,sys_errlist[errno]);
			exit(errno);
		case 0: // Dans le fils
			printf("Je suis dans le fils\n");
			sleep(10);
			break;
		default: // Dans le pere
			printf("Je suis dans le père\n");
			sleep(5);
			printf("sortie attente\n");
			for (int i = 0; i < 100; ++i);
			printf("Infos traitée\n");
	}

	return 0;
}