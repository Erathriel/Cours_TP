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
	
	
	return 0;
}