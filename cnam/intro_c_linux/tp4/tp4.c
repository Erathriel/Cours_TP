/****************************************************
|													|
|			Fichier : tp4.c							|
|			Auteur : NORO Geoffrey					|
|													|
****************************************************/

#include "tp4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// programme de copie d'un fichier 
void copyFile(){
	char *namePath1;
	char *namePath2;

	namePath1=malloc(sizeof(char)*256);
	namePath2=malloc(sizeof(char)*256);

	printf("type the name of the file you want to copy :\n");
	scanf("%s",namePath1);
	printf("type the name of the destination file :\n");
	scanf("%s",namePath2);

	FILE *file1 = fopen(namePath1,"r");
	char charAt;

	if (file1 != NULL)
	{
		FILE *file2 = fopen(namePath2,"w");
		if (file2 != NULL)
		{
			do{
				charAt = fgetc(file1);
				fputc(charAt,file2);
			}
			while(charAt != EOF);
			fclose(file2);
		}
		else{
			fprintf(stderr, "Error : impossible d'ouvrir le fichier %s ou %s", namePath1, namePath2);
		}
		fclose(file1);
	}
	else {
		fprintf(stderr, "Error : impossible d'ouvrir le fichier %s ou %s", namePath1, namePath2);
	}

	free(namePath1);
	free(namePath2);
}

// Menu
void faireChoix(){
	int choix = 0; // user choice variable

	// textual interface
	printf("---------------------------------------------------\n");
	printf("----                  Welcome                  ----\n");
	printf("---------------------------------------------------\n");
	printf("You are in the menu of the tp4 of system\n");
	printf("What do you want to do ?\n");
	printf("1) Copy a file\n");
	printf("2) Count the  numb of char in a file\n");
	printf("3) Print the size of file in bits\n");
	printf("4) Create a file and write the data what do you want in this file\n");
	printf("9) Exit\n");
	scanf("%d", &choix);

	switch(choix){
		case 1 :
			system("clear");
			printf("You choose the copy of file\n");
			copyFile();
			returnMenu();
			break;
		case 2 :
			system("clear");
			printf("You choose count the numb of char in a file\n");
			printf("the number of char of this file is : %d \n", countChar());
			returnMenu();
		case 3 :
			system("clear");
			printf("You choose to print the size of file in bits\n");
			printf("the number of char of this file is : %d \n", taille());
			returnMenu();
		case 4 :
			system("clear");
			printf("You choose create a file and write the data what do you want in this file\n");
			creer();
			returnMenu();
		case 9 :
			system("clear");
			printf("You choose to leave the program see you soon !\n");
			break;

		default :
			system("clear");
			printf("Your choice isn't 1 or 9 ! Please enter again your choice\n");
			faireChoix();
			break;
	}
}

// return to the menu
void returnMenu(){
	int choix = 0;

	printf("Do you want to leave the program or return to the menu ?\n");
	printf("1) back to menu\n2) Quit\n");
	scanf("%d", &choix);

	switch(choix){
		case 1 :
			system("clear");
			faireChoix();
			break;
		case 2 :
			system("clear");
			printf("You choose to leave the program see you soon !\n");
			break;
		default :
			system("clear");
			printf("Your choice isn't 1 or 9 ! Please enter again your choice\n");
			returnMenu();
			break;
	}
}

int countChar(){
	char *namePath;
	namePath=malloc(sizeof(char)*256);

	printf("type the name of the file :\n");
	scanf("%s",namePath);

	FILE *file = fopen(namePath,"r");
	char charAt;

	int nbChar=0;

	if (file != NULL)
	{
		do{
			charAt = fgetc(file);
			nbChar++;
		}
		while(charAt != EOF);
		fclose(file);
	}
	else {
		fprintf(stderr, "Error : impossible d'ouvrir le fichier %s", namePath);
	}

	free(namePath);
	return nbChar;
}

int taille(){
	int nbChar = countChar();
	int taille = nbChar * 8;
	return taille;
}

void creer(){
	char *namePath;
	char *msg;
	namePath=malloc(sizeof(char)*256);
	msg = malloc(sizeof(char)*256);

	printf("type the name of the file :\n");
	scanf("%s",namePath);

	FILE *file = fopen(namePath,"w");

	if (file != NULL)
	{
		printf("write your text here if you want to stop type EOF :\n");
		while(strcmp(fgets(msg,256,stdin),"EOF\n")){
			if (strcmp(msg,"\n"))
			{
				fputs(msg,file);
			}
		}
		fclose(file);
	}
	else {
		fprintf(stderr, "Error : impossible d'ouvrir le fichier %s", namePath);
	}

	free(namePath);
}