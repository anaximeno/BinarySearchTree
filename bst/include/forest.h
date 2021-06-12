/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdlib.h>
#include <stdbool.h>
#include <linkedlist.h>

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
 *    -> nivel (int) : nivel do nó na árvore
 *    -> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT" */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    int valor, depth, nivel;
    char *position;
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


/* Mostra árvores binárias em ordem. */
void mostrar_em_ordem(btree *root);


/*  Criar e retorna os ramos da árvore em ordem dependendo da 
 *  posição e profundidade (depth). */
char *ramo_em_order(broot node);


/* Retorna os níveis em que devem ter ramos na hora de mostrar a árvore
 * binária em ordem. */
linked *profundidade_reversa_em_ordem(btree *node, char* position, linked* list);

#endif // FOREST_H
