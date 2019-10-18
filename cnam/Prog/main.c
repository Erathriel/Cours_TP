#include "vigenere.c"
#include "tp2.c"

int main(int argc, char const *argv[])
{

	//tp1

	/*char *key;
	key = argv[1];

	printf("La clé : %s\n", key );

	char sentance[256];
	fgets(sentance, 256, stdin);

	printf("La phrase : %s\n", sentance);

	vigenereEncryption(sentance, key);
	//vigenereDecrypt(sentance,key);
	
	return 0;*/

	/*int a,b;
 	printf("choisir a : \n");
 	scanf("%d", &a);
 	printf("choisir b : \n");
 	scanf("%d", &b);

	printf("resultat de a + b = %d \n", addition(a,b));*/

	// tp2

	/*produit *tabProduit;
	int nbProduit = demandeNbProduit();
	tabProduit = malloc(nbProduit * sizeof(produit));

	for (int i = 0; i < nbProduit; ++i)
	{
		tabProduit[i] = *creerProduit();
		printf("=========================\n     Next      \n=========================\n");
	}

	printf("le total prix = %f \n", calculPrixTotal(tabProduit,nbProduit));
	free(tabProduit);*/
	

	// tp 2_1

	ListeEntier l;
	l.maillon = NULL;
	int a;
	int b;
	int c;
	a=5;
	b=10;
	c=8;
	ajouter_debut(&l,a);
	ajouter_debut(&l,b);
	afficher_liste(&l);
	printf("La taille de la liste est : %d \n",taille(&l));
	ajouter_fin(&l,c);
	afficher_liste(&l);
	printf("La taille de la liste est : %d \n",taille(&l));
	supprimer_debut(&l);
	afficher_liste(&l);
	printf("La taille de la liste est : %d \n",taille(&l));
	supprimer_fin(&l);
	afficher_liste(&l);
	printf("La taille de la liste est : %d \n",taille(&l));

	return 0;
}