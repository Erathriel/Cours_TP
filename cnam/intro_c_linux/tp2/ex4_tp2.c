#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int calculMediane(int* tab, int nbDeValeur){

}

int main(int argc, char const *argv[])
{
	if(argc<2)
	{
		printf("Veuillez saisir le bon nombre d'argument de la maniere suivante : \n ./nomDeLExecutable nbValeur \n");
		return EXIT_FAILURE;
	}
	else if(argc>2) {
		printf("Nombre d'argument trop grand veuillez utiliser la syntaxe suivante : \n ./nomDeLExecutable nbValeur \n");
		return EXIT_FAILURE;
	}
	else {
		int arg1=atoi(argv[1]);
		int* vRand = (int*) calloc(arg1, sizeof(int));
		printf("%d\n", RAND_MAX);
		//int* vRand =malloc(arg1 *sizeof(int));
		srand(time(NULL)); // initialisation de rand
		printf("%d\n", arg1);
		for (int i = 0; i < arg1; ++i)
		{
			vRand[i]=rand()%100;
		}
		for (int i = 0; i < arg1; ++i)
		{
			printf("| %d |\n", vRand[i]);
		}
		free(vRand);
	}
	return 0;
}