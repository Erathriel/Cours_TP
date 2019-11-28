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
    int tube[2], tube2[2];
    int ret_out, ret_in;
    char *buffer;

    if (pipe(tube) == -1) {
		erreur("Erreur de creation du pipe tube");
		exit(EXIT_FAILURE);
    }

    if (pipe(tube2) == -1) {
		erreur("Erreur de creation du pipe tube2");
		exit(EXIT_FAILURE);
    }


    buffer = (char *) malloc(NBCAR * sizeof(char));

    printf("...\n");


    switch (pid = fork()) 
	{
		case (pid_t) -1:
			erreur("fork");

		case (pid_t) 0: /* Fils */
			close(tube[1]);	/* Fermeture en ecriture */
			close(tube2[0]);
			// lecture du fils
			if (printf("Je suis le fils de PID %d\n Lecture dans le tube : %s\n Nbr Caracteres lus: %d\n",getpid(), buffer, ret_in =read(tube[0], buffer, NBCAR - 1)) == -1) 
			{
				erreur(" Pb Lecture ");
				exit(EXIT_FAILURE);
			}
			// ecriture dans le tube
			strcpy(buffer, "Je passe dans le tube2");
			fprintf(stdout, "Je suis le fils de PID %d\n Ecriture dans le Tube : %s\n Taille du buffer %d\n",getpid(), buffer, NBCAR);
			if (fprintf(stdout, "\nNombre de caractere ecrit dans le Tube %d\n", ret_out = write(tube2[1], buffer, NBCAR)) == -1) 
			{
				erreur(" Pb Ecriture ");
				exit(EXIT_FAILURE);
			}
			write(tube2[1],buffer,NBCAR);
			close(tube[0]);
			close(tube2[1]);
			exit(0);
			break;
		default:			/* Pere */
			close(tube[0]);		/* Fermeture en lecture */
			close(tube2[1]);
			// ecriture du pere
			strcpy(buffer, "Je passe dans le tube1");
			fprintf(stdout,"Je suis le Pere de PID %d\n Ecriture dans le Tube : %s\n Taille du buffer %d\n",getpid(), buffer, NBCAR);
			if (fprintf(stdout, "\tNombre de caractere ecrit dans le Tube %d\n",ret_out = write(tube[1], buffer, NBCAR)) == -1) 
			{
				erreur(" Pb Ecriture ");
				exit(EXIT_FAILURE);
			}
			// lecture du pere
			if(printf("Je suis le père de PID %d\n Lecture dans le tube : %s\n Nbr Caracteres lus: %d\n",getpid(), buffer, ret_in =read(tube2[0], buffer, NBCAR - 1)) == -1)
			{
			 	erreur("Pb lecture père");
				exit(EXIT_FAILURE);
			}
			close(tube[1]);
			close(tube2[0]);
			wait(NULL);
			break;

	}
    free(buffer);
    return EXIT_SUCCESS;
}