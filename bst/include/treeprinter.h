#ifndef TREEPRINTER_H
#define TREEPRINTER_H

#define __author__ "Anaxímeno Brito"

#include "linkedlist.h"
#include "forest.h"


/* Para sistemas baseados em unix, o programa utilizará caracteres utf-8 para apresentar a árvore
e para windows apenas caracteres ascii.*/
#ifdef unix
    #define BRANCH_SPACES "  "
    #define VERTICAL_BRANCH "│ "
    #define LEFT_BRANCH "└──"
    #define RIGHT_BRANCH "┌──"
    #define ROOT_BRANCH "━"
    #define MIDDLE_BRANCH "├──"
    #define LINE_BRANCH "───"
#endif // unix, UTF-8 characters


#ifdef _WIN32
    #define BRANCH_SPACES "  "
    #define VERTICAL_BRANCH "| "
    #define LEFT_BRANCH "'--"
    #define RIGHT_BRANCH ".--"
    #define ROOT_BRANCH "="
    #define MIDDLE_BRANCH "|--"
    #define LINE_BRANCH "---"
#endif // _WIN32, ASCII characters

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
