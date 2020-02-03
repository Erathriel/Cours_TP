// /* piscine.c */

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/ipc.h> 
// #include <sys/sem.h>

// #define NBSEM 2
// #define NC 1
// #define NP 2
// #define IFLAGS (SEMPERM | IPC_CREAT)
// #define SKEY   (key_t) IPC_PRIVATE	
// #define SEMPERM 0600		 /* Permission */





// //initialisation 
// int NbCabinesOccupees = 0, NbPaniersOccupes = 0, NbAbonnesAttente = 0;

// // init sem et operande
// int sem_id ;
// struct sembuf sem_oper_P ;  /* Operation P */
// struct sembuf sem_oper_V ;  /* Operation V */

// int initsem(key_t semkey) 
// {
    
// 	int status = 0;		
// 	int semid_init;
//    	union semun {
// 		int val;
// 		struct semid_ds *stat;
// 		short * array;
// 	} ctl_arg;
//     if ((semid_init = semget(semkey, 4, IFLAGS)) > 0) {
		
// 	    	short array[4] = {NC, NP, 1, 1}; // 4 Semaphores : cabines, paniers, mutexcabine, mutexpanier
// 	    	ctl_arg.array = array;
// 	    	status = semctl(semid_init, 0, SETALL, ctl_arg);
//     }
//    if (semid_init == -1 || status == -1) { 
// 	perror("Erreur initsem");
// 	return (-1);
//     } else return (semid_init);
// }

// void libereSem(int semid){
// 	semctl(semid,0,IPC_RMID);
// }


 
// void P(int semnum) {

// sem_oper_P.sem_num = semnum;
// sem_oper_P.sem_op  = -1 ;
// sem_oper_P.sem_flg = 0 ;
// semop(sem_id,&sem_oper_P,1);
// }

// void V(int semnum) {

// sem_oper_V.sem_num = semnum;
// sem_oper_V.sem_op  = 1 ;
// sem_oper_V.sem_flg  = 0 ;
// semop(sem_id,&sem_oper_V,1);
// }

// void Abonne_se_changer(int i){
	
// 	if (NbCabinesOccupees == N) {
// 		NbAbonnesAttente++;
// 		printf("L'abonne %d se bloque car pas de panier disponible \n", i);
// 		NbAbonnesAttente--;
	
// 	} 
// 	/* prend un panier */
// 	printf("L'abonne %d prend un panier \n", i);
// 	NbPaniersOccupes++;
// 	if (NbAbonnesAttente == 0) {
	
	
// 	} 
// 	if (NbCabinesOccupees == C) {
// 		printf("L'abonne %d se bloque car pas de cabine disponible \n", i);
// 	} 
// 	/* entre dans une cabine */
// 	printf("L'abonne %d entre dans une cabine \n", i);
// 	NbCabinesOccupees++;
// 	printf("L'abonne %d se change et libère la cabine \n", i);
// 	NbCabinesOccupees--;
// } 


// void NonAbonne_se_changer(int i){
	
// 	while (NbAbonnesAttente > 0) {
// 		printf("Le non abonne %d se bloque car abonnes en attente \n", i);
		
// 	} 
		
// 	if (NbPaniersOccupes == N) {
// 		printf("Le non abonne %d se bloque car pas de panier disponible \n", i);		
// 	} 
// 	NbPaniersOccupes++;
// 	/* prend un panier */ 
// 	printf("Le non abonne %d prend un panier \n", i);
// 	if (NbCabinesOccupees == C) {
// 		printf("Le non abonne %d se bloque car pas de cabine disponible \n", i);
		
// 	}
// 	NbCabinesOccupees++;
// 	/* entre dans une cabine */ 
// 	printf("Le non abonne %d entre dans une cabine \n", i);
// 	printf("Le non abonne %d se change et libère la cabine \n", i);
// 	NbCabinesOccupees--;
		
// } 

// void Se_rhabiller(int i){
	
// 	if (NbCabinesOccupees == C) {
// 		printf("Le nageur %d veut se rhabiller mais pas de cabine disponible \n", i);
		
// 	} 
// 	/* entre dans une cabine */ 
// 	NbCabinesOccupees++;
// 	printf("Le nageur %d entre dans une cabine \n", i);
// 	printf("Le nageur %d se change et libère la cabine \n", i);
// 	NbCabinesOccupees--;
// 	printf("Le nageur %d libère le panier \n", i);
// 	NbPaniersOccupes--;
	
		
// } 

// void *fonc_Abonne(void *i){
// 	srand();
// 	printf("L'abonne %d arrive ...\n", (int)i);
// 	Abonne_se_changer((int)i);
// 	/* temps de natation */ 
// 	printf("L'abonne %d nage ...\n", (int)i);
// 	usleep(rand() % 200000);
// 	Se_rhabiller((int)i);
// 	printf("L'abonne %d quitte la piscine\n", (int)i);
	
		
// } 
// void *fonc_nonAbonne(void *i){
// 	srand();
// 	printf("Le non abonne %d arrive ...\n", (int)i);
// 	NonAbonne_se_changer((int)i);
// 	/* temps de natation */
// 	printf("Le non abonne %d nage ...\n", (int)i);
// 	usleep(rand() % 200000);
// 	Se_rhabiller((int)i);
// 	printf("Le non  abonne %d quitte la piscine\n", (int)i);
	
		
// } 
// int main() {
// 	int num;
	
// 	exit(0);
	
// } 


/* Piscine.c by Geoffrey */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/sem.h>

#define NBSEM 2
#define NC 0
#define NP 1
#define MUTEX_CABINE 2
#define MUTEX_PANIER 3
#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE	
#define SEMPERM 0600		 /* Permission */


int NbCabinesLibre = 1, NbPaniersLibre = 2;
// Init semaphore
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
    if ((semid_init = semget(semkey, 4, IFLAGS)) > 0) {
		
	    	short array[4] = {0, 0, 1, 1}; // 4 Semaphores : cabines, paniers, mutexcabine, mutexpanier
	    	ctl_arg.array = array;
	    	status = semctl(semid_init, 0, SETALL, ctl_arg);
    }
   if (semid_init == -1 || status == -1) { 
	perror("Erreur initsem");
	return (-1);
    } else return (semid_init);
}

void libereSem(int semid){
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


void attente(int n) {
   sleep(n); 	/*sleep(rand() % n);*/
}

void Se_rhabiller(int i){

	P(MUTEX_CABINE);
	if (NbCabinesLibre == 0)
	{
		V(MUTEX_CABINE);
		printf("PID : %d Pas de cabine dispo, attend une cabine\n", getpid());
		P(NC);
	}
	else{
		V(MUTEX_CABINE);
	}

	//attente(3);

	P(MUTEX_CABINE);
	NbCabinesLibre--;
	printf("PID : %d se rhabiller : NbCabinesLibre : %d \n",getpid(), NbCabinesLibre);
	V(MUTEX_CABINE);

	//attente(3);

	printf("PID : %d La personne se rhabille\n", getpid());

	P(MUTEX_CABINE);
	NbCabinesLibre++;
	printf("PID : %d se rhabiller : NbCabinesLibre : %d \n", getpid(),NbCabinesLibre);
	V(MUTEX_CABINE);
	P(MUTEX_CABINE);
	if (NbCabinesLibre > 0)
	{
		V(MUTEX_CABINE);
		V(NC);
	}
	else{
		V(MUTEX_CABINE);
	}

	//attente(3);


	P(MUTEX_PANIER);
	NbPaniersLibre++;
	printf("PID : %d se rhabiller : NbPaniersLibre : %d \n",getpid(), NbPaniersLibre);
	V(MUTEX_PANIER);
	P(MUTEX_PANIER);
	if (NbPaniersLibre > 0)
	{
		V(MUTEX_PANIER);
		V(NP);
	}
	else{
		V(MUTEX_PANIER);
	}

	//attente(3);

	printf("PID : %d se rhabiller fin de fonction : NbCabinesLibre : %d \n",getpid(), NbCabinesLibre);
	printf("PID : %d se rhabiller fin de fonction : NbPaniersLibre : %d \n",getpid(), NbPaniersLibre);
	printf("PID : %d Je m'en vais a+\n", getpid());

}

void nage(){
	int i = 0;
	while(i<5){
		printf("PID : %d Je nage\n", getpid());
		i++;
	}
}

void se_changer(int i){

	P(MUTEX_PANIER);
	if (NbPaniersLibre==0)
	{
		V(MUTEX_PANIER);
		printf("PID : %d Pas de panier dispo, attend un panier dispo\n", getpid());
		P(NP);
	}
	else{
		V(MUTEX_PANIER);
	}

	//attente(5);

	P(MUTEX_PANIER);
	NbPaniersLibre--;
	printf("PID : %d se changer : NbPaniersLibre : %d \n", getpid(),NbPaniersLibre);
	V(MUTEX_PANIER);

	//attente(3);

	P(MUTEX_CABINE);
	printf("PID : %d se changer : NbCabinesLibre : %d \n", getpid(),NbCabinesLibre);
	if (NbCabinesLibre == 0)
	{
		V(MUTEX_CABINE);
		printf("PID : %d Pas de cabine dispo, attend une cabine\n", getpid());
		P(NC);
	}
	else{
		V(MUTEX_CABINE);
	}

	//attente(3);

	P(MUTEX_CABINE);
	NbCabinesLibre--;
	printf("PID : %d se changer : NbCabinesLibre : %d \n",getpid(), NbCabinesLibre);
	V(MUTEX_CABINE);

	//attente(3);

	printf("PID : %d La personne se change\n", getpid());

	P(MUTEX_CABINE);
	NbCabinesLibre++;
	printf("PID : %d se changer : NbCabinesLibre : %d \n",getpid(), NbCabinesLibre);
	V(MUTEX_CABINE);
	P(MUTEX_CABINE);
	if (NbCabinesLibre > 0)
	{
		V(MUTEX_CABINE);
		V(NC);
	}
	else{
		V(MUTEX_CABINE);
	}

	//attente(3);

	printf("PID : %d se changer fin de fonction : NbCabinesLibre : %d \n", getpid(),NbCabinesLibre);
	printf("PID : %d se changer fin de fonction : NbPaniersLibre : %d \n",getpid(), NbPaniersLibre);
	printf("PID : %d Je vais nager\n", getpid());
}


void nageur(int i){
	if (!fork())
	{
		/* code */
		printf("PID : %d Coucou j'arrive à la piscine\n",getpid() );
		se_changer(i);
		nage();
		Se_rhabiller(i);
		exit(0);
	}
}


int main(int argc, char const *argv[])
{
	sem_id=initsem(SKEY);
	/*for (int i = 0; i < 3; i++)
	{
		if (!fork())
		{
			nageur();
		}
	}*/
	nageur(0);
	nageur(1);
	nageur(2);

	for (int j=1; j<=3; j++) wait(0);

    libereSem(sem_id); //supprime les semaphores  
	return 0;
}	