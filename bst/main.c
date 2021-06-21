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
    .total_modelos=0,
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
            USER_TYPE = "Undefinded";
            break;
        case 2:  // Admin
            USER_TYPE = "Administrador";
            clearScreen(false);

            adminSection(&car_store);
            USER_TYPE = "Undefinded";
            break;
        case 0:  // Sair
            goto out;
        default:
            printf("\n Opção desconhecida!");
            freebuffer();
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
    char nome_marca[NOMEMAX],
        nome_modelo[NOMEMAX],
        output[NOMEMAX*4];

    b_tree **marca = NULL;

    model_llist **modelo = NULL;

    bool loop = true;

    int media;

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
            freebuffer();

            marca = searchBrand(nome_marca, &store->root);

            clearScreen(true);
            if (marca != NULL)
            {

                if ((*marca)->brand.models == NULL)
                {
                    printf("\n A marca '%s' tem 0 modelos.", nome_marca);
                }
                else
                {
                    printf("\n Modelos da marca %s :", nome_marca);
                    listModels((*marca)->brand.models);
                    media = (int) (*marca)->brand.valor_total / (*marca)->brand.total_carros;
                    printf("\n\n Modelos: %d ______ Carros: %d ______ Media por Carro: %d$00\n",
                        (*marca)->brand.qtdade_modelos, (*marca)->brand.total_carros, media);
                }

            }
            else
            {
                printf("\n Marca '%s' não foi encontrada na base de dados!", nome_marca);
            }

            enterpoint(true);
            break;
        case 'b': // comprar modelo de Carro de uma marca
            clearScreen(true);
            listBrands(store);

            printf("\n Nome da Marca Pretendida > ");
            scanf("%s", nome_marca);
            freebuffer();

            marca = searchBrand(nome_marca, &store->root);

            if (marca != NULL)
            {
                clearScreen(true);
                if ((*marca)->brand.models != NULL)
                {
                    printf("\n Modelos da marca %s :", nome_marca);
                    listModels((*marca)->brand.models);

                    printf("\n\n Nome do Modelo a Comprar > ");
                    scanf("%s", nome_modelo);
                    freebuffer();

                    modelo = searchModel(&(*marca)->brand.models, nome_modelo);

                    if (modelo != NULL)
                    {
                        if ((*modelo)->qtdade > 0)
                        {
                            store->total_modelos--;
                            (*marca)->brand.total_carros--;
                            (*marca)->brand.valor_total -= (*modelo)->preco;
                            (*modelo)->qtdade--;

                            sprintf(output, "\n Parabéns acabaste de comprar o carro '%s %s' por %d$00!",
                                nome_marca, nome_modelo, (*modelo)->preco);

                            animate(output, 40);
                        }
                        else
                        {
                            printf("\n Infelizmente não há mais '%s %s' a venda!",
                                                        nome_marca, nome_modelo);
                        }
                    }
                    else
                    {
                        printf("\n Modelo '%s' não foi encontrado na base de dados!",
                                                                     nome_modelo);
                    }
                }
                else
                {
                    printf("\n A marca %s não tem nenhum modelo a venda!", nome_marca);
                }
            }
            else
            {
                printf("\n Marca '%s' não foi encontrada na base de dados!",
                                                            nome_marca);
            }

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
    bool loop = true;

    char senha[9],
         nome_modelo[NOMEMAX],
         nome_marca[NOMEMAX],
         escolha,
         output[NOMEMAX*4];

    int tentativas = 0,
        tipo, opt, ano, preco, qtdade;

    b_tree **marca = NULL;

    model_llist **modelo = NULL;

    putchar('\n');
    while (tentativas < MAX_TRIES) {
        tentativas++;
        printf("\n Digite a senha de Administrador : ");
        scanf(" %s", senha);
        freebuffer();

        if (strcmp(senha, SENHA_ADMIN) != 0) {
            clearScreen(false);
            printf("\n Senha Errada! Restam mais %d tentativas!", MAX_TRIES-tentativas);
            if (tentativas == MAX_TRIES) {
                printf("\n Vai ser redirecionado para o menu inicial!");
                enterpoint(true);
                goto end;  // Volta para o menu anterior
            }
        } else {
            animate("\n Senha Correta, entrando na secção Administrador", 50);
            animate("...", 650);
            clearScreen(true);
            break;  // Sai do loop e continua o programa
        }
    }

    while (loop)
    {
       switch(menu_3())
        {
        case 'a':  // Ver arvore de marcas
            clearScreen(true);

            printf("\n De que forma mostrar a arvore? (1 - em ordem, 2 - pre ordem, 3 - pos ordem)");
            printf("\n Sua escolha > ");
            tipo = get_int();

            clearScreen(true);
            printTree(*store, tipo, "Marcas");
            enterpoint(true);
            break;
        case 'b': // Ver modelos de uma marca
            clearScreen(true);
            printf("\n Nome da marca > ");
            scanf("%s", nome_marca),
            freebuffer();

            marca = searchBrand(nome_marca, &store->root);

            if(marca != NULL)
            {
                clearScreen(true);
                printf("\n Modelos da marca %s : ", nome_marca);
                printModels((*marca)->brand.models);
            }
            else
            {
                clearScreen(true);
                printf("\n Marca: '%s' não foi encontrada na base de dados!", nome_marca);
            }

            enterpoint(true);
            break;
        case 'c':  // Inserir Marca ou Modelo na store
            clearScreen(true);

            printf("\n Queres inserir uma Marca (1) ou um Modelo (2) ?");
            printf("\n Sua opcao > ");
            opt = get_int();
            switch(opt)
            {
            case 1:  // Inserir Marca
                clearScreen(true);
                printf("\n Nome da Marca : ");
                scanf("%s", nome_marca);
                freebuffer();
insert_marca:
                insertBrand(nome_marca, store, true);
                break;
            case 2: // Inserir Modelo
                clearScreen(true);
                printf("\n Nome da Marca a inserir Modelo : ");
                scanf("%s", nome_marca);
                freebuffer();

                marca = searchBrand(nome_marca, &store->root);

                if (marca != NULL)
                {
                    printf("\n Nome do modelo : ");
                    scanf("%s", nome_modelo);
                    freebuffer();

                    modelo = searchModel(&(*marca)->brand.models, nome_modelo);

                    if (modelo == NULL)
                    {
                        printf("\n Ano : ");
                        ano = get_int();

                        printf("\n Preco : ");
                        preco = get_int();

                        printf("\n Quantidade : ");
                        qtdade = get_int();

                        if (_insert_model_in_list(&(*marca)->brand.models,
                                            nome_modelo, ano, preco, qtdade))
                        {
                            (*marca)->brand.total_carros += qtdade;
                            (*marca)->brand.valor_total += preco * qtdade;
                            (*marca)->brand.qtdade_modelos++;
                            store->total_modelos++;

                            sprintf(output, "\n Modelo '%s' foi inserido na Marca '%s'!\n",
                                                            nome_modelo, nome_marca);
                            animate(output, 40);
                        }
                        else
                        {
                            printf("\n Não foi possível alocar memória para inserir a marca '%s'\n",
                                                                nome_marca);
                        }

                    }
                    else
                    {
                        printf("\n Modelo: '%s' já se encontra introduzido!", nome_modelo);
                        printf("\n Quer adicionar mais desse modelo, Sim (s) ou Nao (n) ? > ");
                        scanf(" %c", &escolha);
                        freebuffer();
                        if (escolha == 's' || escolha == 'S')
                        {
                            printf("\n Quantos mais adicionar ?");
                            printf("\n Quantidade : ");
                            qtdade = get_int();

                            (*modelo)->qtdade += qtdade;
                            (*marca)->brand.total_carros += qtdade;
                            (*marca)->brand.valor_total += (*modelo)->preco * qtdade;
                            break;
                        }
                        else
                        {
                            printf("\n Cancelando a introducao de modelo e voltando ao menu anterior!");
                        }
                    }
                }
                else
                {
                    clearScreen(true);
                    printf("\n Marca: '%s' não foi encontrada na base e dados!", nome_marca);
                    printf("\n Inserir, Sim (s) ou Nao (n)? > ");
                    scanf(" %c", &escolha);
                    freebuffer();

                    if (escolha == 's' || escolha == 'n')
                        goto insert_marca;
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
            opt = get_int();

            switch(opt)
            {
            case 1:  // Remover Marca
                printf("\n Nome da marca a remover : ");
                scanf("%s", nome_marca);
                freebuffer();

                marca = searchBrand(nome_marca, &store->root);

                if (marca != NULL)
                {
                    clearScreen(true);
                    sprintf(output, "\n A remover a marca %s", nome_marca);
                    animate(output, 40);
                    animate("...", 650);

                    removeBinaryNode(marca);

                    animate("\n A marca foi removida!", 40);
                }
                else
                {
                    clearScreen(true);
                    printf("\n Marca: '%s' não foi encontrada na base de dados!", nome_marca);
                }
                break;
            case 2:  // Remover Modelo
                printf("\n Nome da Marca do Modelo : ");
                scanf("%s", nome_marca);
                freebuffer();

                if ((marca = searchBrand(nome_marca, &store->root)) != NULL)
                {
                    printf("\n Nome do modelo a remover : ");
                    scanf("%s", nome_modelo);
                    freebuffer();

                    modelo = searchModel(&(*marca)->brand.models, nome_modelo);

                    if(modelo != NULL)
                    {
                        clearScreen(true);
                        sprintf(output, "\n A remover a modelo %s da marca %s", nome_modelo, nome_marca);
                        animate(output, 40);
                        animate("...", 650);

                        removeModel(&(*marca)->brand.models, nome_modelo);

                        animate("\n O modelo foi removido!", 40);
                    }
                    else
                    {
                        clearScreen(true);
                        printf("\n Modelo: '%s' não foi encontrada na base de dados!", nome_modelo);
                    }
                }
                else
                {
                    clearScreen(true);
                    printf("\n Marca: '%s' não foi encontrada na base de dados!", nome_marca);
                }
                break;
            default:
                printf("\n Opção desconhecida, escolha uma das opcoes indicadas!");
            }
            enterpoint(true);
            break;
        case 'q':  // Sair para o menu anterior
            goto end;
        default:
            printf("\n Opção desconhecida!");
            enterpoint(true);
            fflush(stdin);
        }
    }

end:
    clearScreen(false);
}
