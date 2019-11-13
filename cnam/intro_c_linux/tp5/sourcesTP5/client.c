#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define INITIAL_STOCK   10
#define NB_CLIENTS      3

/* Structure stockant les informations des threads clients et du magasin. */

typedef struct{
   
   pthread_t thread_store;
   pthread_t thread_clients [NB_CLIENTS];
   int valstock;
} T_STORE;

static T_STORE store; 

/* Fonction pour tirer un nombre au sort entre 0 et max. */
int get_random (int max){
   double val;
   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);
   return ((int) val);
}


/* Fonction pour le thread du magasin. */


/* Remise à Zéro du Stock*/
void * fn_store (void * p_data){
   

   return NULL;
}
/*  Fin  Remise à Zéro du Stock*/

/* Fonction Clients. */


/* Fin Fonction Clients */


int main (void){
   int i = 0;
   int ret = 0;

   /* Creation du thread du magasin. */
   printf ("Creation du thread du magasin !\n");
   ret = pthread_create (& store.thread_store, NULL,fn_store, NULL);
   
   /* Creation des threads des clients si celui du magasin a reussi. */
   if (! ret)  {
      printf ("Creation des threads clients !\n");
      for (i = 0; i < NB_CLIENTS; i++) {
         ret = pthread_create ( & store.thread_clients [i], NULL, fn_clients, (void *)i);
         if (ret) {
            fprintf (stderr, "%s", strerror (ret));
         }
      }
   }
   else{
      fprintf (stderr, "%s", strerror (ret));
   }

   
   /* Attente de la fin des threads. */
   
   /* Fin Attente Fin Thread */
   
}

