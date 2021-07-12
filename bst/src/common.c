#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "forest.h"
#include "common.h"
#include "treeprinter.h"

#define MAX_CLEAN_REPEAT_TIMES 32


void line(char *symbol, int times)
{
    printf(" ");
    for (int i = 0 ; i < times ; ++i)
        printf("%s", symbol);
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


void freebuffer(void)
{
	int times = 0;
	char c;

	/* Limpa o buffer, caso tiver muitas tentativas, termina a execução. */
	while ((c = getc(stdin)) != '\n' && c != EOF)
    {
		if (times++ > MAX_CLEAN_REPEAT_TIMES)
        {

			printf("\n erro: atingiu-se o limite de falha!");
			SLEEP(2000);

			exit(1);

		}
	}
}


int get_int(void)
{
	int x;

	while (!scanf(" %d", &x))
    {
		freebuffer();
		printf("\n Valor Invalido, insira um inteiro: ");
	}

    freebuffer();
	return x;
}


void animate(const char *texto, unsigned int milisecs)
{
	int i = 0;
	while (texto[i] != '\0')
    {
		fprintf(stdout, "%c", texto[i++]);
		fflush(stdout);
		if (texto[i] != '\n' && texto[i] != '\t')
            SLEEP(milisecs);
	}
}


char *getName(char *txtname)
{
	char *txt, *name;
	int i, size = 0;

    txt = txtname;
	while (*txt != '.' && *txt != '\0' && ++size && ++txt) ;

	name = (char *) calloc(size+1, sizeof(char));

	for (i = 0, txt = txtname ; txt[i] != '.' && txt[i] != '\0' ; ++i)
		name[i] = txt[i];

	name[i] = '\0';  // Adiciona o final da string

	return name;
}


/* Mostra o primeiro menu do programa.*/
int menu_1(void)
{
    printf("\n\n                            M E N U    I N I C I A L                                     \n");
    printf("          "); line(ROOT_BRANCH, 59);
    printf("\n                             1 - Entrar como Cliente                                        ");
    printf("\n\n                         2 - Entrar como Administrador                                     ");
    printf("\n\n                             0 - Sair  do  programa                                         \n");
    printf("\n");
    printf("          "); line(ROOT_BRANCH, 59);
    printf("\n                SUA ESCOLHA : ");
    int opt = get_int();;

    putchar('\n');
    return opt;
}


char menu_2(void)
{
    printf("\n Escolha uma dessas opcoes:");

    printf("\n    a - Consultar modelos de uma marca.");
    printf("\n    b - Comprar modelo de carro de uma marca.");
    printf("\n    q - Voltar ao menu inicial.");
    printf("\n");
    line(ROOT_BRANCH, 59);
	printf(" Sua escolha > ");

	fflush(stdin);
	char opt;
	scanf(" %c", &opt);
	freebuffer();

	return opt;
}


char menu_3(void)
{
    printf("\n Escolha uma dessas opcoes:");

    printf("\n   a - Ver Arvore de marcas,");
    printf("\n   b - Ver Modelos de uma Marca,");
    printf("\n   c - Inserir Marca ou Modelo,");
    printf("\n   d - Remover Marca ou Modelo,");
    printf("\n   e - Carregar Marcas e Modelos de um ficheiro,");
    printf("\n   f - Salvar marca e seus modelos num ficheiro,");
    printf("\n   g - Apagar todos os dados da loja,");
    printf("\n   q - Sair da administracao da loja.");
    printf("\n");
    line(ROOT_BRANCH, 65);
    printf(" Sua escolha > ");

    fflush(stdin);
    char opt;
    scanf(" %c", &opt);
    freebuffer();

    return opt;
}
