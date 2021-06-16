#ifndef COMMON_H
#define COMMON_H

#ifdef unix
    #include <unistd.h>
    #define CLEAR() (system("clear"));
#endif // linux

#ifdef _WIN32
    #include <Windows.h>
    #define CLEAR() (system("cls"))
#endif // _WIN32

int get_int(void);

void animate(const char *texto, unsigned int milisecs);
#endif // COMMON_H
