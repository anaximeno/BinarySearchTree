/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdlib.h>
#include <stdbool.h>

#ifndef FOREST_H
#define FOREST_H



#define R "RIGHT"
#define L "LEFT"
#define DEPTH_MULTIPLIER 2

typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    int valor, depth, nivel;
    char *posicao;
    // TODO: criar mais campos!
} btree;

/* Ponteiro para árvore binária. */
typedef btree* broot;

/* Limpa recursivamente uma árvore binária. */
void freetree(broot *root);

/**  Mostra recusivamente uma árvore binária. Tem os tipos :
 *    -> a : em ordem,
 *    -> b : pré ordem,
 *    -> c : pós ordem. */
void print_tree(btree *root, char tipo);


#endif // FOREST_H
