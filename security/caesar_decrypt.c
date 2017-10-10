#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	int key;
	key = atoi(argv[1]);
	int i;
	int j=0;
	int value;
	while ((i = fgetc(stdin)) != EOF) {
		value = i - (key%26);
		unsigned char c = (unsigned char) (value);
		if(c>32 && c<65){
			c=90-(64-c);
			printf("%c", c);
		}
		else if(i == 32) {
			c=32;
			printf("%c", c);
		}
		else if(i == 10) {
			c=10;
			printf("%c", c);
		}		
		else {
			printf("%c", c);
		}
	}
	return 0;
}
