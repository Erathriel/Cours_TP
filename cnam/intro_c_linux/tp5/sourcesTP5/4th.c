
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	8

char *messages[NUM_THREADS];

void *AfficheMessage(void *threadid)
{
	int *i = (int *) threadid;
	int num = *i;
	printf("Je suis dans le thread %d \n", num);
	printf("Mon message est : %s \n", messages[num]);
	fflush(stdout);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];

/* Declaration de 8 pointeurs de int */

int *taskids[NUM_THREADS]; 
int rc, t;

messages[0] = "Message 1";
messages[1] = "Message 2";
messages[2] = "Message 3";
messages[3] = "Message 4";
messages[4] = "Message 5"; 
messages[5] = "Message 6";
messages[6] = "Message 7";
messages[7] = "Message 8";

for(t=0;t<NUM_THREADS;t++) {
  taskids[t] = (int *) malloc(sizeof(int));
  *taskids[t] = t;
  
  printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, AfficheMessage, (void *) taskids[t]);
  if (rc) {
    printf("Erreur Creation Threads %d\n", rc);
    exit(-1);
    }
  }

pthread_exit(NULL);
}
