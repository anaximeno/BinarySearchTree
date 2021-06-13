#ifndef TREEPRINTER_H
#define TREEPRINTER_H

#include "linkedlist.h"
#include "forest.h"

#define _author_ "Anaxímeno Brito"

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
