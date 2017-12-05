/***************************************************

Fichier : client.c
Date de creation : 07 novembre 2017
Auteur : NORO Geoffrey & PEGEOT Antoine

***************************************************/

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAILLE 256


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[TAILLE];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0); // creation socket
     // verification ouverture socket
     if (sockfd < 0) 
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr)); // init buffer
     portno = atoi(argv[1]); // recuperation du numero de port place en parametre

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     // verification de la liaison entre la struct sockaddr et le socket
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     // Definition de la taille de file de connexion en attente pour le socket
     listen(sockfd,5);

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,TAILLE); // init du buffer
     // reception du nom envoye par le client
     n = recv(newsockfd,buffer,(TAILLE-1),0);
     if (n < 0) error("ERROR reading from socket");
     printf("Le serveur va répondre : Bonjour %s\n",buffer); 
     char buffer2[TAILLE+50] = {"Bonjour "};
     strcat(buffer2, buffer);
     // renvoie du message du serveur au client
     n = send(newsockfd,buffer2,strlen(buffer2),0); 
     if (n < 0) error("ERROR writing to socket");



    return 0;
}
