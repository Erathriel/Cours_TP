#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define L 2
#define N 3

int main(int argc, char const *argv[])
{
	// variable
	float A[L][N] = {{1.0,2.5,3.0},{2.0,3.0,2.5}};
	float B[N] = {0.5,1.0,0.0};
	float * R = (float *) calloc(3,sizeof(float));
	float t;

	// fonction affichage vecteur
	void affiche_vecteur(int nbElem, float v[nbElem]){

		for (int i = 0; i < nbElem; ++i)
		{
			printf("(%f) \n", v[i] );
		}
	}

	// calcul du produit matrice - vecteur
	for (int i = 0; i < L; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			t = A[i][j] * B[j];
			R[i] += t;
		}
	}
	
	affiche_vecteur(L,R);

	free(R);

	return 0;
}