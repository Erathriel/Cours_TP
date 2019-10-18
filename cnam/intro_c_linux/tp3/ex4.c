#include "ex4.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	if(argc<3)
	{
		printf("Veuillez saisir le bon nombre d'argument de la maniere suivante : \n ./nomDeLExecutable str1 str2 \n");
		return EXIT_FAILURE;
	}
	else if(argc>3) {
		printf("Nombre d'argument trop grand veuillez utiliser la syntaxe suivante : \n ./nomDeLExecutable str1 str2 \n");
		return EXIT_FAILURE;
	}
	else {
		char *str1;
		char *str2;
		str1 = argv[1];
		str2 = argv[2];

		printf("%s\n", str1);
		printf("%s\n", str2);

	return 0;
}