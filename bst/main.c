#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "common.h"
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"



/* Estrutura loja de carros que guarda a raíz das árvores, variável global. */
STORE car_store = {
    .nome="Inditerminado",  /// TODO: pui nome di loja
    .total_marcas=0,
    .total_carros=0,
    .root=NULL
};


void freedom(void);


int main(int argv, char *argc[])
{
    atexit(freedom); setlocale(LC_ALL, "Portuguese");
    printf("\n Data : %s\n\n", __DATE__);

    /** Testes **/
    char tipo;

    /* Teste 1 - inserção de marcas */
    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chivrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    for (int i = 0 ; i < 15 ; ++i)
        insert_brand(marcas_teste[i], &car_store.root);


    /* Teste 2 - carregamento de um arquivo de texto
    charge_file("Ford.txt", &car_store.root);
    charge_file("Mercedes.txt", &car_store.root);
    charge_file("Toyota.txt", &car_store.root);
    */

    /* Teste 2.0.1 - testa a abertura de um arquivo nao existente. */
    // charge_file("Popeye.xtx", &car_store.root);

    /* Teste 3 - Impressão da árvore na tela */
    printf("\n\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha : "); scanf(" %c", &tipo);
    setbuf(stdin, NULL);

    /* Teste 2.1) - Mostra o modelo Toyota inserido acima
    b_tree *brand = search_brand("Toyota", car_store.root);
    print_tree(brand->marca.modelos, tipo, "Modelos");
    */

    /* Teste 1.1) - Mostra as marcas */
    print_tree(car_store.root, tipo, "Marcas");



    enterpoint();

    /** Testes **/
    return 0;
}


void freedom(void)
{
    animate("\n Limpando a memória", 40000);
    animate("....", 900000);

    if (car_store.root != NULL)
        freetree(&car_store.root);  // Limpa root caso não for limpado antes

    animate(" A memória foi limpa!", 40000);
    animate("\n Saindo da execução, obrigado por usar o programa.\n\n", 45500);
}
