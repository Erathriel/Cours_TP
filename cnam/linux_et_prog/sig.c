/****************************************************
|													|
|			Fichier : prg4.c						|
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
		printf("SIGQUIT recu \n)");
		exit(1);
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