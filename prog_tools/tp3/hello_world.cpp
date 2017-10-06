#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "./lib/DisplayMessage.h"
#ifdef _SYSTEM_WINDOWS
	#include <windows.h>
#endif

int main(){
	DisplayMessage("test");
	printf("Hello world\n");
	return 0;
}