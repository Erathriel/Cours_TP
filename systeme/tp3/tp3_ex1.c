/***************************************************

Fichier : tp3_ex1.c
Date de creation : 03 octobre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

/* ce programme calcul la somme de tout les elements d'une matrice a l'aide
de thread qui cree chaque ligne de la matrice et calcul la somme des elements
de la ligne puis l'ajoute a la somme total */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// creation et initialisation du mutex
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

/* definition d'une structure arguments permettant de donne 
a un thread plusieurs arguments */
typedef struct
{
	int min;
	int max;
	int ligne;
	int colonne;
	int nLigne;
	int somme;
	int **matrix;
	
} arguments;

void *thread(void *arg){
	// represente la somme de la ligne
	int s=0;
	// on recupere les arguments donne au thread
	arguments *args = (arguments *) arg;
	pthread_mutex_lock(&mutex); // verrouillage du mutex
	/* on cree un tableau d'entier correspondant a la ligne de la matrice
	du thread actif */
	int *newligne=calloc(args->colonne,sizeof(int));
	// on rempli la ligne de nombre aleatoire
	for(int j=0; j<args->colonne; j++){
		// on cree un nombre aleatoire entre les bornes definis
		newligne[j]=rand()%(args->max-args->min+1) + args->min;
		//printf("[%d]", newligne[j] ); // test d'affichage des éléments de la ligne
		// on l'ajoute à la somme des precedents éléments ( initialiser a 0)
		s+=newligne[j];
	}
	//printf("\n"); // saut de ligne entre les ligne
	/* on ajoute la somme de la ligne du thread acturel a la somme total 
	des elements de la matrice */
	args->somme+=s;
	pthread_mutex_unlock(&mutex); // deverrouillage du mutex
	pthread_exit(newligne); // on renvoie la ligne que l'on a cree
}


int createThread(pthread_t *t, arguments *args){

	int ret = pthread_create(t, NULL, thread, (void *) args);
	/* Q2 : Pour definir un nombre maximal d'affichage il suffit de
	remplacer le dernier parametre de pthread_create par un argument 
	caster en void. */
	if( ret == -1) {
		perror("pthread_create error");
		return EXIT_FAILURE;
	}
	return ret;

}

int main(int argc, char *argv[])
{
	// test si le nombre d'argument est inferieur a 5
	if(argc<5)
	{
		printf("Veuillez saisir le bon nombre d'argument de la maniere suivante : \n ./nomDeLExecutable borneMin borneMax nbLigne nbColonne \n");
		return EXIT_FAILURE;
	}
	// test si le nombre d'argument est superieur a 5
	else if(argc>5) {
		printf("Nombre d'argument trop grand veuillez utiliser la syntaxe suivante : \n ./nomDeLExecutable borneMin borneMax nbLigne nbColonne \n");
		return EXIT_FAILURE;
	}
	else {
		/* on recupere les arguments correspondant au borne permettant de 
		generer un nombre entre un maximum et un minimum (min en premier 
		max	en deuxieme) */
		int arg1=atoi(argv[1]);
		int arg2=atoi(argv[2]);
		int arg3=atoi(argv[3]);
		int arg4=atoi(argv[4]);
		/* creation d'une variable de type struct arguments et 
		instanciation des elements qui la composent et allocation de 
		l'espace memoire pour le tableau composant la matrice */
		arguments args;
		args.min=arg1;
		args.max=arg2;
		args.ligne=arg3;
		args.colonne=arg4;
		args.somme=0;
		args.matrix=calloc(args.ligne,sizeof(args.ligne));
		for(int i=0; i<args.ligne; i++){
			args.matrix[i]=calloc(args.colonne,sizeof(args.colonne));
		}
		// On declare un tableau de 4 threads
		pthread_t thread[args.ligne];
		// initialisation de srand
		srand(time(NULL));
		// creation des threads
		for(int k=0; k<args.ligne; k++){
			createThread(&thread[k], &args);
		}
		/* permet de creer une ligne par threads en attendant la fin
		du thread precedent */
		for(int l=0; l<args.ligne; l++){
			int *ligne;
			if (pthread_join(thread[l], (void**) &ligne)){
				perror("pthread_join");
				return EXIT_FAILURE;
			}
			// affichage de chaque ligne renvoye par chaque thread
			printf("(");
			for (int m = 0; m < args.colonne; m++)
			{
				printf(" %d ", ligne[m] );
			}
			printf(")");
			printf("\n");
		}
		// affichage de la somme
		printf("La somme de cette matrice carre de taille 4 est de %d\n", args.somme);
		pthread_mutex_destroy(&mutex);	

		return 0;
	}
	
}
