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
		printf("Thread %d créer\n", nbre);
		nbre ++ ;
		pthread_join(thr,NULL);
		usleep(10000);
	}

	fprintf(stderr,"Echec de creation après %d \n", nbre);
	return EXIT_SUCCESS;
}
			
void *fonction_thread (void * arg) {
	printf("Hello world !\n");
	#ifdef __LINUX__
		char *os = "A true OS";
		printf("%s\n", os);
		getchar();
		system("clear");
	#endif
	#ifdef WIN32
		char *os = "A blue screen";
		printf("%s\n", os);
		system("PAUSE");
		system("CLS");
	#endif
	return NULL ;

}  

