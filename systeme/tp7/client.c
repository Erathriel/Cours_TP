/***************************************************

Fichier : client.c
Date de creation : 07 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


#include <stdio.h>
#include <stdlib.h> 
#define PORT 6666

int main(void)
{
    int erreur = 0;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[32] = "Hello World !";

    if (!erreur)
    {
       sock = socket(AF_INET, SOCK_STREAM, 0); // creation socket

       // config socket
       sin.sin_addr.s_addr = inet_addr("127.0.0.1");
       sin.sin_family = AF_INET;
       sin.sin_port = htons(PORT);
       bzero(sin.sin_zero,8);

       //connexion au serveur
       if (connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
       {
            printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            //send(sock, buffer, sizeof(buffer), 0);
       }
       else 
       {
            printf("Impossible de se connecter\n");
        }
        shutdown(sock,SHUT_RDWR);
        close(sock);
    }
    return EXIT_SUCCESS;
}