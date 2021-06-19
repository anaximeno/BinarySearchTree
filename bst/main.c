#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "common.h"
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"

#define SENHA "1234"

/* Estrutura loja de carros que guarda a raíz das árvores, variável global. */
STORE car_store = {
    .nome="AMEXUS MOTORS",
    .total_marcas=0,
    .total_carros=0,
    .root=NULL
};


int main(int argv, char *argc[])
{
    atexit(freedom);
    setlocale(LC_ALL, "Portuguese");

    clearScreen();
    animate("\n \t\t Seja Bem Vindo(a) ao programa.", 50);
    printf("\n\n\n Digite a senha : ");
    char s[9];
    scanf(" %s", s);


    if (!strcmp(s, SENHA)) {
        animate("\n Senha Correta, entrando no sistema.", 50);
        clearScreen();
    } else {
        printf("\n Senha errada!");
        exit(0);
    }

    /** Testes **/
    char tipo;

    /* Teste 1 - inserção de marcas */
    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chevrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    for (int i = 0 ; i < 15 ; ++i)
        insertBrand(marcas_teste[i], &car_store);


    /* Teste 1.1) - Mostra as marcas */

    printf("\n\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha : "); scanf(" %c", &tipo);
    setbuf(stdin, NULL);

    printTree(car_store.root, tipo, "Marcas");

    /* Teste 2 - carregamento de um arquivo de texto */
    printf("\n TESTE 2) Carregando marcas de arquivos para a árvore:\n");
    chargeBrandFromFile("Ford.txt", &car_store);
    chargeBrandFromFile("Mercedes.txt", &car_store);
    chargeBrandFromFile("Toyota.txt", &car_store);

    /* Teste 2.0.1 - testa a abertura de um arquivo nao existente. */
    chargeBrandFromFile("Popeye.xtx", &car_store);
    enterpoint();

    /* Teste 2.1) Mostra modelos de marcas */
    printf("\n TESTE 2.1) Modelos das marcas que foram carregadas:\n");
    printf("\n  Modelos da marca Toyota: ");
    mostra_modelos((*searchBrand("Toyota", &car_store.root))->brand.models);
    printf("\n  Modelos da marca Mercedes: ");
    mostra_modelos((*searchBrand("Mercedes", &car_store.root))->brand.models);
    printf("\n  Modelos da marca Ford: ");
    mostra_modelos((*searchBrand("Ford", &car_store.root))->brand.models);
    enterpoint();

    /* Teste 3) Tentando remover uma marca! */
    char *m = "Mercedes";
    printf("\n TESTE 3) Eliminar a marca '%s' da árvore\n", m);
    enterpoint();
    removeBrand(&car_store.root, m);
    printTree(car_store.root, tipo, "Marcas, sem Mercedes");
    /** Testes **/

    return 0;
}


void freedom(void)
{
    if (car_store.root != NULL) {
        animate("\n Limpando a memória", 30);
        animate("...", 650);

        freetree(&car_store.root);  // Limpa root caso não for limpado antes

        animate(" A memória foi limpa!", 30);
    }

    animate("\n Saindo da execução, obrigado por usar o programa!\n\n", 30);
}


void header(void)
{
    static char output[NOMEMAX*4];
    sprintf(output, "\n  %s             %s             Administrador",
                                                car_store.nome, __DATE__);
    printf(output);
    printf("\n ");
    for (int i = 0 ; i < strlen(output)-1 ; ++i)
        printf("=");
    printf("\n");
    //printf("\n Total Marcas: %d\n Total Carros: %d\n", car_store.total_marcas,
    //                                                car_store.total_carros);
}
