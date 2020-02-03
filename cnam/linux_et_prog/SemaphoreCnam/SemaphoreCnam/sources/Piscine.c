 /* piscine.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/sem.h>

#define NBSEM 2
#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE	
#define SEMPERM 0600		 /* Permission */


// init sem et operande
int sem_id ;
struct sembuf sem_oper_P ;  /* Operation P */
struct sembuf sem_oper_V ;  /* Operation V */

int initsem(key_t semkey) 
{
    
	int status = 0;		
	int semid_init;
   	union semun {
		int val;
		struct semid_ds *stat;
		short * array;
	} ctl_arg;
    if ((semid_init = semget(semkey, NBSEM, IFLAGS)) > 0) {
		
	    	short array[NBSEM] = {0, 0};
	    	ctl_arg.array = array;
	    	status = semctl(semid_init, 0, SETALL, ctl_arg);
    }
   if (semid_init == -1 || status == -1) { 
	perror("Erreur initsem");
	return (-1);
    } else return (semid_init);
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


//initialisation 
int NbCabinesOccupees = 0, NbPaniersOccupes = 0, NbAbonnesAttente = 0;


void Abonne_se_changer(int i){
	
	if (NbCabinesOccupees == N) {
		NbAbonnesAttente++;
		printf("L'abonne %d se bloque car pas de panier disponible \n", i);
		NbAbonnesAttente--;
	
	} 
	/* prend un panier */
	printf("L'abonne %d prend un panier \n", i);
	NbPaniersOccupes++;
	if (NbAbonnesAttente == 0) {
	
	
	} 
	if (NbCabinesOccupees == C) {
		printf("L'abonne %d se bloque car pas de cabine disponible \n", i);
	} 
	/* entre dans une cabine */
	printf("L'abonne %d entre dans une cabine \n", i);
	NbCabinesOccupees++;
	printf("L'abonne %d se change et libère la cabine \n", i);
	NbCabinesOccupees--;
} 


void NonAbonne_se_changer(int i){
	
	while (NbAbonnesAttente > 0) {
		printf("Le non abonne %d se bloque car abonnes en attente \n", i);
		
	} 
		
	if (NbPaniersOccupes == N) {
		printf("Le non abonne %d se bloque car pas de panier disponible \n", i);		
	} 
	NbPaniersOccupes++;
	/* prend un panier */ 
	printf("Le non abonne %d prend un panier \n", i);
	if (NbCabinesOccupees == C) {
		printf("Le non abonne %d se bloque car pas de cabine disponible \n", i);
		
	}
	NbCabinesOccupees++;
	/* entre dans une cabine */ 
	printf("Le non abonne %d entre dans une cabine \n", i);
	printf("Le non abonne %d se change et libère la cabine \n", i);
	NbCabinesOccupees--;
		
} 

void Se_rhabiller(int i){
	
	if (NbCabinesOccupees == C) {
		printf("Le nageur %d veut se rhabiller mais pas de cabine disponible \n", i);
		
	} 
	/* entre dans une cabine */ 
	NbCabinesOccupees++;
	printf("Le nageur %d entre dans une cabine \n", i);
	printf("Le nageur %d se change et libère la cabine \n", i);
	NbCabinesOccupees--;
	printf("Le nageur %d libère le panier \n", i);
	NbPaniersOccupes--;
	
		
} 

void *fonc_Abonne(void *i){
	srand();
	printf("L'abonne %d arrive ...\n", (int)i);
	Abonne_se_changer((int)i);
	/* temps de natation */ 
	printf("L'abonne %d nage ...\n", (int)i);
	usleep(rand() % 200000);
	Se_rhabiller((int)i);
	printf("L'abonne %d quitte la piscine\n", (int)i);
	
		
} 
void *fonc_nonAbonne(void *i){
	srand();
	printf("Le non abonne %d arrive ...\n", (int)i);
	NonAbonne_se_changer((int)i);
	/* temps de natation */
	printf("Le non abonne %d nage ...\n", (int)i);
	usleep(rand() % 200000);
	Se_rhabiller((int)i);
	printf("Le non  abonne %d quitte la piscine\n", (int)i);
	
		
} 
int main() {
	int num;
	
	exit(0);
	
} 
