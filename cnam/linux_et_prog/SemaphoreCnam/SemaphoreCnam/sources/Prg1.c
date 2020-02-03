#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define IFLAGS (SEMPERM | IPC_CREAT)
#define SKEY   (key_t) IPC_PRIVATE	
#define SEMPERM 0600		 /* Permission */


/*****************************************************************************************/
/*                 Structure dans le noyau du sémaphore  		*/    
/*     #include <sys/sem.h>				*/
/*					*/
/*	struct _sem  {				*/
/*					*/	
/*	unsigned short int semval  ;  Valeur du sémaphore		*/
/*      unsigned short int sempid  ;  Pid du dernier processus utilisateur	*/	
/*	unsigned short int semncnt ;  Nbre attentes augmentation sémaphore	*/ 	
/*	unsigned short int semzcnt ;  Nbre attentes nullité sémaphore           */ 	
/* 	}				*/
/*                                                                                        */
/*                 Caractéristique d'un ensemble de sémaphores 		*/ 
/*	struct semid_ds {	  			*/
/*                                                                                        */
/*      struct ipc_perm sem_perm   ;  Permissions			*/
/*      struct _sem *sem_base      ;  Pointeur premier sémaphore		*/  
/*      unsigned short sem_nsems   ;  Nbre sémaphore                                      */ 
/*	time_t sem_otime	   ;  Date de la dernière opération                   */
/*	time_t sem_ctime	   ;  Date du dernier changement                      */                                                                         
/*****************************************************************************************/


/*****************************************************************************************/
/*     int semctl(int semid, int semnum, int cmd, ...);                                  */
/*                                                                                       */
/*    Permet de consulter ou de modifier le paramétrage d'un jeu de sémaphores           */
/*                                                                                       */
/*     union semun {                                                                     */
/*          int	     val    ;  Valeur pour SETVAL uniquement                           */
/*	    struct semid_ds * buffer ;  Tampon pour IPC_STAT, IPC_SET          */
/*          unsigned short int *  array  ;  Table pour GETALL, SETALL                    */
/*     }                                                                                 */
/*                                                                                       */
/*****************************************************************************************/


/*****************************************************************************************/
/*                                                                                       */
/*    Action sur les sémaphores			                 */
/*                                                                                       */
/*     struct sembuf {                                                                   */
/*          unsigned short	  sem_num    ;  Numéro de sémaphore                  */
/*	    short sem_op     ;  Opération sur le sémaphore                     */
/*          short sem_flag   ;  flag d'opération = 0 généralement                        */
/*     }                                                                                 */
/*                                                                                       */
/*****************************************************************************************/



int initsem(key_t semkey) 
{
    
	int status = 0;		
	int semid_init;
   	union semun {
		int val;
		struct semid_ds *stat;
		short * array;
	} ctl_arg;
    if ((semid_init = semget(semkey, 3, IFLAGS)) > 0) {
		
	    	short array[3] = {0, 0, 0};
	    	ctl_arg.array = array;
	    	status = semctl(semid_init, 0, SETALL, ctl_arg);
    }
   if (semid_init == -1 || status == -1) { 
	perror("Erreur initsem");
	return (-1);
    } else return (semid_init);
}

 
int main(void) 
{
    
	struct semid_ds semid_ds;
    	int c, i, length;
   	int uid, gid, mode;
   	int retrn, semid, semnum, cmd, choice;
   	short semvals[25];
   	union semun {
		int val;
		struct semid_ds *buf;
		short * array;
	} arg;
    	if ((semid = initsem(SKEY)) < 0)	/* Création d'un ensemble de sémaphore */
	return(1);

    	printf("Valeur du Semid %d \n",semid);
 	printf("Entrer le Semid = ");
   	scanf("%d", &semid);
    
	
	printf("\nFaites votre choix\n");
   	printf("La commande désirée:\n");
   	printf("GETVAL = 1\n");
   	printf("SETVAL = 2\n");
   	printf("GETPID = 3\n");
   	printf("GETNCNT = 4\n");
   	printf("GETZCNT = 5\n");
    	printf("GETALL = 6\n");
    	printf("SETALL = 7\n");
    	printf("IPC_STAT = 8\n");
    	printf("IPC_SET = 9\n");
    	printf("IPC_RMID = 10\n");
    	printf("Entrée = ");
    	scanf("%d", &cmd);

	
	printf("\nsemid =%d, cmd = %d\n\n", semid, cmd);
    	
	switch (cmd) {
	case 1:			/*Renvoie la valeur semval du semno-ième sémaphore 
				  de l'ensemble */

		printf("\nEntrez le numéro de Sémaphore = ");
		scanf("%d", &semnum);
		
	    	retrn = semctl(semid, semnum, GETVAL, arg);
		printf("\nThe semval = %d", retrn);
		break;
	case 2:			/*Place la valeur arg.val dans le champ semval */
		printf("\nEntrez le numéro de Sémaphore = ");
		scanf("%d", &semnum);
		printf("\nEntrez la valeur = ");
		scanf("%d", &arg.val);
		
	    	retrn = semctl(semid, semnum, SETVAL, arg);
		break;
    	case 3:			/*Renvoie la valeur de sempid pour le semno-ième sémaphore. */
		retrn = semctl(semid, 0, GETPID, arg);
		printf("\nLe sempid = %d", retrn);
		break;
    	case 4:			/*Renvoie la valeur de semncnt pour le semno-ième sémaphore. */

		printf("\nEntrez le numéro de Sémaphore = ");
		scanf("%d", &semnum);
		
		retrn = semctl(semid, semnum, GETNCNT, arg);
		printf("\nValeur de semncnt = %d", retrn);
	break;
    	case 5:			/*Renvoie la valeur de semzcnt pour le semno-ième sémaphore. */
		printf("\nEntrez le numéro de Sémaphore = ");
		scanf("%d", &semnum);
		 
	   	retrn = semctl(semid, semnum, GETZCNT, arg);
		printf("\nValeur de semzcnt = %d", retrn);
	break;
    	case 6:			/*Renvoie la valeur semval de chaque semaphore 
				  de l'ensemble dans le tableau arg.array */
	    	arg.buf = &semid_ds;
		retrn = semctl(semid, 0, IPC_STAT, arg);
		if (retrn == -1) goto ERROR;
		length = arg.buf->sem_nsems;
		
	    	arg.array = semvals;
		retrn = semctl(semid, 0, GETALL, arg);
		for (i = 0; i < length; i++) {
	    		printf("%d", semvals[i]);
	    		
			printf(" ");
		}
	
		break;
    	case 7:			/*Mettre tout les semaphores dans l'ensemble. 
				  Donner le nombre de semaphores de l'ensemble.*/ 
	    arg.buf = &semid_ds;
	    retrn = semctl(semid, 0, IPC_STAT, arg);
	    if (retrn == -1) goto ERROR;
	    length = arg.buf->sem_nsems;
	    printf("Longueur = %d\n", length);
	    
	    printf("\nEntrez chaque valeur:\n");
	    for (i = 0; i < length; i++) {
	   	scanf("%d", &c);
		semvals[i] = c ;
	    }
		     
	    arg.array = semvals;
	    retrn = semctl(semid, 0, SETALL, arg);
	    break;
    
	case 8:			/*Donner l'état du set */
				/*Donner et Afficher les valeurs de l'état courant. */ 
	    arg.buf = &semid_ds;
	    retrn = semctl(semid, 0, IPC_STAT, arg);
	    printf("\nLe USER ID = %d\n", arg.buf->sem_perm.uid);
	    printf("Le GROUP ID = %d\n", arg.buf->sem_perm.gid);
            	    printf("Permissions = 0%o\n",arg.buf->sem_perm.mode);
	    printf("Nombre de semaphores dans le set = %d\n",arg.buf->sem_nsems);
	    printf("Temps de la dernière opération = %ld\n",arg.buf->sem_otime);
	    printf("Le dernier Changement = %ld\n", arg.buf->sem_ctime);
	break;
    
	case 9:			/*Selectionner et changer un membre de la structure de donnée  */
	    arg.buf = &semid_ds;
	    retrn = semctl(semid, 0, IPC_STAT, arg.buf);
	    if (retrn == -1) goto ERROR;
	    
	    printf("\nEntrez le numéro pour \n");
	    printf("Le membre a changé:\n");
	    printf("sem_perm.uid = 1\n");
	    printf("sem_perm.gid = 2\n");
                      printf("sem_perm.mode = 3\n");
	    printf("Entrez = ");
	    scanf("%d", &choice);

	    switch (choice) {	
		case 1:		/*Change le user ID. */
			printf("\nEntrez USER ID = ");
			scanf("%d", &uid);
			arg.buf->sem_perm.uid = uid;
			printf("\nUSER ID = %d\n", arg.buf->sem_perm.uid);
	    	break;
	
		case 2:		/*Change le groupe ID. */
			printf("\nEntrez GROUP ID = ");
			scanf("%d", &gid);
			arg.buf->sem_perm.gid = gid;
	    		printf("\nGROUP ID = %d\n",arg.buf->sem_perm.gid);
	    
		break;
	
		case 3:		/*Changer les  permissions. */
	    
			printf("\nEntrez MODE en octal = ");
			scanf("%o", &mode);
			arg.buf->sem_perm.mode = mode;
	    		printf("\nMODE = 0%o\n", arg.buf->sem_perm.mode);
		break;
	
		default: exit(-1);
	}
	
	    retrn = semctl(semid, 0, IPC_SET, arg);
	
	break;
    
	case 10:			/*Suppression de l'objet IPC */
		retrn = semctl(semid, 0, IPC_RMID, arg);
		break;
    
	default: exit(-1);
	
	}
    

	if (retrn == -1)
	 { 
	ERROR: printf("\nErreur de semctl, Numéro erreur = %d\n",errno);
	exit(0);
	}
	printf("\n\nL'opération Semclt a bien fonctionnée\n");
    	printf("pour le semid = %d\n", semid);
	/* Facultatif */	
	semctl(semid, 0, IPC_RMID, arg);
    	
	return(0);
}


 
 
 
 
