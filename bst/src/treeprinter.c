#include "treeprinter.h"
#include "forest.h"
#include "linkedlist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define BRANCHSPACES "  "
#define VERTICALBRANCH "│ "
#define LEFTBRANCH "└──"
#define RIGHTBRANCH "┌──"
#define ROOTBRANCH "━"
#define MIDDLEBRANCH "├──"


struct _divs
{
    char f_div, s_div;
};


struct _divs getDivs(btree *node)
{
    struct _divs divs;
    if (node->level == 0) {
         divs.f_div = '[';
         divs.s_div = ']';
    }
    else {
        divs.f_div = '<';
        divs.s_div = '>';
    }
    return divs;
}

/** Mostram árvores binárias em Ordem */

linked *branchLevelsInOrder(btree *node, linked *list)
{
    char *search_position = !strcmp(node->position, R) ? L : R;
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (!strcmp(parent->position, search_position))
		insertInList(&list, parent->depth);

    return branchLevelsInOrder(parent, list);

}


char *branchInOrder(btree *node)
{
    if (node->depth != 0) {
		linked *branch_levels = NULL;

		branch_levels = branchLevelsInOrder(node, branch_levels);
        unsigned short int i;
		for (i = 1 ; i < node->depth ; ++i)
			printf(isInList(branch_levels, i) ? VERTICALBRANCH : BRANCHSPACES);

		freeList(&branch_levels);

		return !strcmp(node->position, R) ? LEFTBRANCH : RIGHTBRANCH;
	}

	else
		return ROOTBRANCH;
}


void printTreeInOrder(btree *root)
{
    if (root == NULL)
		return ;

	printTreeInOrder(root->left);

    struct _divs divs = getDivs(root);
	printf("%s%c%d%c\n", branchInOrder(root), divs.f_div, root->valor, divs.s_div);

	printTreeInOrder(root->right);
}


/** Mostram a árvore em pré ordem.  */

linked *branchLevelsPreOrder(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->right != NULL && parent->right != node)
		insertInList(&list, node->depth);

    return branchLevelsPreOrder(parent, list);
}

char *branchPreOrder(btree *node)
{
    if (node->depth != 0) {
		linked *branch_levels = NULL;

		branch_levels = branchLevelsPreOrder(node, branch_levels);

        unsigned short int i;
		for (i = 1 ; i < node->depth ; ++i)
			printf(isInList(branch_levels, i) ? "│ " : "  ");
		freeList(&branch_levels);

		char *branch;
		btree *parent = node->parent;

		if (parent->left != NULL && parent->right != NULL && parent->left == node)
			branch = MIDDLEBRANCH;
		else
			branch = LEFTBRANCH;

		return branch;
	}

	else
		return ROOTBRANCH;
}

void printTreePreOrder(btree *root)
{
	if (root == NULL)
		return ;


	struct _divs divs = getDivs(root);
	printf("%s%c%d%c\n", branchPreOrder(root), divs.f_div, root->valor, divs.s_div);

	printTreePreOrder(root->left);
	printTreePreOrder(root->right);
}


/** Mostram a árvore em pós ordem.  */

linked *branchLevelsPostOrder(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->left != NULL && parent->left != node)
		insertInList(&list, node->depth);

    return branchLevelsPostOrder(parent, list);
}


char *branchPostOrder(btree *node)
{
    if (node->depth != 0) {
		linked *branch_levels = NULL;

		branch_levels = branchLevelsPostOrder(node, branch_levels);

        unsigned short int i;
		for (i = 1 ; i < node->depth ; ++i)
			printf(isInList(branch_levels, i) ? "│ " : "  ");
		freeList(&branch_levels);

		char *branch;
		btree *parent = node->parent;

		if (parent->right != NULL && parent->left != NULL && parent->right == node)
			branch = MIDDLEBRANCH;
		else
			branch = RIGHTBRANCH;

		return branch;
	}

	else
		return ROOTBRANCH;
}


void printTreePostOrder(btree *root)
{
	if (root == NULL)
		return ;


	printTreePostOrder(root->left);
	printTreePostOrder(root->right);


	struct _divs divs = getDivs(root);
	printf("%s%c%d%c\n", branchPostOrder(root), divs.f_div, root->valor, divs.s_div);
}

