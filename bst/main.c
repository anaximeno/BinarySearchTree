/**                Sistema de uma loja de carros, usando árvores binárias de pesquisa e listas ligadas.
@CURSO: Engenharia Informática e de Computadores, 1º ano, 2º semestre
@DATA: junho de 2021

        *                                  *
      **  ALGORÍTIMOS E ESTRUTURA DE DADOS  **
        *                                  *

@DISCENTES:
    - Anaxímeno Brito
    - Ângelo Carvalho
    - Márcia Andrade
@PROFESSOR: José Olavo da Paz
@OBS: Recomendamos o uso de Sistemas Operativos baseados em unix (linux, mac os, freebsd, etc),
para a utilização do programa pois, permitem uma melhor experiência gráfica devido a maior compatibilidade com
caracteres UTF-8, porem, foi-se feito o possível para que o programa funcione de maneira satisfatória no Windows OS.
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "include/common.h"
#include "include/linkedlist.h"
#include "include/forest.h"
#include "include/treeprinter.h"

#define ADMIN_PASSWORD "1234"
#define MAX_ADMIN_ENTRY_TRIES 3

// Chama a secção de administrador.
void adminSection(void);
// Chama a secção de cliente.
void clientSection(void);

/* Variável global que determina o tipo de usuário. */
char *userType = "indefinido";


/* Estrutura loja de carros que guarda a raíz das árvores, variável global. */
STORE carStore = {
    .nome="AMEXUS MOTORS",
    .totalMarcas=0,
    .totalModels=0,
    .root=NULL
};


// Liberta a memória utilizada pela árvore binária
void freeMemory(void)
{
    if (carStore.root != NULL)
    {
        animateOutput("\n Limpando a memoria", 30);
        animateOutput("...", 650);
        // Limpa root caso não for limpado antes
        freeTree(&carStore.root);
        animateOutput(" A memoria foi limpa!", 30);
    }
    animateOutput("\n Saindo da execucao, obrigado por usar o programa!\n\n", 30);
}


// Chama e executa as intruções do primeiro menu
static int runner()
{
    setlocale(LC_ALL, "Portuguese");
    static bool stop = false;
    int tries = 0;
    char senha[NORMAL_STRING_SIZE];
    switch (menu_1())
    {
        case 0:
            clearScreen(false);
            stop = true;
            break;
        case 1:
            animateOutput("\n\t\tEntrando na seccao Cliente", 50);
            animateOutput("...", 550);
            userType = "Cliente";
            clientSection();
            break;
        case 2:
            clearScreen(false);
            putchar('\n');
            while (tries < MAX_ADMIN_ENTRY_TRIES)
            {
                tries++;
                printf("\n Digite a senha de Administrador : ");
                scanf(" %s", senha);
                freeBuffer();

                if (strcmp(senha, ADMIN_PASSWORD) != 0) {
                    clearScreen(false);
                    printf("\n Senha Errada! Restam mais '%d' tentativas!", MAX_ADMIN_ENTRY_TRIES-tries);
                    if (tries == MAX_ADMIN_ENTRY_TRIES) {
                        printf("\n Vai ser redirecionado para o menu inicial");
                        animateOutput("...", 550);
                        stop = true;
                        break;
                    }
                } else {
                    userType = "Administrador";
                    animateOutput("\n Senha Correta, entrando na seccao Administrador", 50);
                    animateOutput("...", 550);
                    clearScreen(true);
                    adminSection();
                    break;
                }
            }
            break;
        default:
            printf("\n Opcao desconhecida!");
            enterpoint(false);
    }
    userType = "indefinido";
    if (!stop)
        return runner();
    else
        return 0;
}


int main(int argv, char *argc[])
{
    char output[BIG_STRING_SIZE];
    setlocale(LC_ALL, "Portuguese");
    atexit(freeMemory);

    sprintf(output, "\n\t Oi, Seja Bem Vindo(a) a %s Store!", carStore.nome);

    /* Carregando o sistema com algumas marcas, para testes */
    char *marcasTeste[] = {
        "Mercedes", "Toyota", "Renault", "Chevrolet", "Suzuki",
        "Audi", "Abarth", "Bentley", "Citroen", "Ford",
        "Volvo", "Volkswagen", "Tesla", "Seat", "Porsche"
    };

    for (int i = 0 ; i < 15 ; ++i)
        insertBrand(marcasTeste[i], &carStore, false);

    clearScreen(false);
    animateOutput(output, 30);
    animateOutput("\n\t\t Entrando no sistema", 30);
    animateOutput("....", 550);
    clearScreen(false);

    return runner();
}


void header(void)
{
    char output[BIG_STRING_SIZE];
    sprintf(output, "\n  %s             %s             %s", carStore.nome, __DATE__, userType);
    puts(output);
    drawLine(ROOT_BRANCH, strlen(output)-2);
}


void clientSection(void)
{
    char nomeDaMarca[NORMAL_STRING_SIZE], nomeDoModelo[NORMAL_STRING_SIZE], output[BIG_STRING_SIZE];
    b_tree **nodeMarca = NULL;
    b_tree *brand = NULL;
    struct _linkedModel **nodeModelo = NULL;
    struct _linkedModel *model = NULL;
    bool loop = true;
    int media = 0;

    while (loop == true)
    {
        clearScreen(true);
        listBrands(&carStore);
        switch(menu_2())
        {
        case 'a': /* Consultar modelos de uma marca */
            clearScreen(true);
            listBrands(&carStore);
            printf("\n Nome da marca a consultar > ");
            scanf("%s", nomeDaMarca);
            freeBuffer();
            clearScreen(true);

            nodeMarca = searchBrand(nomeDaMarca, &carStore.root);

            if (nodeMarca == NULL) {
                printf("\n Marca '%s' nao foi encontrada na base de dados!", nomeDaMarca);
                enterpoint(true);
                break;
            } else if ((* nodeMarca)->models == NULL) {
                printf("\n A marca '%s' nao tem nenhum modelo disponivel!", nomeDaMarca);
                enterpoint(true);
                break;
            }

            brand = *nodeMarca;
            media = brand->totalCarros > 0 ? brand->valorTotal / brand->totalCarros : 0;

            printf("\n Modelos da marca %s :", nomeDaMarca);
            listModels(brand->models);
            // TODO: Criar uma opção de ver os dados dos modelos separadamente 
            printf("\n\n Modelos: %d ______ Total Carros: %d ______ Media por Carro: %d$00\n",
                brand->qtdadeModelos, brand->totalCarros, media);

            enterpoint(true);
            break;
        case 'b': /* comprar modelo de Carro de uma marca */
            clearScreen(true);
            listBrands(&carStore);

            printf("\n Nome da Marca Pretendida > ");
            scanf("%s", nomeDaMarca);
            freeBuffer();

            nodeMarca = searchBrand(nomeDaMarca, &carStore.root);

            if (nodeMarca == NULL) {
                printf("\n Marca '%s' nao foi encontrada na base de dados!", nomeDaMarca);
                enterpoint(true);
                break;
            } else if ((* nodeMarca)->models == NULL) {
                printf("\n A marca '%s' nao tem nenhum modelo disponivel!", nomeDaMarca);
                enterpoint(true);
                break;
            }

            brand = *nodeMarca;

            printf("\n Modelos da marca %s :", nomeDaMarca);
            listModels(brand->models);
            printf("\n\n Nome do Modelo a Comprar > ");
            scanf("%s", nomeDoModelo);
            freeBuffer();

            nodeModelo = searchModel(&brand->models, nomeDoModelo);

            if (nodeModelo == NULL) {
                printf("\n O modelo '%s' nao foi encontrado na base de dados!", nomeDoModelo);
                enterpoint(true);
                break;
            } else if ((* nodeModelo)->qtdade <= 0) {
                printf("\n Nao ha stock do modelo '%s %s' na store!", nomeDaMarca, nomeDoModelo);
                enterpoint(true);
                break;
            }

            model = *nodeModelo;

            model->qtdade -= 1;
            brand->totalCarros -= 1;
            brand->valorTotal -= model->preco;
            carStore.totalModels -= 1;

            sprintf(output, "\n Parabens acabaste de comprar o carro '%s %s' por %d$00!",
                nomeDaMarca, nomeDoModelo, model->preco);

            animateOutput(output, 35);
            enterpoint(true);
            break;
        case 'q':
            animateOutput("\n Saindo da seccao Cliente", 35);
            animateOutput("...", 550);
            loop = false;
            continue;
        default:
            printf("\n Opcao desconhecida!");
            enterpoint(true);
            fflush(stdin);
        }
    } clearScreen(false);
}


void adminSection()
{
    bool loop = true;
    char escolha,
         nomeDoModelo[NORMAL_STRING_SIZE],
         nomeDaMarca[NORMAL_STRING_SIZE],
         output[BIG_STRING_SIZE],
         nomeFicheiro[NORMAL_STRING_SIZE];
    int tipo, ano, preco, qtdade;
    b_tree **nodeMarca = NULL;
    b_tree *brand = NULL;
    struct _linkedModel **nodeModelo = NULL;
    struct _linkedModel *model = NULL;


    while (loop == true)
    {
       switch(menu_3())
        {
        case 'a':  // Ver arvore de marcas
            clearScreen(true);
            printf("\n De que forma mostrar a arvore? (1 - em ordem, 2 - pre ordem, 3 - pos ordem)");
            printf("\n Sua escolha > ");
            tipo = get_int();
            clearScreen(true);
            printTree(carStore, tipo, "Marcas");
            enterpoint(true);
            break;
        case 'b': // Ver modelos de uma marca
            clearScreen(true);
            printf("\n Nome da marca > ");
            scanf("%s", nomeDaMarca),
            freeBuffer();

            nodeMarca = searchBrand(nomeDaMarca, &carStore.root);

            if (nodeMarca == NULL) {
                clearScreen(true);
                printf("\n Marca: '%s' nao foi encontrada na base de dados!", nomeDaMarca);
                enterpoint(true);
                break;
            }
            brand = *nodeMarca;
            clearScreen(true);
            printf("\n Modelos da marca %s : ", nomeDaMarca);
            printModels(brand->models);
            enterpoint(true);
            break;
        case 'c':  // Inserir Marca ou Modelo na carStore
            clearScreen(true);
            printf("\n Queres inserir uma Marca (1) ou um Modelo (2) ?");
            printf("\n Sua opcao > ");
            switch(get_int())
            {
            case 1:  // Inserir Marca
                clearScreen(true);
                printf("\n Nome da Marca : ");
                scanf("%s", nomeDaMarca);
                freeBuffer();
$insert_marca:
                insertBrand(nomeDaMarca, &carStore, true);
                break;
            case 2: // Inserir Modelo
                clearScreen(true);
                printf("\n Nome da Marca a inserir Modelo : ");
                scanf("%s", nomeDaMarca);
                freeBuffer();

                nodeMarca = searchBrand(nomeDaMarca, &carStore.root);

                if (nodeMarca == NULL) {
                    clearScreen(true);
                    printf("\n Marca: '%s' nao foi encontrada na base e dados!", nomeDaMarca);
                    printf("\n Inserir, Sim (s) ou Nao (n)? > ");
                    scanf(" %c", &escolha);
                    freeBuffer();

                    if (escolha == 's' || escolha == 'S')
                        goto $insert_marca;
                    else {
                        break;
                    }
                }

                brand = *nodeMarca;

                printf("\n Nome do modelo : ");
                scanf("%s", nomeDoModelo);
                freeBuffer();

                nodeModelo = searchModel(&brand->models, nomeDoModelo);

                if (nodeModelo == NULL) {
                    printf("\n Ano : ");
                    ano = get_int();
                    printf("\n Preco : ");
                    preco = get_int();
                    printf("\n Quantidade : ");
                    qtdade = get_int();

                    if (_insert_model_in_list(&brand->models, nomeDoModelo, ano, preco, qtdade)) {
                        brand->totalCarros += qtdade;
                        brand->valorTotal += preco * qtdade;
                        brand->qtdadeModelos++;
                        carStore.totalModels++;

                        sprintf(output, "\n Modelo '%s' foi inserido na Marca '%s'!\n", nomeDoModelo, nomeDaMarca);
                        animateOutput(output, 40);
                    } else {
                        printf("\n Nao foi possivel alocar memoria para inserir a marca '%s'\n", nomeDaMarca);
                    }
                } else {
                    model = *nodeModelo;
                    printf("\n Modelo: '%s' ja se encontra introduzido!", nomeDoModelo);
                    printf("\n Quer adicionar mais desse modelo, Sim (s) ou Nao (n) ? > ");
                    scanf(" %c", &escolha);
                    freeBuffer();
                    if (escolha == 's' || escolha == 'S')
                    {
                        printf("\n Quantos mais adicionar ?");
                        printf("\n Quantidade : ");
                        qtdade = get_int();
                        model->qtdade += qtdade;
                        brand->totalCarros += qtdade;
                        brand->valorTotal += model->preco * qtdade;
                        break;
                    } else {
                        printf("\n Cancelando a introducao de modelo e voltando ao menu anterior!");
                        animateOutput("...", 300);
                    }
                }
                break;
            default:
                printf("\n Opcao desconhecida!");
                fflush(stdin);
            }
            enterpoint(true);
            break;
        case 'd':  // Remover uma marca ou modelo
            clearScreen(true);
            printf("\n Quer remover uma Marca (1) ou Modelo (2) ? > ");
            switch(get_int())
            {
            case 1:  // Remover Marca
                printf("\n Nome da marca a remover : ");
                scanf("%s", nomeDaMarca);
                freeBuffer();

                nodeMarca = searchBrand(nomeDaMarca, &carStore.root);

                if (nodeMarca == NULL) {
                    clearScreen(true);
                    printf("\n Marca: '%s' nao foi encontrada na base de dados!", nomeDaMarca);
                    break;
                }

                clearScreen(true);
                sprintf(output, "\n A remover a marca %s", nomeDaMarca);
                animateOutput(output, 40);
                animateOutput("...", 650);

                removeBinaryNode(nodeMarca);

                animateOutput("\n A marca foi removida!", 40);
                break;
            case 2:  // Remover Modelo
                printf("\n Nome da Marca do Modelo : ");
                scanf("%s", nomeDaMarca);
                freeBuffer();

                nodeMarca = searchBrand(nomeDaMarca, &carStore.root);

                if (nodeMarca == NULL) {
                    clearScreen(true);
                    printf("\n Marca: '%s' nao foi encontrada na base de dados!", nomeDaMarca);
                    break;
                }
                printf("\n Nome do modelo a remover : ");
                scanf("%s", nomeDoModelo);
                freeBuffer();

                brand = *nodeMarca;
                nodeModelo = searchModel(&brand->models, nomeDoModelo);

                if ( nodeModelo == NULL)
                {
                    clearScreen(true);
                    printf("\n Modelo: '%s' nao foi encontrada na base de dados!", nomeDoModelo);
                    break;
                }

                clearScreen(true);
                sprintf(output, "\n A remover a modelo %s da marca %s", nomeDoModelo, nomeDaMarca);
                animateOutput(output, 30);
                animateOutput("...", 550);

                removeModel(&brand->models, nomeDoModelo);

                animateOutput("\n O modelo foi removido!", 40);
                break;
            default:
                printf("\n Opcao desconhecida, escolha uma das opcoes indicadas!");
            }
            enterpoint(true);
            break;
        case 'e': // Carregar marcas e modelos de um ficheiro
            clearScreen(true);
            printf("\n O ficheiro precisa ter a seguinte estrutura");
            printf(" nome_da_marca.txt,\n com todos os modelos e seus dados escritos dentro!\n");
            printf("\n Nome do ficheiro a Carregar : ");
            scanf("%s", nomeFicheiro);
            freeBuffer();
            chargeBrandFromFile(nomeFicheiro, &carStore);
            enterpoint(true);
            break;
        case 'f':
            clearScreen(true);
            printf("\n Nome da marca a guardar em arquivo : ");
            scanf("%s", nomeDaMarca);
            freeBuffer();

            if(saveBrandInFile(carStore, nomeDaMarca)) {
                sprintf(output, "\n Marca: '%s' foi salva como '%s.txt'", nomeDaMarca, nomeDaMarca);
                animateOutput(output, 35);
            }

            enterpoint(true);
            break;
        case 'g':
            clearScreen(true);
            printf("\n Tem certeza que quer eliminar todos os dados da loja ? Sim (s) ou Nao (n) : ");
            scanf(" %c", &escolha);
            freeBuffer();

            if (escolha == 's' || escolha == 'S') {
                animateOutput("\n A eliminar todos os dados da loja", 40);
                animateOutput("....", 550);

                freeTree(&carStore.root);

                animateOutput("\n Todas as Marcas e Modelos foram apagados!", 35);
            } else
                printf("\n Voltando ao menu anterior.");
            enterpoint(true);
            break;
        case 'q':  // Sair para o menu anterior
            animateOutput("\n Saindo da seccao Administrador", 35);
            animateOutput("...", 550);
            loop = false;
            break;
        default:
            printf("\n Opccao desconhecida!");
            enterpoint(true);
            fflush(stdin);
        }
    } clearScreen(false);
}
