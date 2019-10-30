#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Exemple 1 : 1 pere et 2 fils

/*int main(){
	int child = fork();
	int c=5;
	if(child == 0){
		c+=5;
	}
	else{
		child = fork();
		c+=10;
		if(child!=0){
			c+=5;
		}
	}
	printf("pid = %d\n c = %d\n", getpid(), c);
	return 0;
}*/

// Exemple 2 : fork, wait, exit

/*int main(int argc, char const *argv[])
{
	pid_t pid;
	int i,j;
	int status;

	for (int i = 0; i < 8; ++i)
	{
		i+=j;
	}

	pid = fork();

	if (pid == 0)
	{	
		printf("je suis le fils\n");
		exit(0);
	}
	else{
		printf("je suis le père\n");
		printf("pid de mon fils = %d\n", pid);
		wait(&status);
		printf("retour dans le père\n");
	}
}*/

// Exemple 3 :modif du 2

/*int main(int argc, char const *argv[])
{
	int status;
	pid_t pid;
	int returned;

	pid=getpid();
	printf("Le pid actuelle est : %d\n", pid);

	pid=fork();

	switch(pid){
		case -1 :
			fprintf(stderr, "erreur du fork\n");
			exit(1);
			break;
		case 0 :
			printf("On est dans le fils et son pid est : %d \n", getpid());
			printf("Hello, je suis le fils\n");
			exit(23);
			break;

		default :
			printf("Hello je suis le père et je vais attendre mon fils\n");
			wait(&status);
			returned=WEXITSTATUS(status);
			if (WIFEXITED(status))
			{
				printf("La valeur de status est : %d \n", returned);
			}
			break;
	}
}*/

// Exemple 4 : appeller exec

int main(int argc, char const *argv[])
{
	int status, returned;
	pid_t pid = fork();

	switch(pid){
		case -1 :
			fprintf(stderr, "erreur du fork\n");
			exit(1);
			break;
		case 0 :
			printf("Je suis dans le fils je vais executer $ calcul 5 6\n");
			execl("calcul","calcul","5", "6",NULL); // plus précis avec le chemin absolue
			exit(-1);
		default :
			printf("Hello je suis le père et je vais attendre mon fils qui execute calcul\n");
			wait(&status);
			returned=WEXITSTATUS(status);
			if (WIFEXITED(status))
			{
				printf("La valeur de status est : %d \n", returned);
			}
			break;
	}
}