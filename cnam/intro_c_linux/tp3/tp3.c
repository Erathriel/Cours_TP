#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void echangeValeur(int *val1, int *val2){
	int *tmp = *val1;
	*val1 = *val2;
	*val2 = tmp;
}

void echangeStruct(data *val1, data *val2){
	data *tmp =malloc(sizeof(data));
	*tmp = *val1;
	*val1 = *val2;
	*val2 = *tmp;
}

void testStruct(){
	int val1 = 5;
	int val2 = 2;

	echangeValeur(&val1,&val2);
	printf("val 1 : %d \n val 2 : %d \n", val1, val2 );

	data *data1;
	data *data2;

	data1 = malloc(sizeof(data));
	data2 = malloc(sizeof(data));

	data1->name="data1";
	data1->id=1;
	data1->price=3.20;
	data2->name="data2";
	data2->id=2;
	data2->price=3.25;

	echangeStruct(data1,data2);

	printf("nom : %s id : %d price : %f \n", data1->name, data1->id, data1->price );
	printf("nom : %s id : %d price : %f \n", data2->name, data2->id, data2->price );
}
