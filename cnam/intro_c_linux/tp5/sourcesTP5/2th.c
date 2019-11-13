#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#define NUM_THREADS	3

// thread mode joinable

void erreur(const char *msg)
{
    perror(msg);
    exit(1);
}

void *AfficheEtat(void *data)
{

    long num;
    num = (long) data;
    printf("\nJe suis le thread #%ld \n", num);    
    printf("de TID : %ld \n", (long) pthread_self());
    fflush(stdout);
    pthread_exit(NULL);
}

void *thread1_process(void *data)
{

    long num;
    num = (long) data;
    printf("\nJe suis le thread #%ld \n", num);    
    printf("de TID : %ld \n", (long) pthread_self());
    fflush(stdout);
    pthread_exit(NULL);
}

int main(void)
{

    int i,j, rc;
    pthread_t thread_id[NUM_THREADS];
    // void * retour;
	
    for (i = 0; i < NUM_THREADS; i++) {
	if (rc = pthread_create(&thread_id[i], 0, AfficheEtat, (void *) i) != 0)
	    erreur("Erreur Creation thread");
        pthread_join(thread_id[i],NULL); // Permet d'attendre la fin de chaque thread avant d'en créer un autre
	    //usleep(30000);  
    }
		    	 
    // ajout pour que le thread soit en mode detached

    pthread_attr_t thread_attr;
    pthread_t th1;

    if (pthread_attr_init (&thread_attr) != 0) {
        fprintf (stderr, "pthread_attr_init error");
        exit (1);
    }

    if (pthread_attr_setdetachstate (&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        fprintf (stderr, "pthread_attr_setdetachstate error");
        exit (1);
    }

    // puis de créer les threads avec des appels du type:

    if (pthread_create (&th1, &thread_attr, thread1_process, NULL) < 0) {
        fprintf (stderr, "pthread_create error for thread 1\n");
        exit (1);
    }

	pthread_exit(NULL);
}

