#include "tp2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int demandeNbProduit(){
	int nbProduit;
	printf("Combien de produit voulez vous ? \n");
	scanf("%d", &nbProduit);
	return nbProduit;
}

produit* creerProduit(){
	produit *p = malloc(sizeof(produit));
	printf("entrez code produit : \n");
	scanf("%d", &p->code);
	printf("entrez prix produit : \n");
	scanf("%f", &p->prix);
	// p->prix <=> (*p).prix
	printf("entrez quantité produit : \n");
	scanf("%d", &p->quantite);
	return p;
}

float calculPrixTotal(produit *tab, int taille){
	float total=0;
	// crochet = etoile pour les pointeur
	for (int i = 0; i < taille; ++i)
	{
		total += ((tab[i].prix)*(tab[i].quantite));
	}

	return total;
}

// tp2_1

void ajouter_debut(ListeEntier* l, int v){
	Maillon *m = malloc(sizeof(Maillon));
	m->valeur = v;
	m->m = l->maillon;
	l->maillon = m;
}

void ajouter_fin(ListeEntier* l, int v){
	Maillon *m = malloc(sizeof(Maillon));
	m->valeur = v;
	m->m = NULL;
	if (l->maillon == NULL)
	{
		ajouter_debut(l,v);
	}
	else{
		Maillon* tmp = l->maillon;

		while(tmp->m != NULL){
			tmp = tmp->m;
		}

		tmp->m = m;
	}
}

void afficher_liste(ListeEntier* l){
	Maillon *tmp = l->maillon;
	while(tmp != NULL){
		printf(" %d -> ", tmp->valeur);
		tmp= tmp->m;
	}
	printf("\n");
}

void supprimer_debut(ListeEntier* l){
	Maillon *tmp = malloc(sizeof(Maillon));
	tmp = l->maillon;
	l->maillon=l->maillon->m;
	free(tmp);
}

void supprimer_fin(ListeEntier *l){
	Maillon *tmp = malloc(sizeof(Maillon));
	tmp = l->maillon;
	while(tmp->m->m != NULL){
		tmp = tmp->m;
	}
	free(tmp->m);
	tmp->m=NULL;
}

int taille(ListeEntier *l){
	int compteur=0;
	Maillon *tmp = malloc(sizeof(Maillon));
	tmp = l->maillon;
	while(tmp != NULL){
		tmp = tmp->m;
		compteur++;
	}
	return compteur;
}

void supprimer_tout(ListeEntier *l, int v){
	Maillon *tmp = malloc(sizeof(Maillon));
	tmp = l->maillon;
	while(tmp->m != NULL ){
		if (tmp->m->valeur == v)
		{
			
		}
	}
}