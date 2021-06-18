/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdbool.h>
#include "common.h"

#ifndef FOREST_H
#define FOREST_H

#define R "RIGHT"
#define L "LEFT"



/* Estrutura de árvore binária, com os campos:
 *    -> parent (struct _binarytree *) : estrutura pai do nó atual
 *    -> left (struct _binarytree *) : estrutura do lado esquerdo
 *    -> right (struct _binarytree *) : estrutura do lado direita
 *    -> valor (int) : guarda um valor inteiro
 *    -> level (int) : nivel do nó na árvore
 *    -> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT"
 *    -> model (union struct _modelo) : estrutura que representa um modelo
 *    -> brand (union struct _marca) : estrutura que representa uma marca.
 * */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    char *position, *tipo;
    int level;

    union
    {
        struct _model
        {
            char nome[NOMEMAX];
            int ano, preco, qtdade;
        } model;
        struct _brand
        {
            char nome[NOMEMAX];
            int qtdade_modelos, valor_total;
            /* modelos aponta para uma árvore binária,
               contendo todos os modelos dessa marca. */
            struct _binarytree *modelos;
        } brand;
    };
} b_tree;


/* Estrutura Macro (em termos de tamanho) que quarda a raíz das árvores. */
typedef struct _store
{
    char *nome;
    int total_marcas, total_carros;
    b_tree *root;
} STORE;




/* Carrega um nó binário guardado no arquivo de nome [marca].txt com os elementos,
e retorna se conseguiu ou não carregar (bool).

Organização do arquivo a ser lido:
    [nome do modelo]    [ano de lançamento]     [preço]     [quantidate]

*/
bool charge_file(char *filename, STORE *store);


/* Cria e retorna um nó binário. */
b_tree *create_binary_node(char *position, b_tree *parent);


/* Insere uma nova marca caso não existir na árvore binária. */
void insert_brand(const char *nome, STORE *store);
/* Insere recursivamente uma marca na árvore */
void _insert_brand_in_tree(const char *nome, b_tree **root, char *position,
    b_tree *parent);


/* Procura e retorna o indereço da Marca na árvore. */
b_tree *search_brand(const char *nome, b_tree *root);


/* Insere um novo modelo caso não existir na árvore binária. */
void insert_model(const char *nome, const char *marca, int ano,
    int preco, int qtdade, b_tree **root);
/* Função recursiva que insere um modelo na marca determinada.  */
void _insert_model_in_brand(b_tree **brand, const char *nome, int ano, int preco,
	int qtdade, b_tree **root, char *position, b_tree *parent);


/* Procura e retorna um modelo em na árvore que se encontra dentro de uma marca. */
b_tree *search_modelo(const char *nome, b_tree *marca_root);


/* Limpa recursivamente uma árvore binária. */
void freetree(b_tree **root);


/* Retorna o nó mais à esquerda do nó indicado. */
b_tree *_leftest_node(b_tree *node);


/* Elimina um nó da árvore. */
void remove_binary_node(b_tree **root);


/* Remove uma marca da árvore. */
void remove_brand(b_tree **root, const char *marca);



/* O nó filho herda alguns dados referentes a posição do nó pai.

Os dados herdados são:
    -> parent
    -> position
    -> level */
void inherit_position(b_tree *filho, b_tree *pai);
#endif // FOREST_H
