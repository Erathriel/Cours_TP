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
	// Exercice 2
  struct data { char str[SIZE_MESSAGE];};
  int shmId;
  char message[SIZE_MESSAGE];
  key_t key = ftok("./",'h'); // Key creation
  shmId = shmget(key,SIZE_MESSAGE,IPC_CREAT | 0644); // Segment creation
  struct data* p=(struct data *)shmat(shmId,NULL,0); // Attache segement 
  pid_t pid_fils = fork(); // Create son
  
  if (pid_fils == -1) {
    perror("fork"); // error
  }
  else if (pid_fils == 0) {
    struct data* f = shmat(shmId,NULL,0); // Attache segment
    printf("Child read : %s \n smhid : %d \n", p->str, shmId); // Son read of his father
    if(shmdt(f) == -1){
      printf("Error segment can't be detched \n");
    }
    else
    {
      printf("Segment detached \n");
    }
  }
  else {
    sprintf(p->str, "Hello world !"); // Father write a message
    wait(NULL);
    shmdt(p);
    shmctl(shmId, IPC_RMID, NULL); // Delete segment
  }
  return 0;

}

