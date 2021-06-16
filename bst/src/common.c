#include <stdio.h>
#include <stdlib.h>
#include "common.h"


#ifdef unix
    #include <unistd.h>
    #define CLEAR() (system("clear"));
#endif // linux

#ifdef _WIN32
    #include <Windows.h>
    #define CLEAR() (system("cls"))
#endif // _WIN32


void animate(const char *texto, unsigned int milisecs)
{
	int i = 0;
	while (texto[i] != '\0') {
		fprintf(stdout, "%c", texto[i++]);
		fflush(stdout);
		usleep(milisecs);
	}
}
