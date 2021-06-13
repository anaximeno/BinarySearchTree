/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdbool.h>

#ifndef FOREST_H
#define FOREST_H


#define R "RIGHT"
#define L "LEFT"
#define DEPTH_MULTIPLIER 2


/* Estrutura de árvore binária, com os campos:
 *    -> parent (struct _binarytree *) : estrutura pai do nó atual
 *    -> left (struct _binarytree *) : estrutura do lado esquerdo
 *    -> right (struct _binarytree *) : estrutura do lado direita
 *    -> valor (int) : guarda um valor inteiro
 *    -> depth (int) : profundidade do nó na árvore
 *    -> level (int) : nivel do nó na árvore
 *    -> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT" */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    int valor, depth, level;
    char *position;
    // TODO: criar mais campos!
} btree;


/* Ponteiro para árvore binária. */
typedef btree* broot;


/* Cria um nó da árvore binária. */
struct _binarytree *createBinaryNode(int valor, char *position,
                                int level, int depth, btree *parent);



/* Insere um valor na árvore binária. */
void insertInTree(broot *root, int valor);


/* Limpa recursivamente uma árvore binária. */
void freeTree(broot *root);


/**  Mostra recusivamente uma árvore binária. Tem os tipos :
 *    -> a : em ordem,
 *    -> b : pré ordem,
 *    -> c : pós ordem. */
void printTree(btree *root, char tipo);


#endif // FOREST_H
