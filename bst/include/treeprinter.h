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
 *    -> a : em ordem,
 *    -> b : pré ordem,
 *    -> c : pós ordem. */
void printTree(b_tree *root, char tipo, const char *title);



/**  Mostram a árvore em ordem. */

linked_number *_in_order_branch_depths(b_tree *node, linked_number *list);
char *_in_order_branch(b_tree *node);
void _in_order(b_tree *root);


/** Mostram a árvore em pré ordem.  */

linked_number *_pre_order_branch_depths(b_tree *node, linked_number *list);
char *_pre_order_branch(b_tree *node);
void _pre_order(b_tree *root);


/** Mostram a árvore em pós ordem.  */

linked_number *_post_order_branch_depths(b_tree *node, linked_number *list);
char *_post_order_branch(b_tree *node);
void _post_order(b_tree *root);

#endif // TREEPRINTER_H
