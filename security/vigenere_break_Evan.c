#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define TAILLE_MAX_MESSAGE 65536
#define TAILLE_MAX_CLE 128
#define OUTPUT_FILE "break.txt"

#define INDICE_COINC    0.075f
#define MARGE_INDICE    0.002f



int main(int argc, char *argv[]) {

    unsigned short int freq_alphabet[26][TAILLE_MAX_CLE][TAILLE_MAX_CLE] = {{{0}}};
    int taille_message = -1;
    int nb_lettres_message = 0;
    int nb_lettres = 0;
    char message[TAILLE_MAX_MESSAGE] = {0};
    float indiceCoincidence;
    float indiceCoincRecord = 0.0f;
    int taille_cle;
    int taille_cle_indice_record = 0;
    unsigned char c;
    bool boucle = true;
    int i = 0;
    int j;
    int boucle_clef = 0;
    FILE * fichier = stdin;

    if(argc > 1){
       fichier = fopen(argv[1], "r");
       if (fichier==NULL){
        printf ("Error opening file: %s",argv[1]);
        return 0;
       }
    }
    else
        printf("Vous pouviez également entrer le nom d'un fichier texte en argument.\n");
    /*fichier = fopen("test.txt", "r");
    if (fichier==NULL){
	 printf ("Error opening file: %s",argv[1]);
	 return 0;
    }*/

    while ((i = fgetc(fichier)) != EOF) {
      c = (unsigned char) i;

      if(c >= 'A' && c <= 'Z'){
        nb_lettres_message += 1;
      }

      if( (taille_message+1) < TAILLE_MAX_MESSAGE){
          taille_message += 1;
          message[taille_message] = c;
      }

      printf("%c", c);
    }
    printf("\n");

    fclose(fichier);

    if(nb_lettres_message < 2){
        printf("Pas assez de lettres majuscules (il y en a %i).\n", nb_lettres_message);
        return 0;
    }

    for(taille_cle = 0; taille_cle < nb_lettres_message && taille_cle < TAILLE_MAX_CLE && boucle; taille_cle++){


        for(j = 0; j< taille_cle; j++){
            indiceCoincidence = 0.0f;
            boucle_clef = taille_cle - j;
            nb_lettres = 0;

            //if(taille_cle < 12) printf("%i ", taille_cle);
            for(i = 0; i< taille_message+1; i++){
                c = message[i];

                if(c >= 'A' && c <= 'Z'){
                    if( boucle_clef >= taille_cle){     //ne prend qu'une lettre par clé
                        freq_alphabet[c-'A'][j][taille_cle] ++;
                        nb_lettres ++;
                        boucle_clef = 0;
                        //if(taille_cle < 12) printf("%c",c);
                    }
                    //else{ if(taille_cle < 12) printf("_"); }
                    boucle_clef ++;
                }
            }

            if(nb_lettres >= 4){
              for(i = 0; i<26; i ++ ){
              indiceCoincidence = indiceCoincidence +
                  ( (float)freq_alphabet[i][j][taille_cle]*((float)freq_alphabet[i][j][taille_cle]-1.000f) )
                      / ( (float)nb_lettres*((float)nb_lettres-1.000f) );
              //printf("%i %f %i %i  ",taille_cle, indiceCoincidence, nb_lettres, freq_alphabet[i][j]);
              }
              if(taille_cle < 12) printf("\n%i %f ",taille_cle, indiceCoincidence);
              //if( fabs(indiceCoincidence - INDICE_COINC) < fabs(indiceCoincRecord - INDICE_COINC) ){
              if( fabs(indiceCoincidence - INDICE_COINC) < MARGE_INDICE) {
                  indiceCoincRecord = indiceCoincidence;
                  taille_cle_indice_record = taille_cle;
                  boucle = false;
              }
            }
        }

    }

    if(indiceCoincRecord <= 0){
	  printf("Erreur, texte trop court?\n");
	  return 0;
    }


    printf("L'indice de coincidence pour une taille de clef %i est de %f (%f+/-%f).\n"
           ,taille_cle_indice_record, indiceCoincRecord, INDICE_COINC, MARGE_INDICE);


    taille_cle = taille_cle_indice_record;

    char cle[taille_cle+1];
    cle[taille_cle] = '\0';

    int freq_E;
    char lettreE;
    int decalage;

      for(j = 0; j < taille_cle; j++){
          cle[j] = 'A';
          freq_E = 0;
          lettreE = '\0';
          for(i = 0; i < 26; i++){
              if(freq_alphabet[i][j][taille_cle] > freq_E){
                  lettreE = i+'A';
                  freq_E = freq_alphabet[i][j][taille_cle];
              }
              printf("%i ", freq_alphabet[i][j][taille_cle]);
          }
          decalage = lettreE - 'E';
          cle[j] += decalage;
          if(cle[j] < 'A')
              cle[j] += 26;
          if(cle[j] > 'Z')
              cle[j] -= 26;
          printf("\n%i lettreE: %c, %i fois, decalage: %i, dechiffree: %c \n"
            , j, lettreE, freq_E, decalage, cle[j]);
      }

    printf("La clef est alors:\n%s\n", cle);

    /*
    printf("  ");
    for(j = 0; j<taille_cle; j++){
        printf("%i", j);
        if(j < 10)
          printf("   ");
    }
    printf("\n");
    int total_verif = 0;
    for(i = 0; i<26; i++){
        printf("%c ", i+'A');
        for(j = 0; j<taille_cle; j++){
            printf("%i", freq_alphabet[i][j][taille_cle]);
            total_verif += freq_alphabet[i][j][taille_cle];
            if(freq_alphabet[i][j][taille_cle] < 10)
              printf(" ");
            if(freq_alphabet[i][j][taille_cle] < 100)
              printf(" ");
            if(freq_alphabet[i][j][taille_cle] < 1000)
              printf(" ");
        }
        printf("\n");
    }

  printf("%i / %i\n", total_verif, nb_lettres_message);*/


  fichier = fopen(OUTPUT_FILE, "w");
  if (fichier==NULL){
    printf ("Error opening file: %s",OUTPUT_FILE);
    return 0;
  }
    boucle_clef = 0;
  for (i = 0; i < taille_message; i++){

        c = message[i];

        if(c >= 'A' && c <= 'Z'){
            c -= (cle[boucle_clef] - 'A');
            if(c < 'A')
                c += 26;
            boucle_clef += 1;
            if(boucle_clef >= taille_cle)
                boucle_clef = 0;
        }
        fputc ( c , fichier );
  }

  fclose(fichier);
  
  printf("Texte déchiffré dans le fichier %s\n", OUTPUT_FILE);

  return 0;

}
