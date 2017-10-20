#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define foreach( ptrvar, strvar ) char* ptrvar; for( ptrvar=strvar ; (*ptrvar) != '\0' ; *ptrvar++)

int main(int argc, char *argv[]) {
	// récupération de la clé passer en paramètre
	char *key=NULL;
	key = argv[1];
	char *plainText = argv[2];
	char cipherText[26];
	char *motSansDouble;
	motSansDouble=malloc(sizeof(char)*26);
	char *alphabet=NULL;
	alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int place = 0;

	printf("%s\n", key );

	for (int c = 0; c < strlen(key); c++)
	{
		int d=0;
		for (int i = 0; i < strlen(key); i++)
		{
			if(motSansDouble[i]==key[c]){
				d++;
			}
		}
		if(d == 0){
			motSansDouble[place]=key[c];
			place++;
		}
	}

	for (int j = 0; j < strlen(alphabet); j++)
	{
		int compt = 0;
		for (int k = 0; k < strlen(motSansDouble); k++)
		{
			if (alphabet[j]==motSansDouble[k])
			{
				compt++;
			}
		}
		if (compt==0)
		{
			motSansDouble[place]=alphabet[j];
			place++;
		}
	}

	for (int l = 0; l < strlen(plainText); l++)
	{
		unsigned char c = (unsigned char) plainText[l]-65;
		cipherText[l] = motSansDouble[l];
		

	}

	printf("test\n");
	printf("%s\n", alphabet );
	printf("%s\n", motSansDouble);
	printf("text chiffré : %s\n", cipherText);

	free(motSansDouble);
	return 0;
}