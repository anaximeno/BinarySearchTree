/** PROJETO DE AED: Sistema de uma loja de carros, usando árvores binárias de pesquisa.

* CURSO: Engenharia Informática e de Computadores, 1º ano, 2º semestre

* DATA: junho de 2021


 *                                  *
** ALGORÍTIMOS E ESTRUTURA DE DADOS **
 *                                  *


* PROJECTO: TIPO: Projeto final de Cadeira



* DISCENTES:

    * Anaxímeno Brito
    * Ângelo Carvalho
    * Márcia Andrade



* PROFESSOR: José Olavo da Paz

* OBS: Recomendamos o uso de Sistemas Operativos baseados em unix (linux, mac os, freebsd, etc),
para a utilização do programa pois, permitem uma melhor experiência gráfica devido a maior compatibilidade com
caracteres UTF-8, porem, foi-se feito o possível para que o programa funcione de maneira satisfatória no Windows SO.

**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "common.h"
#include "linkedlist.h"
#include "forest.h"
#include "treeprinter.h"

#define SENHA_ADMIN "1234"
#define MAX_TRIES 3


/* Estrutura loja de carros que guarda a raíz das árvores, variável global. */
STORE car_store = {
    .nome="AMEXUS MOTORS",
    .total_marcas=0,
    .total_carros=0,
    .root=NULL
};


/* Variável global que determina o tipo de usuário. */
char *USER_TYPE = "Undefined";

/* Chama a secção de administrador. */
void adminSection(STORE *store);
/* Chama a secção de cliente. */
void clientSection(STORE *store);


int main(int argv, char *argc[])
{
    atexit(freedom);
    setlocale(LC_ALL, "Portuguese");

    char output[NOMEMAX*4];

    /* Carregando o sistema com algumas marcas, para testes */
    char *marcas_teste[] = {"Mercedes", "Toyota", "Renault", "Chevrolet", "Suzuki",
                            "Audi", "Abarth", "Bentley", "Citroen", "Ford",
                            "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"};

    for (int i = 0 ; i < 15 ; ++i)
        insertBrand(marcas_teste[i], &car_store, false);

    chargeBrandFromFile("Mercedes.txt", &car_store);

    clearScreen(false);
    sprintf(output, "\n\t Oi, Seja Bem Vindo(a) a %s Store!", car_store.nome);
    animate(output, 50);
    while (true)
    {
        switch (menu_1())
        {
        case 1:  // Cliente
            USER_TYPE = "Cliente";

            clientSection(&car_store);

            break;
        case 2:  // Admin
            USER_TYPE = "Administrador";
            clearScreen(false);

            adminSection(&car_store);
            break;
        case 0:  // Sair
            goto out;
        default:
            printf("\n Opção desconhecida!");
            cleanbuf();
            enterpoint(false);
        }
    }

out:
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
    sprintf(output, "\n  %s             %s             %s",
                                        car_store.nome, __DATE__, USER_TYPE);
    printf(output);
    line(strlen(output)-1);
    //printf("\n Total Marcas: %d\n Total Carros: %d\n", car_store.total_marcas,
    //                                                car_store.total_carros);
}


void clientSection(STORE *store)
{
    char nome_marca[NOMEMAX];
    b_tree **marca;
    bool loop = true;
    animate("\n Entrando na secção Cliente", 50);
    animate("...", 650);

    while (loop) {
        clearScreen(true);
        listBrands(store);

        switch(menu_2())
        {
        case 'a': // Consultar modelos de uma marca
            clearScreen(true);
            listBrands(store);

            printf("\n Nome da marca > ");
            scanf("%s", nome_marca);
            cleanbuf();
            marca = searchBrand(nome_marca, &store->root);
            clearScreen(true);

            if (*marca != NULL) {
                if ((*marca)->brand.models == NULL) {
                    printf("\n A marca '%s' tem 0 modelos.", nome_marca);
                } else {
                    printf("\n Modelos da marca %s :", nome_marca);
                    listModels((*marca)->brand.models);
                }
            } else {
                printf("\n Marca '%s' não foi encontrada na base de dados!", nome_marca);
            }

            enterpoint(true);
            break;
        case 'b': // comprar modelo de Carro de uma marca

            enterpoint(true);
            break;
        case 'q':
            loop = false;
            continue;
        default:
            printf("\n Opção desconhecida!");
            enterpoint(true);
            fflush(stdin);
        }

    }

    clearScreen(false);
}


void adminSection(STORE *store)
{
    char senha[9];
    char tipo, *m;
    int tentativas = 0;


    putchar('\n');
    while (tentativas < MAX_TRIES) {
        tentativas++;
        printf("\n Digite a senha de Administrador : ");
        scanf(" %s", senha);
        fflush(stdin);

        if (strcmp(senha, SENHA_ADMIN) != 0) {
            clearScreen(false);
            printf("\n Senha Errada! Restam mais %d tentativas!", MAX_TRIES-tentativas);
            if (tentativas == MAX_TRIES)
                exit(0);  // Sai da execução
        } else {
            animate("\n Senha Correta, entrando na secção Administrador", 50);
            animate("...", 650);
            clearScreen(true);
            cleanbuf();
            break;  // Sai do loop e continua o programa
        }
    }

    /* Teste 1.1) - Mostra as marcas */
    printf("\n\n De que forma mostrar a árvore? (a - em ordem, b - pre ordem, c - pos ordem)");
    printf("\n Sua escolha > "); scanf(" %c", &tipo);
    setbuf(stdin, NULL);

    printTree(store->root, tipo, "Marcas");

    /* Teste 2 - carregamento de um arquivo de texto */
    printf("\n TESTE 2) Carregando marcas de arquivos para a árvore:\n");
    chargeBrandFromFile("Ford.txt", store);
    chargeBrandFromFile("Toyota.txt", store);

    /* Teste 2.0.1 - testa a abertura de um arquivo nao existente. */
    chargeBrandFromFile("Popeye.xtx", store);
    enterpoint(true);

    /* Teste 2.1) Mostra modelos de marcas */
    printf("\n TESTE 2.1) Modelos das marcas que foram carregadas:\n");
    printf("\n  Modelos da marca Toyota: ");
    printModels((*searchBrand("Toyota", &store->root))->brand.models);
    printf("\n  Modelos da marca Mercedes: ");
    printModels((*searchBrand("Mercedes", &store->root))->brand.models);
    printf("\n  Modelos da marca Ford: ");
    printModels((*searchBrand("Ford", &store->root))->brand.models);
    enterpoint(true);

    m = "Mercedes";
    printf("\n TESTE 3) A Eliminar a marca '%s' da árvore\n", m);
    enterpoint(true);

    removeBrand(&store->root, m);
    printTree(store->root, tipo, "Marcas, sem Mercedes");

    clearScreen(false);
}
