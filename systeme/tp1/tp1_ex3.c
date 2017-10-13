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
  	shmId = shmget(key,SIZE_MESSAGE,IPC_CREAT | 0644); // Segment creation
  	struct data* p1=(struct data *)shmat(shmId,NULL,0); // Attache segement
	sprintf(p1->str, "Jean");
	fgetc(stdin);
	printf(" %s \n", p1->str);
}
