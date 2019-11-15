/****************************************************
|													|
|			Fichier : prg1.c						|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void erreur(const char *msg)
{
    perror(msg);
}

#define NBCAR 256

int main(void)
{
    pid_t pid;
    int tube[2];
    int ret_out, ret_in;
    char *buffer;

    if (pipe(tube) == -1) {
	erreur("Erreur de creation du pipe");
	exit(EXIT_FAILURE);
    }


    buffer = (char *) malloc(NBCAR * sizeof(char));


    switch (pid = fork()) {

    case (pid_t) - 1:
	erreur("fork");

    case (pid_t) 0:		/* Fils */
	{
#if 0
	    close(tube[1]);	/* Fermeture en ecriture */
#endif

	    if (printf
		("Je suis le fils de PID %d\n Lecture dans le tube : %s\n Nbr Caracteres lus: %d\n",
		 getpid(), buffer, ret_in =
		 read(tube[0], buffer, NBCAR - 1)) == -1) {
		erreur(" Pb Lecture ");
		exit(EXIT_FAILURE);
	    }
#if 0
	    close(tube[0]);
#endif

	    exit(0);
	    break;
	}

    default:			/* Pere */

#if 0
	close(tube[0]);		/* Fermeture en lecture */
#endif

	strcpy(buffer, "Je passe dans le tube");
	fprintf(stdout,
		"Je suis le Pere de PID %d\n Ecriture dans le Tube : %s\n Taille du buffer %d\n",
		getpid(), buffer, NBCAR);
	if (fprintf
	    (stdout, "Nombre de caractere ecrit dans le Tube %d\n",
	     ret_out = write(tube[1], buffer, NBCAR)) == -1) {
	    erreur(" Pb Ecriture ");
	    exit(EXIT_FAILURE);
	}
#if 0
	close(tube[1]);
#endif

	wait(NULL);
	break;

    }

    free(buffer);
    return EXIT_SUCCESS;
}