/***************************************************

Fichier : tp6.c
Date de creation : 01 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	if (argc > 1 && argc < 3)
	{
		if (atoi(argv[1]) > -1 && atoi(argv[1]) < 8)
		{
			int CPUchoisi = atoi(argv[1]);
			long int nbCPU = sysconf(_SC_NPROCESSORS_ONLN);
			int tmp=0;
			int cpuActive = sched_getcpu();
			cpu_set_t setCPU;
			CPU_ZERO(&setCPU);
			CPU_SET(CPUchoisi,&setCPU);

			if (sched_setaffinity(getpid(), sizeof(setCPU), &setCPU) == -1)
			{
				printf("affinity error\n");
			}

			else{

				while(1){

					tmp = sched_getcpu();

					if(cpuActive == tmp){
						printf("Le cpu est toujours : %d\n",tmp );
					}

					else{
						printf("Le cpu est devenu : %d \n",tmp );
						cpuActive=tmp;
					}
				}
			}
		}
		else{
			printf("Veuillez entrer une valeur correcte !\n");
		}
	}
	else{
		printf("nombre d'arguments incorrect\n");
	}

	return 0;
}