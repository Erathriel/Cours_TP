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

#define NB_SIGNAUX 3
int signaux[NB_SIGNAUX]={SIGINT,SIGTERM,SIGHUP};

int main(int argc, char const *argv[])
{
	sigset_t masque;
	sigset_t anciens;
	sigset_t pendants;
	int i;
	struct sigaction pourIgnorer;

	/* Creation du masque contenant les trois signaux a bloquer on commence par 
	creer un masque vide avec sigemptyset que l'on remplit ensuite avec sigaddset */

	sigemptyset(&masque);
	for (int i = 0; i < NB_SIGNAUX; ++i)
	{
		sigaddset(&masque,signaux[i]);
	}

	/* Mise en place du masque avec sauvegarde de l'ancien masque dans la variable anciens */
	sigprocmask(SIG_SETMASK,&masque,&anciens);

	/* on s'endort */
	fflush(stdout);
	sleep(5);
	fflush(stdout);

	/* On recupere la liste des signaux pendants */
	sigpending(&pendants);

	/* Decodage des signaux pendants */
	for (int i = 0; i < NB_SIGNAUX; ++i)
	{
		if (sigismember(&pendants,i))
		{
			printf("Signal %d pendant bloque\n", i);
		}
	}


	return 0;
}