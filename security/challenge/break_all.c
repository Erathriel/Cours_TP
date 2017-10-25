#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define INDICE_FR 0.075
#define INDICE_ALEATOIRE 0.035

/*void RetourMenu(){
	unsigned char choix2;
	printf("-------------------------------------\n");
	printf("Voulez vous retournez au menu ? (O/N) \n");
	scanf ("%c", &choix2);
	//printf("%d\n", choix2);
	
}*/

/*void VigenereBreak(){
	FILE* fileCipherText=NULL;
	char *fileName;
	int *alphabetFreq;

	int nbLettre=0;
	float indiceCoincidence=0;
	int tailleKey=0;

	char charAt;

	fileName=malloc(sizeof(char)*256);
	alphabetFreq=calloc(ALPHABET_SIZE,sizeof(int));


	printf("Saisir le nom du fichier .txt contenant le message chiffré :\n");
	scanf("%s",fileName);
	printf("%s\n",fileName );

	fileCipherText = fopen(fileName, "r");

	if (fileCipherText != NULL)
	{
        do{
        	charAt=fgetc(fileCipherText);
        	if (charAt >= 'A' && charAt <= 'Z')
        	{
        		alphabetFreq[charAt-'A'] += 1;
        		nbLettre++;
        	}
        }
        while(charAt != EOF);
        fclose(fileCipherText);
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
        	unsigned char c = (unsigned char) (i+65);
        	printf("La lettre %c apparait %d fois dans le texte.\n", c ,alphabetFreq[i]);

        	indiceCoincidence += (float)(alphabetFreq[i]*(alphabetFreq[i]-1))/(nbLettre*(nbLettre-1));
        }
        printf("%f\n",INDICE_FR );
        printf("%f\n",INDICE_ALEATOIRE );
        printf("%d\n",nbLettre );
        printf("%f\n",indiceCoincidence );
        tailleKey = ((INDICE_FR - INDICE_ALEATOIRE)*nbLettre)/((nbLettre)*indiceCoincidence - (nbLettre*INDICE_ALEATOIRE) + INDICE_FR);
        printf("%d\n", tailleKey);
        free(alphabetFreq);
	}
	else{
		printf("Impossible de lire le fichier %s !\n", fileName);
	}
}*/

void VigenereBreak(){
	FILE* logFile=NULL;

	FILE* fileCipherText=NULL;
	char *fileName;
	int *alphabetFreq;
	char *message;

	float indiceCoincidenceMoy=0;
	int nbLettre=0;
	float indiceCoincidence=0;
	int tailleKey=0;
	int tailleMessage=0;

	char charAt;

	fileName=malloc(sizeof(char)*256);
	alphabetFreq=calloc(ALPHABET_SIZE,sizeof(int));
	message=malloc(sizeof(char)*50000);


	printf("Saisir le nom du fichier .txt contenant le message chiffré :\n");
	scanf("%s",fileName);
	printf("%s\n",fileName );

	logFile = fopen("log.txt","w");
	fileCipherText = fopen(fileName, "r");

	if (fileCipherText != NULL)
	{
        do{
        	charAt=fgetc(fileCipherText);
        	message[tailleMessage]=charAt;
        	tailleMessage++;
        }
        while(charAt != EOF);
        fclose(fileCipherText);
        while(tailleKey < 16 && (indiceCoincidenceMoy < 0.073 || indiceCoincidenceMoy > 0.077)){
        	indiceCoincidenceMoy=0;
        	tailleKey++;
        	for (int k = 0; k < tailleKey; k++)
        	{
        		fprintf(logFile, "---------------------DEBUT boucle %d ----------------------\n", k);
        		indiceCoincidence = 0;
        		nbLettre=0;
        		for (int l = 0; l < tailleMessage; l+=tailleKey)
	        	{
	        		unsigned char c = (unsigned char) message[l+k];
	        		if ((c >= 'A' && c <= 'Z'))
	        		{
	        			alphabetFreq[c -'A'] +=1;
	        			nbLettre++;
	        		}
	        	}
	        	for (int i = 0; i < ALPHABET_SIZE; ++i)
		        {
		        	unsigned char c = (unsigned char) (i+'A');
		        	fprintf(logFile,"La lettre %c apparait %d fois dans le texte.\n", c ,alphabetFreq[i]);

		        	indiceCoincidence += (float)(alphabetFreq[i]*(alphabetFreq[i]-1))/(nbLettre*(nbLettre-1));
		        	fprintf(logFile, "tmp : %f\n", indiceCoincidence);
		        }
		        for (int j = 0; j < ALPHABET_SIZE; j++)
		        {
		        	alphabetFreq[j]=0;
		        }
		        fprintf(logFile," n lettre : %d\n",nbLettre );
		        fprintf(logFile, "%f\n",indiceCoincidence );
		        indiceCoincidenceMoy += (indiceCoincidence/tailleKey);
		        fprintf(logFile, "moy ind : %f\n", indiceCoincidenceMoy);
        	}
        	indiceCoincidenceMoy += INDICE_ALEATOIRE;
	        fprintf(logFile,"indice : %f\n",indiceCoincidence );
	        fprintf(logFile,"tailleMessage : %d\n", tailleMessage);
	        fprintf(logFile,"key : %d\n",tailleKey );
        }
        printf("%d\n", tailleKey);

        free(alphabetFreq);
	}
	else{
		printf("Impossible de lire le fichier %s !\n", fileName);
	}
	fclose(logFile);
}

void CaesarBreak(){
	FILE* fileCipherText=NULL;
	FILE* filePlainText=NULL;
	char *fileName;
	char *fileName2;
	int *alphabetFreq;

	char charAt;
	char cryptedLetter=0;
    int freqCryptedLetter=0;
    int key=0;

	alphabetFreq=calloc(ALPHABET_SIZE,sizeof(int));
	fileName=malloc(sizeof(char)*256);
	fileName2=malloc(sizeof(char)*256);
	
	printf("Saisir le nom du fichier .txt contenant le message chiffré :\n");
	scanf("%s",fileName);
	printf("Saisir le nom du fichier .txt qui recevras le message décrypté :\n");
	scanf("%s",fileName2);
	fileCipherText = fopen(fileName, "r");
	filePlainText = fopen(fileName2, "w");
	


	if (fileCipherText != NULL && filePlainText != NULL)
	{
		do{
        	charAt=fgetc(fileCipherText);
        	if (charAt >= 'A' && charAt <= 'Z')
        	{
        		alphabetFreq[charAt-'A'] += 1;
        	}
        }
        while(charAt != EOF);
        fclose(fileCipherText);
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
        if (key<0)
        {
        	key = -key;
        }
        printf("La clé est donc : %d\n", key);
        fileCipherText = fopen(fileName, "r");
        if (fileCipherText !=NULL)
        {
        	do{
        		charAt=fgetc(fileCipherText);
        		if (charAt >= 'A' && charAt <= 'Z')
        		{
        			charAt = charAt - key;
        			if (charAt < 'A')
        			{	
        				charAt += 26;
        			}
        			fputc(charAt, filePlainText);
        		}
        		else if(charAt == -1){
        			fputc(' ', filePlainText);
        		}
        		else {
        			fputc(charAt, filePlainText);
        		}
        	}
        	while(charAt != EOF);
        	fclose(fileCipherText);
        	fclose(filePlainText);
        }
        else{
        	printf("Impossible de lire le fichier %s !\n", fileName);
        }
        printf("Message décrypté !\n");
        free(alphabetFreq);
	}

	else {
		printf("Impossible de lire le fichier %s ou %s !\n", fileName, fileName2);
	}
	
}

// choisir comment on veut casser le texte chiffré

void FaireChoix(){
	int choix = 0;

	printf("---------- Break Challenge ----------\n");
	printf("1) Caesar Break\n");
	printf("2) Vigenere Break\n");
	printf("3) Subtitution Break\n");
	printf("Choisissez comment vous voulez casser votre message chiffré : ");
	scanf ("%d", &choix);

	switch(choix){
		case 1:
			printf("-------------------------------------\n");
			printf("Choix cesar\n");
			CaesarBreak();
			break;
		case 2:
			printf("-------------------------------------\n");
			printf("Choix Vigenere\n");
			VigenereBreak();
			break;
		case 3:
			printf("-------------------------------------\n");
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