#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>


void *fonction_thread (void * arg) ; 

int main(void) {
	pthread_t thr;
	int nbre = 0;
	while ( pthread_create(&thr,NULL,fonction_thread,NULL) == 0) {
		nbre ++ ;
	}

	fprintf(stderr,"Echec de creation après %d \n",
		nbre);
	return EXIT_SUCCESS;
}
			
void *fonction_thread (void * arg) {
	return NULL ;

}  

