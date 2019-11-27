// Modification 10/2014

/* Creation de 3 threads; chacune incremente un compteur qui lui est associe*/ 
    
/* Trois_Th.c */ 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int compteur[3];
 
/* fonction executee par  chaque thread */ 
void *fonc_thread(void *k) {

	printf("Thread numero %d : mon tid est %d\n", 
		(int) k,pthread_self());
	for (;;)
	compteur[(int) k]++;

} 

int main(void) {
	int i, num;
	pthread_t pth_id[3];

/* creation des threads */ 
	for (num = 0; num < 3; num++) {
		pthread_create(pth_id + num, 0, fonc_thread, (void *) num);
		printf("Main: thread numero %d creee: id = %d\n", 
			num,pth_id[num]);
	} 
	usleep(10000);	/* attente de 10 ms */
	/* Affichage des compteurs (20 fois): entre 2 affichages, les compteurs peuvent avoir ete incrementes */ 
	printf("Affichage des compteurs\n");
	for (i = 0; i < 20; i++) {
		printf("%d \t%d \t%d\n", 
			compteur[0], compteur[1], compteur[2]);
		usleep(1000);		/* attente de 1 ms entre 2 affichages */
	}
	exit(0);
}


 
 
