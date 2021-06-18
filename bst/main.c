#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "common.h"
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"

#define SENHA 1234

/* Estrutura loja de carros que guarda a raíz das árvores, variável global. */
STORE car_store = {
    .nome="Amexus Car Store",
    .total_marcas=0,
    .total_carros=0,
    .root=NULL
};


int main(int argv, char *argc[])
{
    atexit(freedom);
    setlocale(LC_ALL, "Portuguese");

    clearScreen();
    animate("\n Seja Bem Vindo!", 50000);
    /* */
    printf("\n senha : ");
    int s = get_int();

    if (s != SENHA) {
        printf("\n Senha errada!");
        exit(0);
    } else {
        animate("\n Senha Correta, entrando no sistema.", 50000);
        clearScreen();
    }

    /** Testes **/
    char tipo;

    /* Teste 1 - inserção de marcas */
    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chevrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    for (int i = 0 ; i < 15 ; ++i)
        insert_brand(marcas_teste[i], &car_store);


    /* Teste 2 - carregamento de um arquivo de texto */
    //charge_file("Ford.txt", &car_store);
    //charge_file("Mercedes.txt", &car_store);
    //charge_file("Toyota.txt", &car_store);


    /* Teste 2.0.1 - testa a abertura de um arquivo nao existente. */
    //charge_file("Popeye.xtx", &car_store.root);

    /* Teste 3 - Impressão da árvore na tela */

    printf("\n\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha : "); scanf(" %c", &tipo);
    setbuf(stdin, NULL);

    /* Teste 2.1) - Mostra o modelo Toyota inserido acima */
    //b_tree *brand = search_brand("Toyota", car_store.root);
    //if (brand != NULL)
    //    print_tree(brand->marca.modelos, tipo, "Modelos");


    /* Teste 1.1) - Mostra as marcas */
    //tipo = 'a';
    print_tree(car_store.root, tipo, "Marcas");

    /* Teste 4) Tentando remover uma marca! */
    //char *m = "Audi";
    //printf("\n Agora tentando eliminar a marca '%s'!", m);
    //fflush(stdout);
    //sleep(1);
    //remove_brand(&car_store.root, m);
    //print_tree(car_store.root, tipo, "Marcas");
    /** Testes **/

    return 0;
}


void freedom(void)
{
    if (car_store.root != NULL) {
        animate("\n Limpando a memória", 30000);
        animate("....", 700000);

        freetree(&car_store.root);  // Limpa root caso não for limpado antes

        animate(" A memória foi limpa!", 30000);
    }

    animate("\n Saindo da execução, obrigado por usar o programa!\n\n", 30500);
}


void header(void)
{
    printf("\n LOJA : %s\n DATA : %s", car_store.nome, __DATE__);
    printf("\n SECÇAO : Administrador\n");
}
