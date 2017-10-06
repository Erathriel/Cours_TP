#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void DisplayMessage(const char *szMessage){
#ifdef _SYSTEM_LINUX
	printf("%s\n", szMessage);
#endif
#ifdef _SYSTEM_WINDOWS
	MessageBox(NULL,szMessage,NULL,NULL);
#endif
}