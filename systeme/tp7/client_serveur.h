#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/* Création d un serveur */
extern int creer_serveur_tcp ( int , int, int );
/* Attente d un client */
extern int attendre_client_tcp ( int , int );
/* Dans un serveur retourne l adresse du client connecté */
extern char *  adresse_client ( void );
/* Création d un client */
extern int creer_client_tcp ( char * , int , int );
/* Retourne l adresse en format réseau de l adresse en notation pointée */
extern int adresse (char *, int );
/* Création d un serveur */
extern int creer_serveur_udp ( int , int );
/* Création d un client */
extern int creer_client_udp ( char * , int, struct sockaddr_in *,
                              struct sockaddr_in *, int);
/* Lit ou écrit n caractères sur un descripteur ne s arrête qu'en cas d'erreur */
extern int ecrire_n ( int, char * , int);
extern int lire_n   ( int, char *, int);