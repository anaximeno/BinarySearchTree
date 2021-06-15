/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdbool.h>

#ifndef FOREST_H
#define FOREST_H


#define R "RIGHT"
#define L "LEFT"
#define DEPTH_MULTIPLIER 2

#define NOMEMAX 32


/** Estrutura de árvore binária, com os campos:
 *    >> parent (struct _binarytree *) : estrutura pai do nó atual
 *    >> left (struct _binarytree *) : estrutura do lado esquerdo
 *    >> right (struct _binarytree *) : estrutura do lado direita
 *    >> valor (int) : guarda um valor inteiro
 *    >> level (int) : nivel do nó na árvore
 *    >> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT" 
 *    >> modelo (union struct _modelo) : estrutura que representa um modelo
 *    >> marca (union struct _marca) : estrutura que representa uma marca.
 * */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    int valor, level;
    char *position, *tipo;

    /* union foi usado para previnir a alocação de memória desnecessária. */
    union 
    {
        struct _modelo 
        {
            char nome[NOMEMAX];
            int ano, preco, qtdade;
        } modelo;
        struct _marca 
        {
            char nome[NOMEMAX];
            int qtdade_modelos, valor_total;
            /* modelos aponta para uma árvore binária contendo todos os modelos dessa marca. */
            struct _binarytree *modelos;
        } marca;
    };
} btree;


/* Ponteiro para árvore binária. */
typedef btree* broot;


/* Cria um nó da árvore binária. */
btree *createBinNode(int valor, char* position, int level, btree *parent);



/* Insere um valor na árvore binária. */
void insertInTree(broot* root, int valor);


/* Procura por um valor e retorna o nó que contém esse valor */
void searchInTree(btree* root, int valor);


/* Salva a árvore num arquivo. */
void saveTreeOnFile(btree* root, const char* filename);


/* Salva um nó binário num arquivo. */
void saveBinaryNodeOnFile(btree* node, const char* filename);


/* Elimina um valor da árvore. */
void eliminateBinaryNode(int valor, broot* root);


/* Carrega um nó binário guardado no arquivo de nome [marca].txt com os elementos:

    [nome do modelo]    [ano de lançamento]     [preço]     [quantidate] */
struct _binarytree *chargeFile(const char* filename);


/* Cria e retorna um nó binário. */
btree *createBinaryNode(char *position, btree *parent);


/* Insere uma nova marca caso não existir na árvore binária. */
void insertNewMarca(const char *nome, broot *root, char *position, 
    btree *parent);


/* Insere um novo modelo caso não existir na árvore binária. */
void insertNewModelo(const char *nome, const char *marca, int ano, 
    int preco, int qtdade, broot *root);
void _insert_model_in_models(const char *nome, int ano, int preco, 
	int qtdade, broot *root, char *position, btree *parent);


/* Procura e retorna o indereço da Marca na árvore. */
broot *searchMarca(const char *nome, broot *root);


/* Limpa recursivamente uma árvore binária. */
void freeTree(broot* root);


#endif // FOREST_H
