#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"

/* Limpa as estruturas dinamicas criadas aquí e ficheiros abertos. */
int fcloseall(void);
void freeDom(void);

/* Raíz da árvore binária, variável global. */
btree *root = NULL;


int main(int argv, char *argc[])
{setlocale(LC_ALL, "Portuguese");
atexit(freeDom);
    /** Teste */
    int vetor[13] = {1, 2, 5, 4, 3, 6, 5, 8,-1, 4, 9, 0, -4};
    insertInTree(&root, 3);

    for (int i = 0 ; i < 13 ; ++i)
        insertInTree(&root, vetor[i]);

    char tipo;

    printf("\n De que forma que mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha: ");
    scanf(" %c", &tipo);

    printTree(root, tipo);
    /** Teste */

    freeTree(&root);
    return 0;
}


void freeDom(void)
{
    if (root != NULL)
        freeTree(&root);  // Limpa root caso não for limpado antes
    fcloseall();    // Fecha todos os ficheiros abertos
    printf("\n Saindo da execução.\n");
}
