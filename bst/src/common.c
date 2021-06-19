#include <stdio.h>
#include <stdlib.h>
#include "forest.h"
#include "common.h"


void clearScreen(void)
{
    system(CLEAR);
    header();
}


void enterpoint(void)
{
    printf("\n Clique [ENTER] para continuar");
    getchar();
    fflush(stdin);
    clearScreen();
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

	while (!scanf(" %d", &x)) {
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
		if (texto[i] != '\n' || texto[i] != '\t')
            usleep(microsecs);
	}
}


char *getName(char *txtname)
{
	char *txt = txtname;
	int i, size = 0;

	while (*txt != '.' && *txt != '\0' && ++size && ++txt) ;

	char *name = (char *) calloc(size+1, sizeof(char));

	txt = txtname;
	for (i = 0 ; txt[i] != '.' && txt[i] != '\0' ; ++i)
		name[i] = txt[i];

	name[i] = '\0';  // Adiciona o final da string

	return name;
}
