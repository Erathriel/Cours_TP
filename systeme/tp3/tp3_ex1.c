/***************************************************

Fichier : tp3_ex1.c
Date de création : 03 octobre 2017
Auteur : NORO Geoffrey

***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct
{
	int min;
	int max;
	int taille;
	int nLigne;
	int **matrix;
} arguments;

void *thread(void *arg){
	arguments *args = (arguments *) arg;
	int *newligne=calloc(args->taille,sizeof(int));
	for(int j=0; j<args->taille; j++){
		newligne[j]=rand()%(args->max-args->min+1) + args->min;
		printf("[%d]", newligne[j] );
	}
	printf("\n");
	pthread_exit(newligne);
}


int createThread(pthread_t *t, arguments *args){

	int ret = pthread_create(t, NULL, thread, (void *) args);
	// Q2 : Pour définir un nombre maximal d'affichage il suffit de remplacer le dernier paramètre de pthread_create par un argument caster en void.
	if( ret == -1) {
		perror("pthread_create error");
		return EXIT_FAILURE;
	}
	return ret;

}

int main(int argc, char *argv[])
{
	int arg1=atoi(argv[1]);
	int arg2=atoi(argv[2]);
	arguments args;
	pthread_t thread[4];
	args.min=arg1;
	args.max=arg2;
	args.taille=4;
	args.matrix=calloc(args.taille,sizeof(args.taille));
	for(int i=0; i<args.taille; i++){
		args.matrix[i]=calloc(args.taille,sizeof(args.taille));
	}
	srand(time(NULL));
	for(int k=0; k<4; k++){
		createThread(&thread[k], &args);
	}
	for(int l=0; l<4; l++){
		int *ligne;
		if (pthread_join(thread[l], (void**) &ligne)){
			perror("pthread_join");
			return EXIT_FAILURE;
		}
	}

	return 0;
}
