#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

float calculMediane(int* tab, int nbValeur){
	int compteur=0;
	int mediane = tab[abs(nbValeur/2)];
	for (int i = 0; i < nbValeur; ++i)
	{
		if (tab[i]<=mediane)
		{
			compteur++;
		}
	}
	printf("nb valeur %d \n", nbValeur);
	printf("mediane %d\n", mediane );
	printf("compteur : %d \n", compteur );
	return (compteur*100)/nbValeur;
}

float calculQuart(int* tab, int nbValeur){
	int compteur=0;
	int quart = tab[abs(nbValeur/4)];
	for (int i = 0; i < nbValeur; ++i)
	{
		if (tab[i]<=quart)
		{
			compteur++;
		}
	}
	return (compteur*100)/nbValeur;
}

float calculTroisQuart(int* tab, int nbValeur){
	int compteur=0;
	int troisQuart = tab[abs(nbValeur*0.75)];
	for (int i = 0; i < nbValeur; ++i)
	{
		if (tab[i]<=troisQuart)
		{
			compteur++;
		}
	}
	return (compteur*100)/nbValeur;
}

void fusion(int tableau[],int deb1,int fin1,int fin2)
{
        int *table1;
        int deb2=fin1+1;
        int compt1=deb1;
        int compt2=deb2;
        int i;
        
        table1=malloc((fin1-deb1+1)*sizeof(int));

        //on recopie les éléments du début du tableau
        for(i=deb1;i<=fin1;i++)
            {
            table1[i-deb1]=tableau[i];
            }
                        
        for(i=deb1;i<=fin2;i++)
            {        
            if (compt1==deb2) //c'est que tous les éléments du premier tableau ont été utilisés
                {
                break; //tous les éléments ont donc été classés
                }
            else if (compt2==(fin2+1)) //c'est que tous les éléments du second tableau ont été utilisés
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute les éléments restants du premier tableau
                compt1++;
                }
            else if (table1[compt1-deb1]<tableau[compt2])
                {
                tableau[i]=table1[compt1-deb1]; //on ajoute un élément du premier tableau
                compt1++;
                }
            else
                {
                tableau[i]=tableau[compt2]; //on ajoute un élément du second tableau
                compt2++;
                }
            }
        free(table1);
}
        

void tri_fusion_bis(int tableau[],int deb,int fin)
{
        if (deb!=fin)
            {
            int milieu=(fin+deb)/2;
            tri_fusion_bis(tableau,deb,milieu);
            tri_fusion_bis(tableau,milieu+1,fin);
            fusion(tableau,deb,milieu,fin);
            }
}

void tri_fusion(int tableau[],int longueur)
{
     if (longueur>0)
            {
            tri_fusion_bis(tableau,0,longueur-1);
            }
}

int main(int argc, char const *argv[])
{
	// Q4 : augmenter arg v copier coller 3 quart remplacer 0.75 par valeur entre 0 et 1 du argv (flemme)
	if(argc<2)
	{
		printf("Veuillez saisir le bon nombre d'argument de la maniere suivante : \n ./nomDeLExecutable nbValeur \n");
		return EXIT_FAILURE;
	}
	else if(argc>2) {
		printf("Nombre d'argument trop grand veuillez utiliser la syntaxe suivante : \n ./nomDeLExecutable nbValeur \n");
		return EXIT_FAILURE;
	}
	else {
		int arg1=atoi(argv[1]);
		int* vRand = (int*) calloc(arg1, sizeof(int));
		//printf("%d\n", RAND_MAX);
		//int* vRand =malloc(arg1 *sizeof(int));
		srand(time(NULL)); // initialisation de rand
		//printf("%d\n", arg1);
		for (int i = 0; i < arg1; ++i)
		{
			vRand[i]=rand()%100;
		}
		tri_fusion(vRand,arg1);
		for (int i = 0; i < arg1; ++i)
		{
			printf("| %d |\n", vRand[i]);
		}

		printf("pourcentage inf mediane : %f \n", calculMediane(vRand,arg1));
		printf("pourcentage inf quart 1 : %f \n", calculQuart(vRand,arg1));
		printf("pourcentage inf quart 3 : %f \n", calculTroisQuart(vRand,arg1));

		free(vRand);
	}
	return 0;
}