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
{   atexit(freeDom); setlocale(LC_ALL, "Portuguese");

    printf("\n Data : %s\n\n", __DATE__);

    /** Testes **/

    /* Teste 1 - inserção de marcas */
    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chivrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    for (int i = 0 ; i < 15 ; ++i)
        insertNewMarca(marcas_teste[i], &root);


    /* Teste 2 - carregamento de um arquivo de texto
    chargeFile("Ford.txt", &root);
    chargeFile("Mercedes.txt", &root);
    chargeFile("Toyota.txt", &root);
    */
    // system(CLEAR);

    /* Teste 3 - Impressão da árvore na tela */
    printf("\n\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha : ");
    char tipo;
    scanf(" %c", &tipo);
    setbuf(stdin, NULL);
    printTree(root, tipo);

    printf("\n Clique enter para sair...");
    getchar();

    /** Testes **/

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
