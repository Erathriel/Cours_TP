#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int somme;
	if (argc < 3 || argc > 3)
	{
		fprintf(stderr,"Erreur nb arguments incorrecte\n");
		exit(-1);
	}
	somme=atoi(argv[1])+atoi(argv[2]);
	printf("somme : %d\n", somme);
	exit(5);
}