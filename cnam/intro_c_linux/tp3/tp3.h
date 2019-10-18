#ifndef TP3_H
#define TP3_H

typedef struct
{
	char *name;
	int id;
	float price;
} data;

void echangeValeur(int *val1, int *val2);
void echangeStruct(data *val1, data *val2);
void testStruct();


#endif // TP3_H