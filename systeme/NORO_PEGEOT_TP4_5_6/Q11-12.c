/***************************************************

Fichier : tp6.c
Date de creation : 01 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>

int main(int argc, char const *argv[])
{
	// Q11
	long int CPU = sysconf(_SC_NPROCESSORS_ONLN);

	// Q12
	int tmp=0;
	int cpuActive = sched_getcpu();

	// Q11
	printf("Le nombre de CPU utilisable est de : %ld\n",CPU);

	//Q12
	while(1){
		tmp = sched_getcpu();
		if(cpuActive == tmp){
			printf("Le cpu est toujours : %d\n",tmp );
		}
		else{
			printf("Le cpu à changer ! C'est devenu : %d \n", tmp);
			cpuActive=tmp;
			exit(1);
		}
	}


	return 0;
}