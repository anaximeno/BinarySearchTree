/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdbool.h>
#include "common.h"
#include "linkedlist.h"

#ifndef FOREST_H
#define FOREST_H

#define R "RIGHT"
#define L "LEFT"




struct _brand
{
    char nome[NOMEMAX];
    int qtdade_modelos,
        valor_total,
        total_carros;
    /* modelos aponta para uma lista, contendo todos os modelos dessa marca. */
    model_llist *models;
};

/* Estrutura de árvore binária, com os campos:
 *    -> parent (struct _binarytree *) : estrutura pai do nó atual
 *    -> left (struct _binarytree *) : estrutura do lado esquerdo
 *    -> right (struct _binarytree *) : estrutura do lado direita
 *    -> valor (int) : guarda um valor inteiro
 *    -> level (int) : nivel do nó na árvore
 *    -> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT"
 *    -> brand (struct _brand) : estrutura que representa uma marca.
 * */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    char *position;
    int level;

    struct _brand brand;
} b_tree;


/* Estrutura Macro (em termos de tamanho) que quarda a raíz das árvores. */
typedef struct _store
{
    const char *nome;
    int total_marcas, total_modelos;
    b_tree *root;
} STORE;


/* Carrega um nó binário guardado no arquivo de nome [marca].txt com os elementos,
e retorna se conseguiu ou não carregar (bool).

Organização do arquivo a ser lido:
    [nome do modelo]    [ano de lançamento]     [preço]     [quantidate]

*/
void chargeBrandFromFile(char *filename, STORE *store);


/* Cria e retorna um nó binário. */
b_tree *createBinaryNode(char *position, b_tree *parent);


/* Insere uma nova marca caso não existir na árvore binária. */
void insertBrand(const char *nome, STORE *store, bool verbose);
/* Tenta inserir recursivamente uma marca na árvore e retorna se foi inserida (true ou false). */
bool _insert_brand_in_tree(const char *nome, b_tree **root, char *position,
    b_tree *parent);


/* Procura e retorna o indereço da Marca na árvore. */
b_tree **searchBrand(const char *nome, b_tree **root);


/* Insere um novo modelo caso não existir na árvore binária. */
void insertModel(char *nome, char *marca, int ano,
    int preco, int qtdade, STORE *store);

/* Procura e retorna um modelo em na árvore que se encontra dentro de uma marca. */
b_tree *search_modelo(const char *nome, b_tree *marca_root);


/* Guarda Marca e seus modelos em um arquivo, com nome_da_marca.txt */
bool saveBrandInFile(STORE store, char *nome_marca);


/* Limpa recursivamente uma árvore binária. */
void freetree(b_tree **root);


/* Retorna o nó mais à esquerda do nó indicado. */
b_tree **_leftest_node(b_tree **node);


/* Elimina o nó 'root' indicado (não precisa ser a raíz) da árvore. */
void removeBinaryNode(b_tree **root);


/* Remove uma marca da árvore. */
void removeBrand(b_tree **root, const char *marca);



/* O nó filho herda alguns dados referentes a posição do nó pai.

Os dados herdados são:
    -> parent
    -> position
    -> level */
void _inherit_position(b_tree *filho, b_tree *pai);


/* Lista recursivamente todas as marcas da árvore.*/
void _list_brands(b_tree *node);
/* Lista todas as marcas da loja. */
void listBrands(STORE *store);

#endif // FOREST_H
