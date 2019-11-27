/****************************************************
|													|
|			Fichier : add_and_mult.c				|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "mult.h"

int multi(int a, int b){
	return a*b;
}

void *thread(void *d) {
	data *da = malloc(sizeof(data));
	da = (data *) d;
	printf("%d\n", da->num1);
	printf("%d\n", da->num2);
	int r = multi(da->num1,da->num2);
	printf("%d\n", r);
	pthread_exit((void *)r);
	free(da);
}


int createThread(pthread_t *t, data *d){
	int ret = pthread_create(t,NULL,thread, (void *) d);
	if (ret == -1)
	{
		perror("pthread_create error");
		return EXIT_FAILURE;
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	data *d = malloc(sizeof(data));
	data *d2 = malloc(sizeof(data));
	pthread_t pthid[2];
	int res;

	for (int i=0; i < 2; ++i)
	{
		switch(i){
			case 0:
				d->num1=1;
				d->num2=2;
				createThread(&pthid[i], d);
				break;
			case 1:
				d2->num1=3;
				d2->num2=4;
				createThread(&pthid[i], d2);
				break;
			default:
				printf("ERROR\n");
				break;
		}
		// bug
		/*if (pthread_join(pthid[i],&res))
		{
			perror("pthread_join");
		}
		printf("Le resultat de la multiplication est : %d\n",res);
		sleep(1);*/
	}
	// code qui marche
	for (int i = 0; i < 2; ++i)
	{
		if (pthread_join(pthid[i],&res))
		{
			perror("pthread_join");
		}
		printf("Le resultat de la multiplication est : %d\n",res);
	}

	free(d);
	free(d2);
	return 0;
}