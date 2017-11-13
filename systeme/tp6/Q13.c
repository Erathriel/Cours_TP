/***************************************************

Fichier : tp6.c
Date de creation : 01 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	
	int tmp=0;
	int cpuActive = sched_getcpu();
	cpu_set_t setCPU;
	CPU_ZERO(&setCPU);
	CPU_SET(0,&setCPU);
	if (sched_setaffinity(getpid(), sizeof(setCPU), &setCPU) == -1)
	{
		perror("affinity error");
	}

	

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

	return 0;
}