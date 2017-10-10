#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
	char *key;
	key = argv[1];
	int i;

	printf("%s\n", key );

	for(int j=0; j<strlen(key); j++){
		unsigned char c = (unsigned char) key[j];
		printf("%c\n", c );
	}

	char sentance[256];
	fgets(sentance, 256, stdin);
	printf("%s\n", sentance);

	for(int i=0; i<strlen(sentance); i++){
		unsigned char c = (unsigned char) sentance[i];
		printf("%c\n", c );
	}
	int value;
	int compteur=0;
	for(int k=0; k<strlen(sentance)-1; k++){
		if(sentance[k]== ' '){
			printf(" ");
			compteur++;
		}
		else {
			//printf("%c , %s , %c, %i \n",sentance[k], key, key[k%strlen(key)], (sentance[k] - key[k%strlen(key)]) );
			value = (sentance[k] - key[(k-compteur)%strlen(key)]+26)%26;
			//printf("%i\n", value);
			unsigned char c = (unsigned char) (value+65);
			printf("%c", c);
		}
	}
	printf("\n");

	return 0;
}
