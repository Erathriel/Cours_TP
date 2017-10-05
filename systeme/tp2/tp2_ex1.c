#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>

// -Wall -Wextra

// multiplication function !
int mult(int fact, int x) {
 	x=fact*x;
	return x;
}

void map(int *tab, int lg, int (*mult)(int,int), int fact){	
	for(int i=0; i<lg; i++){
		printf("Element numéro %i de base : %d \n",i,tab[i]);
		tab[i]=(*mult)(tab[i],fact);
		printf("Element numéro %i multiplié : %d \n",i,tab[i]);
	}
}

int main(int argc, char *argv[])
{	
	int tab[]={1,2,3,4};
	int lg=4;
	int fact = atoi(argv[1]);
	int (*pMult)(int,int);
	pMult = mult;
	map(tab,lg,pMult,fact);
	return 0;
}
