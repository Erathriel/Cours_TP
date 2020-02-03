#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

#define SKEY (key_t) IPC_PRIVATE
#define IFLAGS (SEMPERM | IPC_CREAT)
#define SEMPERM 0600


// Pour operande P et V
int sem_id;
sem_t* mutexPanier;
sem_t* mutexCabine;
sem_t* NC;
sem_t* NP;

/* attente en seconde, ou aleatoire */
void attente(int n) {
   sleep(n); 	/*sleep(rand() % n);*/
}



int main(int argc, char *argv[])
{
   int i;
   mutexPanier = sem_open("mutexPanier",O_CREAT, 666, 0);
   mutexCabine = sem_open("mutexCabine",O_CREAT, 666, 0);
   NC = sem_open("NC", O_CREAT, 666, 0);
   NP = sem_open("NP", O_CREAT, 666, 0);
  
  
 
   for (i=1; i<=3; i++) wait(0);

   sem_destroy(mutexA);
   sem_destroy(mutexB);
  
   return 0;
}