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

int main(int argc, char const *argv[])
{
	int erreur = 0;
    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKET csock;
    SOCKADDR_IN csin;
    char buffer[1024]="Hello world";
    int port=atoi(argv[1]);
    int sinSize = sizeof csin;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == INVALID_SOCKET)
	{
    	printf("socket()\n");
    	return EXIT_FAILURE;
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    bzero(sin.sin_zero,8);
	
    if(bind (sock, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
    	printf("bind()\n");
        return EXIT_FAILURE;
	}

	if(listen(sock, 5) == SOCKET_ERROR)
	{
	    printf("listen()\n");
	    return EXIT_FAILURE;
	}

	csock = accept(sock, (SOCKADDR *)&csin, &sinSize);

	if (csock == INVALID_SOCKET)
	{
		printf("accept()\n");
		return EXIT_FAILURE;
	}

	send(csock, &buffer, sizeof(buffer),0);

    shutdown(csock,SHUT_RDWR);
    close(csock);
	shutdown(sock,SHUT_RDWR);
    close(sock);

	return EXIT_SUCCESS;
}