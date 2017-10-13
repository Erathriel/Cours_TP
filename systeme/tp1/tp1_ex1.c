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
	// Exercice 1 !
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
    sprintf(f->str, "Hello world !"); // Son write a message in the segment
    if(shmdt(f) == -1){ // Segment detache
      printf("Error segment can't be detached \n");
    }
    else
    {
      printf("Segment detached \n");
    }
  }
  else {
    sleep(1); // Wait the death of his son
    printf("Father read : %s \n smhid : %d \n", p->str, shmId); // Read his son message
    shmdt(p);
    shmctl(shmId, IPC_RMID, NULL); // Delete segment
  }
  return 0;

}












