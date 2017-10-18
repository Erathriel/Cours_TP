#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void Caesar_Break(){
	FILE* file=NULL;
	char *fileName;
	fileName=malloc(sizeof(char)*256);
	printf("choisir le message a decrypter :\n");
	scanf("%s",fileName);
	printf("%s\n",fileName);
	file = fopen(fileName, "r");
	if (file != NULL)
	{
		printf("OK\n");
	}
	else {
		printf("Impossible de lire le fichier !\n");
	}
	/*do{
        nucleotide=fgetc(fichier);
        taille++;// on regarde le nombre de caractère
        }
        while(nucleotide != EOF);
        fclose(fichier);
        printf ("taille= %d \n",taille);*/
}

// choisir comment on veut casser le texte chiffrer

void FaireChoix(){
	int choix = 0;

	printf("---------- Break Challenge ----------\n");
	printf("1) Caesar Break\n");
	printf("2) Vigenere Break\n");
	printf("3) Subtitution Break\n");
	scanf ("%d", &choix);

	switch(choix){
		case 1:
			printf("Choix cesar\n");
			Caesar_Break();
			break;
		case 2:
			printf("Choix Vigenere\n");
			break;
		case 3:
			printf("Choix substitution\n");
			break;
		default:
			printf("Votre choix n'est pas entre 1,2 ou 3 !\n");
			break;
	}
}

int main(int argc, char *argv[]) {
	
	FaireChoix();
	return 0;
}