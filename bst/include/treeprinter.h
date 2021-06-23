#ifndef TREEPRINTER_H
#define TREEPRINTER_H

#define __author__ "Anaxímeno Brito"

#include "linkedlist.h"
#include "forest.h"


/* Guarda as divisas das árvores na hora que serão imprimidas. */
typedef struct _divs
{
    char f, s;
} DIVS;


/* Retorna as divisas das árvores na hora de imprimir. */
struct _divs *_get_divs(b_tree *node);


/**  Mostra recursivamente uma árvore binária. Tem os tipos :
 *    -> 1 : em ordem,
 *    -> 2 : pré ordem,
 *    -> 3 : pós ordem. */
void printTree(STORE store, int tipo, const char *title);



/**  Mostram a árvore em ordem. */

/* Retorna uma lista com os níveis de profundidade que necessítam ter 
uma string de ramo vertical (VERTICAL_BRANCH) na hora de mostrar a árvore.*/
linked_number *_in_order_branch_depths(b_tree *node, linked_number *list);
/* Retorna a string de ramo a ser mostrado dependendo do nó. */
char *_in_order_branch(b_tree *node);
/* Chamada recursiva que mostra a árvore em ordem. */
void _in_order(b_tree *root);


/** Mostram a árvore em pré ordem.  */

/* Retorna uma lista com os níveis de profundidade que necessítam ter 
uma string de ramo vertical (VERTICAL_BRANCH) na hora de mostrar a árvore.*/
linked_number *_pre_order_branch_depths(b_tree *node, linked_number *list);
/* Retorna a string de ramo a ser mostrado dependendo do nó. */
char *_pre_order_branch(b_tree *node);
/* Chamada recursiva que mostra a árvore em pré ordem. */
void _pre_order(b_tree *root);


/** Mostram a árvore em pós ordem.  */

/* Retorna uma lista com os níveis de profundidade que necessítam ter 
uma string de ramo vertical (VERTICAL_BRANCH) na hora de mostrar a árvore.*/
linked_number *_post_order_branch_depths(b_tree *node, linked_number *list);
/* Retorna a string de ramo a ser mostrado dependendo do nó. */
char *_post_order_branch(b_tree *node);
/* Chamada recursiva que mostra a árvore em pós ordem. */
void _post_order(b_tree *root);

#endif // TREEPRINTER_H
