#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>


#define SIZE_MESSAGE 256

int main(int argc, char *argv[])
{
	struct data { char str[SIZE_MESSAGE];};
  	int shmId;
  	char message[SIZE_MESSAGE];
	key_t key = ftok("./",'h'); // Key creation
	shmId = shmget(key,SIZE_MESSAGE,0644);
  	struct data* p2 = shmat(shmId,NULL,0); // Attache segement
	printf("I read : %s \n", p2->str);
	char *mess= p2->str;
	sprintf(p2->str,"Bonjour %s", mess);
	shmdt(p2);
}
