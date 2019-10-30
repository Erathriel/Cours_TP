#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	int child = fork();
	int c=5;
	if(child == 0){
		c+=5;
	}
	else{
		child = fork();
		c+=10;
		if(child!=0){
			c+=5;
		}
	}
	printf("pid = %d\n c = %d\n", getpid(), c);
	return 0;
}