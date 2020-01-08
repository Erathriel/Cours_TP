#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>


typedef struct
{
	long type;
	pid_t pidEmetteur;
	int nb_un;
	int nb_deux;
} trequeteClient;

typedef struct 
{
	long type; // Prend la valeur du pid client
	int res; // Resultat de l'operation
}treponse;

int main(int argc, char const *argv[])
{
	int msgid; // valeur de retour de la creation de la file
	key_t key; // valeur de retour de la cration de la cle
	int longMSG;
	trequeteClient requete;
	treponse reponse;
	int pid;

	/****************************************************************/
	/*  Creation de la clé IPC 					*/
	/*  key_t ftok(const char *pathname, int proj_id);              */
	/****************************************************************/

    if ((key = ftok(argv[0], 'A')) == -1) {
		perror("Erreur de creation de la clé \n");
		exit(1);
    }

	/****************************************************************/
	/* Creation de la file de message 				*/
	/* int msgget(key_t key, int msgflg);				*/
	/****************************************************************/

    if ((msgid = msgget(key, 0750 | IPC_CREAT | IPC_EXCL)) == -1) { //int msgget(key_t key, int msgflg);
		perror("Erreur de creation de la file\n");
		exit(1);
    }
    switch(pid==fork())
    {
	    case (pid_t) 0:
	    	printf("...\n");
			requete.type=1;
			requete.pidEmetteur=getpid();
			printf("Nombre 1 :\n");
			scanf("%d",&requete.nb_un);
			printf("Nombre 2 :\n");
			scanf("%d",&requete.nb_deux);
			//requete.nb_un=1;
			//requete.nb_deux=2;
			
			if (msgsnd(msgid,&requete,sizeof(trequeteClient) - sizeof(long),0) == -1){
				perror("Erreur de ecriture fils requete \n");
				exit(1);
			}
			printf("Requête envoyée par le client.\n");
			/*if(msgrcv(msgid,&reponse,sizeof(treponse) - sizeof(long),getpid(),0) == -1){
				perror("Erreur de lecture fils requete \n");
				exit(1);
			}
			printf("Le Resultat est : %d \n",reponse.res); */
			exit(0);
	    default:
		    /* Lecture de la requête */
		    wait(NULL);
				
				if ((longMSG = msgrcv(msgid, &requete, sizeof(trequeteClient) - sizeof(long), 1,0)) == -1) {
				    printf("valeur de retour : %d \n ", longMSG);
				    perror("Erreur de lecture pere requete \n");
				    exit(1);
				}
				printf("nb 1 %d\n", requete.nb_un);
				printf("nb 2 %d\n", requete.nb_deux);

				//reponse.res = requete.nb_un + requete.nb_deux;
				//reponse.type = requete.pidEmetteur;

				/*if (msgsnd(msgid, &reponse, sizeof(treponse) - sizeof(long),0) == -1) {
				    perror("Erreur de ecriture pere requete \n");
				    exit(1);
				}*/

    }
	/* A tester */  
	msgctl(msgid, IPC_RMID, NULL);

    return 0;
}