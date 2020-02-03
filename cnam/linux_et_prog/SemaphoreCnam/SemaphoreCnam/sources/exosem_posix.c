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
sem_t* mutexA;
sem_t* mutexB;

 
/* affichage pour suivi du trajet */
void message(int i, char* s) {
   #define COLONNE 20
   int j, NbBlanc;
   NbBlanc=i*COLONNE;
   for (j=0; j<NbBlanc; j++) putchar(' ');
   printf("%s\n",s);
   fflush(stdout);
}

/* attente en seconde, ou aleatoire */
void attente(int n) {
   sleep(n); 	/*sleep(rand() % n);*/
}

/* creation du processus TGV */
void TGV(int i) {
   if (! fork()) {
	message(i, "depart Paris");
	attente(3);
	message(i, "arrivee Strasbourg");
	attente(3);
	sem_post(mutexA);
	message(i, "depart Strasbourg");
	attente(10);
	message(i, "arrivee Bâle");
	attente(3);
	message(i, "arret");
	exit(0);
   }
}

/* creation du processus TER */
void TER(int i) {
   if (! fork()) {
	message(i, "attente TGV");
	attente(3);
	sem_wait(mutexA);
	message(i, "depart Strasbourg");
	attente(3);
	
	message(i, "arrivee Mulhouse");
	attente(3);
	sem_post(mutexB);
	message(i, "arret");
	exit(0);
   }
}

/* creation du processus taxi */
void Taxi(int i) {
   if (! fork()) {
	message(i, "attente TER");
	attente(3);
	sem_wait(mutexB);
	message(i, "depart Mulhouse");
	attente(3);
	
	message(i, "arrivee Belfort");
	attente(3);
	message(i, "arret");
	exit(0);
   }
}

int main(int argc, char *argv[])
{
   int i;
   mutexA = sem_open("A",O_CREAT, 666, 0);
   mutexB = sem_open("B",O_CREAT, 666, 0);
   printf("%10s%20s%20s\n\n", "TGV", "TER", "TAXI");
  
   TGV(0);
   TER(1);
   Taxi(2);
 
   for (i=1; i<=3; i++) wait(0);

   sem_destroy(mutexA);
   sem_destroy(mutexB);
  
   return 0;
}