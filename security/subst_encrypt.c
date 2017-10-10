#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define foreach( ptrvar, strvar ) char* ptrvar; for( ptrvar=strvar ; (*ptrvar) != '\0' ; *ptrvar++)

int main(int argc, char *argv[]) {
	// récupération de la clé passer en paramètre
	char *key=NULL;
	key = argv[1];
	char *motSansDouble=NULL;
	motSansDouble=malloc(sizeof(char)*26);
	int e = 0;

	printf("%s\n", key );

	/*for(int j=0; j<strlen(key); j++){
		unsigned char c = (unsigned char) key[j];
		printf("%c\n", c );
	}*/

	for (int c = 0; c < strlen(key); c++)
	{
		int d=0;
		for (int i = 0; i < strlen(key); ++i)
		{
			if(motSansDouble[i]==key[c]){
				d++;
			}
		}
		if(d == 0){
			motSansDouble[e]=key[c];
			e++;
		}
	}

	printf("%s\n", motSansDouble);

	free(motSansDouble);
	return 0;
}