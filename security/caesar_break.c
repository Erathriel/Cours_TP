#include <stdio.h>
#include <stdlib.h>


#define TAILLE_MAX_MESSAGE 512


int main(int argc, char *argv[]) {

    int freq_alphabet[26] = {0};
    int decalage;
    int taille_message = 0;
    char message[TAILLE_MAX_MESSAGE] = {0};

    int i;
    while ((i = fgetc(stdin)) != '\n') {
        unsigned char c = (unsigned char) i;

        if(c >= 'A' && c <= 'Z'){
            freq_alphabet[c-'A'] += 1;
        }

        if(taille_message < TAILLE_MAX_MESSAGE)
            message[taille_message] = c;
        taille_message += 1;

        printf("%c", c);
    }
    printf("\n");

    char lettreE = 0;
    int freq_E = 0;

    for(i = 0; i < 26; i++){
        if(freq_alphabet[i] > freq_E){
            lettreE = i+'A';
            freq_E = freq_alphabet[i];
        }
        printf("%i ", freq_alphabet[i]);
    }

    if(lettreE < 'A' || lettreE > 'Z' ){
        printf("Aucune lettre majuscule dans le message.\n");
        return 0;
    }

    decalage = lettreE - 'E';

    for(i = 0; i < taille_message && i < TAILLE_MAX_MESSAGE; i++){
        if(message[i] >= 'A' && message[i] <= 'Z'){
            message[i] -= decalage;
            if(message[i] < 'A')
                message[i] += 26;
        }
    }
    printf("\nLa lettre qui apparaît le plus est %c qui apparaît %i fois.\n", lettreE, freq_E);

    printf("Si c'est la lettre E, le décalage est de %i. Dans ce cas, le message est:\n%s\n", decalage, message);



    return 0;
}









