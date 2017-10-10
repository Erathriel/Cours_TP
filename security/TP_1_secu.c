#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int i;
	while ((i = fgetc(stdin)) != EOF) {
		unsigned char c = (unsigned char) i;
		printf("%c\n", c);
	}
	return 0;
}
