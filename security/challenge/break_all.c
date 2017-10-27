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
void VigenereBreak(){
	FILE* logFile=NULL;

	FILE* fileCipherText=NULL;
	char *fileName;
	int *alphabetFreq;
	char *message;
	char *messageNoSpace;

	int nbLettre=0;
	float indiceCoincidence=0;
	int tailleKey=0;
	int tailleMessage=0;
	int tailleMessageNoSpace=0;

	char charAt;

	fileName=malloc(sizeof(char)*256);
	alphabetFreq=calloc(ALPHABET_SIZE,sizeof(int));
	message=malloc(sizeof(char)*50000);
	messageNoSpace=malloc(sizeof(char)*50000);


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
        for (int c = 0; c < tailleMessage; c++)
        {
        	if ((message[c] >= 'A' && message[c] <= 'Z'))
	        {
	        	messageNoSpace[tailleMessageNoSpace]=message[c];
	        	tailleMessageNoSpace++;
	        }
        }
        while(tailleKey < 16 && (indiceCoincidence < 0.075 || indiceCoincidence > 0.085)){
        	indiceCoincidence = 0;
        	tailleKey++;
        	for (int k = 0; k < tailleKey; k++)
        	{
        		fprintf(logFile, "---------------------DEBUT boucle %d ----------------------\n", k);
        		nbLettre=0;
        		for (int l = 0; l < tailleMessageNoSpace; l+=tailleKey)
	        	{
	        		unsigned char c = (unsigned char) messageNoSpace[l+k];
	        		if ((c >= 'A' && c <= 'Z'))
	        		{
	        			alphabetFreq[c -'A'] +=1;
	        			nbLettre++;
	        			fprintf(logFile, "lettre lu : %c\n", c);
	        		}
	        	}
	        	for (int i = 0; i < ALPHABET_SIZE; ++i)
		        {
		        	unsigned char c = (unsigned char) (i+'A');
		        	fprintf(logFile,"La lettre %c apparait %d fois dans le texte.\n", c ,alphabetFreq[i]);
		        	fprintf(logFile, "alpha freq : %d \n",alphabetFreq[i] );
		        	fprintf(logFile,"numerateur : %f\n", (float)(alphabetFreq[i]*(alphabetFreq[i]-1.0)));
		        	fprintf(logFile, "denominateur : %f\n",(float)(nbLettre*(nbLettre-1.0)) );
		        	fprintf(logFile, "res : %f\n", (float)(alphabetFreq[i]*(alphabetFreq[i]-1.0))/(float)(nbLettre*(nbLettre-1.0)));
		        	indiceCoincidence += (float)(alphabetFreq[i]*(alphabetFreq[i]-1.0))/(float)(nbLettre*(nbLettre-1.0));
		        	fprintf(logFile, "tmp ind : %f \n", indiceCoincidence);
		        }
		        for (int j = 0; j < ALPHABET_SIZE; j++)
		        {
		        	alphabetFreq[j]=0;
		        }
		        fprintf(logFile," n lettre : %d\n",nbLettre );
        	}
	        indiceCoincidence /= tailleKey;
	        fprintf(logFile,"indice : %f\n",indiceCoincidence );
	        fprintf(logFile,"tailleMessage : %d\n", tailleMessageNoSpace);
	        fprintf(logFile,"key : %d\n\n\n",tailleKey );
        }
        printf("%d\n", tailleKey);
	}
	else{
		printf("Impossible de lire le fichier %s !\n", fileName);
	}
	free(messageNoSpace);
    free(message);
    free(alphabetFreq);
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