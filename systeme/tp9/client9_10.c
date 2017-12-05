/***************************************************

Fichier : client.c
Date de creation : 07 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAILLE 256

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[TAILLE];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]); // recuperation du numero de port place en parametre
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // creation socket
    // verification ouverture socket
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]); // recuperation de l'ip du serveur placer en parametre
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // init buffer
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr, 
        server->h_length);
    serv_addr.sin_port = htons(portno);
    // connection au serveur
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Entrez votre nom: ");
    bzero(buffer,TAILLE); // init buffer
    fgets(buffer,TAILLE-1,stdin); // recupere le nom entré par l'utilisateur
    // envoie d'un message au serveur
    n = send(sockfd,buffer,strlen(buffer),0);
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,TAILLE);
    // reception du message du serveur
    n = recv(sockfd,buffer,(TAILLE-1),0);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer); 
    return 0;
}
