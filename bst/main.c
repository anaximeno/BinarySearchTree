#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"



void freeDom(void);

/* Raíz da árvore binária, variável global. */
btree *root = NULL;


#ifdef linux
    #define CLEAR "clear"
#endif // linux

#ifdef _WIN32
    #define CLEAR "cls"
#endif // _WIN32



int main(int argv, char *argc[])
{atexit(freeDom); setlocale(LC_ALL, "Portuguese");

    /** Teste **/

    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chivrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    char tipo;

    for (int i = 0 ; i < 15 ; ++i)
        insertNewMarca(marcas_teste[i], &root);

    system(CLEAR);
    printf("\n Data : %s\n", __DATE__);
    printf("\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha : ");
    scanf(" %c", &tipo);
    setbuf(stdin, NULL);
    printTree(root, tipo);

    printf("\n Clique enter para sair...");
    getchar();
    /** Teste **/

    freeTree(&root);
    return 0;
}


void freeDom(void)
{
    system(CLEAR);
    printf("\n Limpando a memória...");

    if (root != NULL)
        freeTree(&root);  // Limpa root caso não for limpado antes

    printf(" Saindo da execução.\n Obrigado por usar o programa!\n\n");
}
