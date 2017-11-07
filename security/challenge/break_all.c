/***************************************************

Fichier : break_all.c
Auteur : NORO Geoffrey

***************************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define INDICE_FR 0.075

/* stock le text sans caractere speciaux et prend en parametre
le message stocker, la taille du message et le tableau dans lequel
on veut stocker le texte sans caractere special
*/
char* TxtSansSpeChar(char* mess, int tailleMess, char* messNoSpace){
    int tailleMessageNoSpace=0;
    // parcours le message avec caractere speciaux stock uniquement les lettre dans le second tableau
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



/* lis le texte ecrit dans un fichier et le stock dans un tableau de caractere
prend en parametre le fichier .txt du texte chiffre et le tableau de caratere dans 
lequel on stock les caractere présent dans le fichier
*/
char* LireTxt(FILE* file, char* mess){
    // variable permettant de stocker le caractere lu a chaque iteration
    char charAt;
    int tailleMessage=0;
    do{
        charAt=fgetc(file);
        mess[tailleMessage]=charAt;
        tailleMessage++;
    }
    while(charAt != EOF); // stop lorsque le programme arrive a la fin du fichier

    return mess;
}

/* remet a 0 les frequences d apparition des lettres de l alphabet prend en parametre
le tableau des frequences des lettres de l'alphabet
*/
int* RAZFreq(int* alphaFreq){
    // parcours le tableau et met les valeurs à 0
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
        alphaFreq[j]=0;
    }

    return alphaFreq;
}

/* calcul la taille de la cle utilisee pour chiffrer le texte prenant en parametre
le message sans caractere special, l indice de coincidence, la taille de la clef, 
le tableau de fréquence des lettres de l alphabet, la taille du message sans 
caractere speciaux et le nombre de lettre du message
*/
int CalculCleVigenere(char* messageNoSpace, float indiceCoincidence, int tailleKey, int* alphabetFreq, int tailleMessageNoSpace, int nbLettre){

    /* 
    parcours le texte avec un decalage avec des tailles de clef inferieur a 16 et tant que l'indice de coincidence n'est pas compris entre
    0.075 et 0.085
    */
    while(tailleKey < 16 && (indiceCoincidence < 0.075 || indiceCoincidence > 0.085)){
            indiceCoincidence = 0;
            tailleKey++;
            // parcours le texte toute les k lettres depuis la lettre de position k
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
                // calcul l'indice de coincidence
                for (int i = 0; i < ALPHABET_SIZE; ++i)
                {
                    unsigned char c = (unsigned char) (i+'A');
                    indiceCoincidence += (float)(alphabetFreq[i]*(alphabetFreq[i]-1.0))/(float)(nbLettre*(nbLettre-1.0));
                }
                alphabetFreq = RAZFreq(alphabetFreq);
                //fprintf(logFile," n lettre : %d\n",nbLettre );
            }
            indiceCoincidence /= tailleKey;
        }
        printf("La taille de la clé est de : %d\n\n\n", tailleKey);
        return tailleKey;
}

/* cherche la cle utilisee pour chiffrer le texte prenant en parametre
le message sans caractere special, l indice de coincidence, la taille de la clef, 
le tableau de fréquence des lettres de l alphabet, la taille du message sans 
caractere speciaux, le tableau de caractere de la cle et le nombre de lettre du message
*/
char* ChercheCle(int tailleKey, char* messageNoSpace, int* alphabetFreq, int max, char* key, int tailleMessageNoSpace, int nbLettre){
    // recherche dans chaque sous texte la lettre la plus utiliser correspondant au decalage de son texte et trouve la lettre correspondante
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
    }
    return key;
}

/* 
fonction de déchiffrement de Vigenere prenant en paramètre la clef obtenue dans 
la fonction Vigenere_break et le nom du fichier du texte chiffrer (du type : texte.txt)
et stock le resultat dans un fichier
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

// decrypte le chiffrement par substitution
void SubstitutionBreak(){

}

// decrypte le chiffre de Vigenere a l aide de la fonction de dichiffrement de Vigenere
void VigenereBreak(){

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

	fileCipherText = fopen(fileName, "r");

	if (fileCipherText != NULL)
	{
        message=LireTxt(fileCipherText, message);
        tailleMessage=strlen(message);
        fclose(fileCipherText);
        messageNoSpace=TxtSansSpeChar(message, tailleMessage, messageNoSpace);
        tailleMessageNoSpace=strlen(messageNoSpace);
        tailleKey=CalculCleVigenere(messageNoSpace, indiceCoincidence, tailleKey, alphabetFreq, tailleMessageNoSpace, nbLettre);
        alphabetFreq=RAZFreq(alphabetFreq);
        key=ChercheCle(tailleKey, messageNoSpace, alphabetFreq, max, key, tailleMessageNoSpace, nbLettre);
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
        // lis le texte et incremente la frequence de chaque lettre lorsquelle est rencontree
		do{
        	charAt=fgetc(fileCipherText);
        	if (charAt >= 'A' && charAt <= 'Z')
        	{
        		alphabetFreq[charAt-'A'] += 1;
        	}
        }
        while(charAt != EOF);
        fclose(fileCipherText);
        // cherche la lettre la plus utiliser dans le tableau de frequence
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
        // calcule la valeur du decalage en supposant la lettre la plus utilisee
        key = cryptedLetter - 'E';
        if (key<0)
        {
        	key = -key;
        }
        printf("La clé est donc : %d\n", key);
        fileCipherText = fopen(fileName, "r");
        // lis le texte chiffre et le reecris decrypte dans un autre fichier
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