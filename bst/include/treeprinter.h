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

linked *branchLevelsInOrder(btree *node, linked *list);
char *branchInOrder(btree *node);
void printTreeInOrder(btree *root);


/** Mostram a árvore em pré ordem.  */

linked *branchLevelsPreOrder(btree *node, linked *list);
char *branchPreOrder(btree *node);
void printTreePreOrder(btree *root);


/** Mostram a árvore em pós ordem.  */

linked *branchLevelsPostOrder(btree *node, linked *list);
char *branchPostOrder(btree *node);
void printTreePostOrder(btree *root);

#endif // TREEPRINTER_H
