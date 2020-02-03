/* Exemple de synchronisation par semaphores                  */
/*    trajet Paris-Belfort synchronise par semaphores         */
/*    Un voyageur part de Paris a destination de Perros.      */
/*    Il doit emprunter :                                     */
/*            . le TGV de Paris a Strasbourg,                 */
/*            . le TER de Strasbourg a Mulhouse,              */
/*            . le taxi de Mulhouse a Belfort.                */
/*    TGV, TER et taxi sont 3 processus independants          */
/*    qui se synchronisent pour amener le voyageur a bon port */
/*    Execution :                                             */
/*                                                            */
/*       TGV             TER                    TAXI          */
/*                                                            */
/* depart Paris                                               */
/*                    attente TGV                             */
/*                                        attente TER         */
/* arrivee Strasbourg                                         */
/* depart Strasbourg                                          */
/*                    depart Strasbourg                       */
/*                    arrivee Mulhouse                        */
/*                    arret                                   */
/*                                        depart Mulhouse     */
/*                                        arrivee Belfort     */
/* arrivee Bâle                                               */
/*                                        arret               */
/* arret                                                      */
/**************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE	
#define SEMPERM 0600		 /* Permission */


/*********************************************************************/
/*  Pour Operation P et V 					     */

int sem_id ;
struct sembuf sem_oper_P ;  /* Operation P */
struct sembuf sem_oper_V ;  /* Operation V */

/*********************************************************************/

int initsem(key_t semkey) 
{
    
	int status = 0;		
	int semid_init;
   	union semun {
		int val;
		struct semid_ds *stat;
		short * array;
	} ctl_arg;
    if ((semid_init = semget(semkey, 2, IFLAGS)) > 0) {
		
	    	short array[2] = {0, 0};
	    	ctl_arg.array = array;
	    	status = semctl(semid_init, 0, SETALL, ctl_arg);
    }
   if (semid_init == -1 || status == -1) { 
	perror("Erreur initsem");
	return (-1);
    } else return (semid_init);
}

void libereSem(int semnum){
	semctl(semid,0,IPC_RMID);
}
 
void P(int semnum) {

sem_oper_P.sem_num = semnum;
sem_oper_P.sem_op  = -1 ;
sem_oper_P.sem_flg = 0 ;
semop(sem_id,&sem_oper_P,1);
}

void V(int semnum) {

sem_oper_V.sem_num = semnum;
sem_oper_V.sem_op  = 1 ;
sem_oper_V.sem_flg  = 0 ;
semop(sem_id,&sem_oper_V,1);
}

 
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
	V(0);
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
	P(0);
	message(i, "depart Strasbourg");
	attente(3);
	
	message(i, "arrivee Mulhouse");
	attente(3);
	V(1);
	message(i, "arret");
	exit(0);
   }
}

/* creation du processus taxi */
void Taxi(int i) {
   if (! fork()) {
	message(i, "attente TER");
	attente(3);
	P(1);
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
   int i,semid;
   printf("%10s%20s%20s\n\n", "TGV", "TER", "TAXI");
  
   semid=initsem(SKEY);
   TGV(0);
   TER(1);
   Taxi(2);
 
   for (i=1; i<=3; i++) wait(0);

   libereSem(semid); //supprime les semaphores  
  
   return(0);
}



