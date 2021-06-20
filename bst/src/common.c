#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "forest.h"
#include "common.h"
#include "treeprinter.h"

#define MAX_CLEAN_REPEAT_TIMES 32


void line(int lim)
{
    printf("\n ");
    for (int i = 0 ; i < lim ; ++i)
        printf("%s", ROOT_BRANCH);
    printf("\n");
}


void clearScreen(bool show_header)
{
    system(CLEAR);

    if (show_header == true)
        header();
}


void enterpoint(bool show_header)
{
    fflush(stdin);
    printf("\n\n Clique em [ENTER] para continuar");
    getchar();
    fflush(stdin);
    clearScreen(show_header);
}


void cleanbuf(void)
{
	int times = 0;
	char c;

	/* Limpa o buffer, caso tiver muitas tentativas, termina a execução. */
	while ((c = getc(stdin)) != '\n' && c != EOF) {
		if (times++ > MAX_CLEAN_REPEAT_TIMES) {

			printf("\n erro: atingiu-se o limite de falha!");
			SLEEP(2000);

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


void animate(const char *texto, unsigned int milisecs)
{
	int i = 0;
	while (texto[i] != '\0') {
		fprintf(stdout, "%c", texto[i++]);
		fflush(stdout);
		if (texto[i] != '\n' && texto[i] != '\t')
            SLEEP(milisecs);
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


/* Mostra o primeiro menu do programa.*/
int menu_1(void)
{
    printf("\n\n           Menu Inicial");
    line(34);
    printf("\n    1 - Entrar como Cliente,");
    printf("\n    2 - Entrar como Administrador,");
    printf("\n    0 - Sair do programa.");
    printf("\n\n Sua escolha > ");
    return get_int();
}


char menu_2()
{
    printf("\n Escolha uma dessas opções:");
    printf("\n    a - Consultar modelos de uma marca.");
    printf("\n    b - Comprar modelo de carro de uma marca.");
    printf("\n    q - Voltar ao menu inicial.");
	printf("\n Sua escolha > ");

	fflush(stdin);
	char opt;
	scanf(" %c", &opt);
	cleanbuf();

	return opt;
}
