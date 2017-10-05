/***************************************************

Fichier : tp2_ex3.c
Date de création : 26 Septembre 2017
Auteur : NORO Geoffrey

***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct arguments
{
	int min;
	int max;
	int taille;
	int **matrix;
};

void *thread(void *arg){

	/*int compt=0;
	int i2=(int)arg;
	while(compt<i2){
		printf("id thread fils = %i and number of prints : %i \n", (int)pthread_self(), compt);
		sleep(1);
		compt++;
	}*/

	pthread_exit(NULL);
}


int createThread(pthread_t *t){

	int ret = pthread_create(t, NULL, thread, NULL);
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
	struct arguments args;
	pthread_t thread[4];
	args.min=arg1;
	args.max=arg2;
	args.taille=4;
	args.matrix=calloc(args.taille,sizeof(args.taille));
	for(int i=0; i<args.taille; i++){
		args.matrix[i]=calloc(args.taille,sizeof(args.taille));
	}
	createThread(thread);
	if (pthread_join(thread,NULL)){
		perror("pthread_join");
		return EXIT_FAILURE;
	}
	return 0;
}