/****************************************************
|													|
|			Fichier : sig.c							|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void message1(int n){
	if (n == SIGQUIT)
	{
		printf("%d\n",n );
		printf("SIGQUIT recu \n)");
		exit(1);
	}
	else{
		printf("%d\n",n );
		printf("SIGINT reçu \n");
		exit(2);
	}
}

void message2(int n){printf("Signal %d : recu\n");}

int main(int argc, char const *argv[])
{
	int n;
	signal(SIGINT,message1);
	signal(SIGQUIT,message1);
	signal(SIGUSR1,message2);
	signal(SIGUSR2,message2);
	for (;;){}
	return 0;
}