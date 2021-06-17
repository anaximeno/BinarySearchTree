#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "common.h"
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"



/* Raíz da árvore binária, variável global. */
b_tree *root = NULL;

void freedom(void);


int main(int argv, char *argc[])
{   atexit(freedom); setlocale(LC_ALL, "Portuguese");

    printf("\n Data : %s\n\n", __DATE__);

    /** Testes **/

    /* Teste 1 - inserção de marcas */
    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chivrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    for (int i = 0 ; i < 15 ; ++i)
        insertNewMarca(marcas_teste[i], &root);


    /* Teste 2 - carregamento de um arquivo de texto
    charge_file("Ford.txt", &root);
    charge_file("Mercedes.txt", &root);
    charge_file("Toyota.txt", &root);
    */

    /* Teste 3 - Impressão da árvore na tela */
    printf("\n\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha : ");
    char tipo;
    scanf(" %c", &tipo);
    setbuf(stdin, NULL);

    CLEAR();
    printTree(root, tipo, "Marcas");
    enterpoint();

    /** Testes **/
    return 0;
}




void freedom(void)
{
    animate("\n Limpando a memória", 40000);
    animate("....", 900000);

    if (root != NULL)
        freetree(&root);  // Limpa root caso não for limpado antes

    animate(" A memória foi limpa.\n Saindo da execução, obrigado por usar o programa!\n\n", 40000);
}
