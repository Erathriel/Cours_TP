#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define INDICE_FR 0.075

char* TxtSansSpeChar(char* mess, int tailleMess, char* messNoSpace){
    int tailleMessageNoSpace=0;
    for (int c = 0; c < tailleMess; c++)
    {
        if ((mess[c] >= 'A' && mess[c] <= 'Z'))
        {
            messNoSpace[tailleMessageNoSpace]=mess[c];
            tailleMessageNoSpace++;
        }
    }
    return messNoSpace;
}

char* LireTxt(FILE* file, char* mess){
    char charAt;
    int tailleMessage=0;
    do{
        charAt=fgetc(file);
        mess[tailleMessage]=charAt;
        tailleMessage++;
    }
    while(charAt != EOF);

    return mess;
}

int* RAZFreq(int* alphaFreq){

    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        alphaFreq[j]=0;
    }

    return alphaFreq;
}

int CalculCleVigenere(char* messageNoSpace, float indiceCoincidence, int tailleKey, int* alphabetFreq, int tailleMessageNoSpace, int nbLettre){

    while(tailleKey < 16 && (indiceCoincidence < 0.075 || indiceCoincidence > 0.085)){
            indiceCoincidence = 0;
            tailleKey++;
            for (int k = 0; k < tailleKey; k++)
            {
                nbLettre=0;
                for (int l = 0; l < tailleMessageNoSpace; l+=tailleKey)
                {
                    unsigned char c = (unsigned char) messageNoSpace[l+k];
                    if ((c >= 'A' && c <= 'Z'))
                    {
                        alphabetFreq[c -'A'] +=1;
                        nbLettre++;
                    }
                }
                for (int i = 0; i < ALPHABET_SIZE; ++i)
                {
                    unsigned char c = (unsigned char) (i+'A');
                    indiceCoincidence += (float)(alphabetFreq[i]*(alphabetFreq[i]-1.0))/(float)(nbLettre*(nbLettre-1.0));
                }
                alphabetFreq = RAZFreq(alphabetFreq);
            }
            indiceCoincidence /= tailleKey;
        }
        printf("%d\n\n\n", tailleKey);
        return tailleKey;
}

/* 
fonction de déchiffrement de Vigenere prenant en paramètre la clef obtenue dans 
la fonction Vigenere_break et le nom du fichier du text crypter (du type : texte.txt)
*/
void VigenereDecrypt(char* key, char* cipherTextName){
	FILE* fileCipherText=NULL;
	FILE* filePlainText=NULL;

	char *decryptKey = key;
	char *fileName = cipherTextName;
	char *fileName2;

	char charAt;

	fileName2=malloc(sizeof(char)*256);

	printf("La cle est : %s\n", key );

	printf("Saisir le nom du fichier .txt contenant le message chiffré :\n");
	scanf("%s",fileName2);

	fileCipherText = fopen(fileName,"r");
	filePlainText = fopen(fileName2,"w");

	if (fileCipherText != NULL && filePlainText != NULL)
	{
		int letter=0;
		do{
        	charAt=fgetc(fileCipherText);
        	if (charAt >= 'A' && charAt <= 'Z')
        	{
        		if (letter > strlen(key)-1)
        		{
        			letter=0;
        			printf("char lu : %c\n", charAt);
        			charAt = (charAt - key[letter%strlen(key)]+26)%26;
        			charAt += 'A';
        			printf("lettre de la cle : %c\n", key[letter]);
        			printf("%c\n",charAt );
        			if (charAt < 'A')
        			{	
        				charAt += 26;
        			}
        			fputc(charAt, filePlainText);
        			letter++;
        		}
        		else{
        			printf("char lu : %c\n", charAt);
        			charAt = (charAt - key[letter%strlen(key)]+26)%26;
        			charAt += 'A';
        			printf("lettre de la cle : %c\n", key[letter]);
        			printf("%c\n",charAt );
        			if (charAt < 'A')
        			{	
        				charAt += 26;
        			}
        			fputc(charAt, filePlainText);
        			letter++;
        		}
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
	else {
		printf("Impossible de lire le fichier %s ou %s !\n", fileName, fileName2);
	}
	free(fileName2);
}

// decrypte le chiffre de Vigenere a l aide de la fonction de dichiffrement de Vigenere
void VigenereBreak(){
	//FILE* logFile=NULL;

	FILE* fileCipherText=NULL;
	char *fileName;
	int *alphabetFreq;
	char *message;
	char *messageNoSpace;
	char *key;

	int nbLettre=0;
	float indiceCoincidence=0;
	int tailleKey=0;
	int tailleMessage=0;
	int tailleMessageNoSpace=0;
	int max = 0;

	char charAt;

	fileName=malloc(sizeof(char)*256);
	alphabetFreq=calloc(ALPHABET_SIZE,sizeof(int));
	message=malloc(sizeof(char)*50000);
	messageNoSpace=malloc(sizeof(char)*50000);
	key=malloc(sizeof(char)*256);


	printf("Saisir le nom du fichier .txt contenant le message chiffré :\n");
	scanf("%s",fileName);

	//logFile = fopen("log.txt","w");
	fileCipherText = fopen(fileName, "r");

	if (fileCipherText != NULL)
	{
        message = LireTxt(fileCipherText, message);
        tailleMessage = strlen(message);
        fclose(fileCipherText);
        messageNoSpace=TxtSansSpeChar(message, tailleMessage, messageNoSpace);
        tailleMessageNoSpace=strlen(messageNoSpace);
        tailleKey=CalculCleVigenere(messageNoSpace, indiceCoincidence, tailleKey, alphabetFreq, tailleMessageNoSpace, nbLettre);
        printf("%d\n\n\n", tailleKey);
        alphabetFreq=RAZFreq(alphabetFreq);
        for (int n = 0; n < tailleKey; n++)
        {
        	max=0;
        	nbLettre=0;
        	for (int o = 0; o < tailleMessageNoSpace; o+=tailleKey)
        	{
        		unsigned char c = (unsigned char) messageNoSpace[o+n];
	        		if ((c >= 'A' && c <= 'Z'))
	        		{
	        			alphabetFreq[c -'A'] +=1;
	        			nbLettre++;
	        		}
        	}
        	for (int p = 0; p < ALPHABET_SIZE; p++)
        	{
        		unsigned char c = (unsigned char) p;
        		if (alphabetFreq[p]>max)
        		{
        			c -= 'E';
        			c = c + 2 * 'A';
        			if (c < 'A')
        			{
        				c+=26;
        			}
        			key[n]=c;
        			max=alphabetFreq[p];
        		}
        		alphabetFreq[p]=0;
        	}
        	printf("%c\n", key[n]);
        }
        VigenereDecrypt(key,fileName);
	}
	else{
		printf("Impossible de lire le fichier %s !\n", fileName);
	}
	free(messageNoSpace);
    free(message);
    free(alphabetFreq);
}

// decrypte le chiffre de cesar
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
        	unsigned char c = (unsigned char) (i+'A');
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

    // affichage du choix de la technique de decryptage
	printf("---------- Break Challenge ----------\n");
	printf("1) Caesar Break\n");
	printf("2) Vigenere Break\n");
	printf("3) Subtitution Break\n");
	printf("Choisissez comment vous voulez casser votre message chiffré : ");
	scanf ("%d", &choix);

    // selection en fonction du choix utilisateur
	switch(choix){
        // decryptage avec Cesar
		case 1:
			printf("-------------------------------------\n");
			printf("Choix cesar\n");
			CaesarBreak();
			break;
        // decryptage avec Vigenere
		case 2:
			printf("-------------------------------------\n");
			printf("Choix Vigenere\n");
			VigenereBreak();
			break;
        // decryptage avec Substitution
		case 3:
			printf("-------------------------------------\n");
			printf("Choix substitution\n");
			break;
		default:
			printf("Votre choix n'est pas entre 1,2 ou 3 !\n");
			break;
	}
}

// programme principale
int main(int argc, char *argv[]) {
	
	FaireChoix();
	return 0;
}