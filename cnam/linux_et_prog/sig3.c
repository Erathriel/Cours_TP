/****************************************************
|													|
|			Fichier : sig3.c						|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void message1(int n){
	printf("Message 1 : Signal %d : recu\n", n);
	//sleep(2);
	//kill(getppid(),SIGUSR2);
}
void message2(int n){printf("Message 2 : Signal %d : recu\n", n);}

int main(int argc, char const *argv[])
{
	extern int errno;
	extern int *sys_errlist[];
	pid_t pid;

	signal(SIGUSR1,message1);
	signal(SIGUSR2,message2);
	pid=fork();

	switch(pid){
		case -1:
			fprintf(stderr,"Error %d in fork: %s\n", errno,sys_errlist[errno]);
			exit(errno);
		case 0: // Dans le fils
			sleep(2);
			printf("Je suis dans le fils\n");
			kill(getppid(),SIGUSR2);
			exit(0);
			break;
		default: // Dans le pere
			printf("Je suis dans le père\n");
			kill(pid,SIGUSR1);
			pause();
			wait(SIGCHLD);
	}

	return 0;
}