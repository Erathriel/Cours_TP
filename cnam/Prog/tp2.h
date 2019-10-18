#ifndef TP2_H
#define TP2_H

typedef struct{

	int code;
	float prix;
	int quantite;

} produit;

int demandeNbProduit();

produit* creerProduit();

float calculPrixTotal(produit *tab, int taille);

typedef struct Maillon Maillon;

struct Maillon{

	int valeur;
	Maillon *m;

};

typedef struct 
{

	Maillon *maillon;

} ListeEntier;

void ajouter_debut(ListeEntier* l, int v);

void ajouter_fin(ListeEntier* l, int v);

void afficher_liste(ListeEntier* l);

void supprimer_debut(ListeEntier* l);

void supprimer_fin(ListeEntier *l);

int taille(ListeEntier *l);

void supprimer_tout(ListeEntier *l, int v);

#endif // TP2_H