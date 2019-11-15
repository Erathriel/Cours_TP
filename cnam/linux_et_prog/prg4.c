/****************************************************
|													|
|			Fichier : prg4.c						|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void erreurFin(const char* msg){perror(msg);exit(1);}

int main(int argc, char const *argv[])
{
	printf("Lancement de la ligne de commande ls | wc -l \n");
	int fd[2];
	pipe(fd);
	if (fork()==0)
	{ // Le fils
		printf("FILS is running\n");
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		close(fd[1]);
		execl("/bin/ls","ls",NULL);{ erreurFin("pb sur exec ls"); }
	}
	else{
		printf("PERE is running\n");
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		execl("/usr/bin/wc","wc","-l",NULL);{ erreurFin("pb sur exec wc"); };
	}
	return 0;
}