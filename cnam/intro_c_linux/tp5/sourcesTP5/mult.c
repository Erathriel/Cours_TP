/****************************************************
|													|
|			Fichier : add_and_mult.c				|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *arg){
	int *arguments = (int *) arg;
	int resultat;
	for (int i = 0; i < 3; ++i)
	{
		printf("%d \n", arguments[i]);
	}
	if (arguments[0] != 0)
	{
		resultat = arguments[1]*arguments[2];
		printf("Le resultat de %d + %d est : %d \n", arguments[1], arguments[2], resultat);
	}

	pthread_exit(NULL);
}

int threadCreator(pthread *t, int *i){
	int ret = pthread_create(t, NULL, thread, (void *) i);
	if (ret == -1)
	{
		perror("pthread_create error");
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	pthread_t pthid[3];
	int a,b,c,d;
	int arg[3];

	for (int i = 0; i < 3; ++i)
	{
		switch(i)
		{
			case 1:
				arg[0] = i;
				arg[1] = a;
				arg[2] = b;
			case 2:
				arg[0] = i;
				arg[1] = c;
				arg[2] = d;
			case 3:
				arg[0] = i;
				arg[1] = 0;
				arg[2] = 0;
			default:
				printf("Erreur\n");
		}
		threadCreator(&pthid[i], arg);
	}

	return 0;
}