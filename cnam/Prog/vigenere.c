#include "vigenere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void vigenereEncryption(char* text, char* key){
	int value;
	int compteur=0;
	for(int k=0; k<strlen(text)-1; k++){
		if(text[k]== ' '){
			printf(" ");
			compteur++;
		}
		else{
			value = (text[k] + key[(k-compteur)%strlen(key)])%26;
			unsigned char c = (unsigned char) (value+65);
			printf("%c", c);
		}
	}
	printf("\n");
}

void vigenereDecrypt(char* text, char* key){
	int value;
	int compteur=0;
	for(int k=0; k<strlen(text)-1; k++){
		if(text[k]== ' '){
			printf(" ");
			compteur++;
		}
		else {
			value = (text[k] - key[(k-compteur)%strlen(key)]+26)%26;
			unsigned char c = (unsigned char) (value+65);
			printf("%c", c);
		}
	}
	printf("\n");
}

int addition(int a, int b){
	int resultat;
 	resultat = a + b;
 	return resultat;
}