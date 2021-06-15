#ifndef TREEPRINTER_H
#define TREEPRINTER_H

#define __author__ "Anaxímeno Brito"

#include "linkedlist.h"
#include "forest.h"


/**  Mostra recusivamente uma árvore binária. Tem os tipos :
 *    -> a : em ordem,
 *    -> b : pré ordem,
 *    -> c : pós ordem. */
void printTree(btree *root, char tipo);



/**  Mostram a árvore em ordem. */

linked *_branchLevelsInOrder(btree *node, linked *list);
char *_branchInOrder(btree *node);
void _printTreeInOrder(btree *root);


/** Mostram a árvore em pré ordem.  */

linked *_branchLevelsPreOrder(btree *node, linked *list);
char *_branchPreOrder(btree *node);
void _printTreePreOrder(btree *root);


/** Mostram a árvore em pós ordem.  */

linked *_branchLevelsPostOrder(btree *node, linked *list);
char *_branchPostOrder(btree *node);
void _printTreePostOrder(btree *root);

#endif // TREEPRINTER_H
