#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define MAX_CLEAN_REPEAT_TIMES 32

#ifdef unix
    #include <unistd.h>
    #define CLEAR() (system("clear"));
#endif // linux

#ifdef _WIN32
    #include <Windows.h>
    #define CLEAR() (system("cls"))
#endif // _WIN32


void enterpoint(void)
{
    printf("\n Clique [enter] para continuar");
    getchar();
    fflush(stdin);
    CLEAR();
}


void cleanbuf(void)
{
	int times = 0;
	char c;

	/* Limpa o buffer, caso tiver muitas tentativas, termina a execução. */
	while ((c = getc(stdin)) != '\n' && c != EOF) {

		if (times++ > MAX_CLEAN_REPEAT_TIMES) {

			printf("\n erro: atingiu-se o limite de falha!");
			sleep(2);

			exit(1);

		}
	}
}


int get_int(void)
{
	int x;
	while (!scanf("%d", &x)) {
		cleanbuf();
		printf("\n Valor Inválido, insira um inteiro: ");
	}

	return x;
}


void animate(const char *texto, unsigned int microsecs)
{
	int i = 0;
	while (texto[i] != '\0') {
		fprintf(stdout, "%c", texto[i++]);
		fflush(stdout);
		usleep(microsecs);
	}
}
