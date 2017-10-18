#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26

void Caesar_Break(){
	FILE* file=NULL;
	char *fileName;
	char charAt;
	int *alphabetFreq;
	char cryptedLetter=0;
    int freqCryptedLetter=0;
    int key=0;
	alphabetFreq=calloc(ALPHABET_SIZE,sizeof(int));
	fileName=malloc(sizeof(char)*256);
	printf("choisir le message a decrypter :\n");
	scanf("%s",fileName);
	file = fopen(fileName, "r");
	if (file != NULL)
	{
		do{
        	charAt=fgetc(file);
        	//printf("%c\n", charAt);
        	if (charAt >= 'A' && charAt <= 'Z')
        	{
        		//printf("%d\n", charAt-'A');
        		alphabetFreq[charAt-'A'] += 1;
        	}
        }
        while(charAt != EOF);
        fclose(file);
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
        	if(alphabetFreq[i] > freqCryptedLetter){
            	cryptedLetter = i+'A';
            	freqCryptedLetter = alphabetFreq[i];
        	}
        	unsigned char c = (unsigned char) (i+65);
        	printf("La lettre %c apparait %d fois dans le texte.\n", c ,alphabetFreq[i]);
        }
        printf("La lettre la plus utilisée dans ce text est : %c\n", cryptedLetter);

        key = cryptedLetter - 'E';
	}
	else {
		printf("Impossible de lire le fichier !\n");
	}
	
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
//
int main(int argc, char *argv[]) {
	
	FaireChoix();
	return 0;
}