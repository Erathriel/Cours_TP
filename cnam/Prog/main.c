#include "vigenere.c"

int main(int argc, char const *argv[])
{
	/*char *key;
	key = argv[1];

	printf("La clé : %s\n", key );

	char sentance[256];
	fgets(sentance, 256, stdin);

	printf("La phrase : %s\n", sentance);

	vigenereEncryption(sentance, key);
	//vigenereDecrypt(sentance,key);
	
	return 0;*/

	int a,b;
 	printf("choisir a : \n");
 	scanf("%d", &a);
 	printf("choisir b : \n");
 	scanf("%d", &b);

	printf("resultat de a + b = %d \n", addition(a,b));

}