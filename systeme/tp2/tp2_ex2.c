/***************************************************

Fichier : tp2_ex2.c
Date de création : 19 Septembre 2017
Auteur : NORO Geoffrey

***************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread(void *arg){

	int compt=0;
	int i2=(int)arg;
	while(compt<i2){
		printf("id thread fils = %i and number of prints : %i \n", (int)pthread_self(), compt);
		sleep(1);
		compt++;
	}

	pthread_exit(NULL);
}

int createThread(pthread_t *t, int i){

	int ret = pthread_create(t, NULL, thread, (void*) i);
	// Q2 : Pour définir un nombre maximal d'affichage il suffit de remplacer le dernier paramètre de pthread_create par un argument caster en void.
	if( ret == -1) {
		perror("pthread_create error");
		return EXIT_FAILURE;
	}
	return ret;

}


int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	int i3;
	printf("ENTREZ VOTRE NOMBRE D'AFFICHAGE : \n");
	scanf("%i", &i3);
	createThread(&thread1, i3);
	createThread(&thread2, i3);
	if (pthread_join(thread1,NULL)){
		perror("pthread_join");
		return EXIT_FAILURE;
	}
	if (pthread_join(thread2,NULL)){
		perror("pthread_join");
		return EXIT_FAILURE;
	}
	return 0;
}
