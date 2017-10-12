/***************************************************

Fichier : tp3_ex1.c
Date de creation : 03 octobre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// creation et initialisation du mutex
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

/* definition d'une structure arguments permettant de passer en paramêtre 
à un thread plusieurs arguments */
typedef struct
{
	int min;
	int max;
	int taille;
	int nLigne;
	int somme;
	int **matrix;
	
} arguments;

void *thread(void *arg){
	arguments *args = (arguments *) arg;
	pthread_mutex_lock(&mutex); // verrouillage du mutex
	int *newligne=calloc(args->taille,sizeof(int));
	for(int j=0; j<args->taille; j++){
		newligne[j]=rand()%(args->max-args->min+1) + args->min;
		printf("[%d]", newligne[j] );
		args->somme+=newligne[j];
	}
	printf("\n");
	pthread_mutex_unlock(&mutex); // deverrouillage du mutex
	pthread_exit(newligne);
}


int createThread(pthread_t *t, arguments *args){

	int ret = pthread_create(t, NULL, thread, (void *) args);
	/* Q2 : Pour definir un nombre maximal d'affichage il suffit de
	remplacer le dernier parametre de pthread_create par un argument caster
	en void. */
	if( ret == -1) {
		perror("pthread_create error");
		return EXIT_FAILURE;
	}
	return ret;

}

int main(int argc, char *argv[])
{
	/* On recupere les arguments correspondant au borne permettant de 
	generer un nombre entre un maximum et un minimum (min en premier max
	en deuxieme) */
	int arg1=atoi(argv[1]);
	int arg2=atoi(argv[2]);
	int arg3=atoi(argv[3]);
	/* creation d'une variable de type struct arguments et instanciation 
	des elements qui la composent et allocation de l'espace memoire pour 
	le tableau composant la matrice */
	arguments args;
	args.min=arg1;
	args.max=arg2;
	args.taille=arg3;
	args.somme=0;
	args.matrix=calloc(args.taille,sizeof(args.taille));
	for(int i=0; i<args.taille; i++){
		args.matrix[i]=calloc(args.taille,sizeof(args.taille));
	}
	// On declare un tableau de 4 thread
	pthread_t thread[args.taille];
	// initialisation de srand
	srand(time(NULL));
	for(int k=0; k<args.taille; k++){
		createThread(&thread[k], &args);
	}
	for(int l=0; l<args.taille; l++){
		int *ligne;
		if (pthread_join(thread[l], (void**) &ligne)){
			perror("pthread_join");
			return EXIT_FAILURE;
		}
	}

	printf("La somme de cette matrice carre de taille 4 est de %d\n", args.somme);	

	return 0;
}
