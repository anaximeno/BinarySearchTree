#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "treeprinter.h"
#include "forest.h"
#include "linkedlist.h"

#define __author__ "Anaxímeno Brito"

#define BRANCHSPACES "  "
#define VERTICALBRANCH "│ "
#define LEFTBRANCH "└──"
#define RIGHTBRANCH "┌──"
#define ROOTBRANCH "━"
#define MIDDLEBRANCH "├──"



void printTree(btree *root, char tipo)
{
	switch (tipo)
	{
	case 'a':
		/* Mostra a árvore binária em ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Em Ordem\n\n");
		printTreeInOrder(root);
		putchar('\n');
		break;
	case 'b':
		/* Mostra a árvore binária em pré ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Pré Ordem\n\n");
		printTreePreOrder(root);
		putchar('\n');
		break;
	case 'c':
		/* Mostra a árvore binária em pós ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Pós Ordem\n\n");
		printTreePostOrder(root);
		putchar('\n');
		break;
	default:
		printf("\n erro: opção desconhecida, escolha entre (a, b ou c)!\n");
		break;
	}
}


typedef struct _divs
{
    char f, s;
} DIVS;


struct _divs *getDivs(btree *node)
{
    DIVS *divs = (DIVS *) malloc (sizeof(DIVS));
	if (divs != NULL) {
		if (node->level == 0) {
			divs->f = '[';
			divs->s = ']';
		} else {
			divs->f = '<';
			divs->s = '>';
		}
	}
    return divs;
}

	/** Mostram árvores binárias em Ordem */

linked *branchLevelsInOrder(btree *node, linked *list)
{
	/* Procura por posições contrárias reversamente na árvore. */
    char *search_position = !strcmp(node->position, R) ? L : R;
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (!strcmp(parent->position, search_position))
		insertInList(&list, parent->level*DEPTH_MULTIPLIER);

    return branchLevelsInOrder(parent, list);

}


char *branchInOrder(btree *node)
{
    if (node->level != 0) {
		linked *branch_levels = NULL;

		branch_levels = branchLevelsInOrder(node, branch_levels);
        unsigned short int i;
		for (i = 1 ; i < node->level*DEPTH_MULTIPLIER ; ++i)
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

    DIVS *divs = getDivs(root);
	printf("%s%c%d%c\n", branchInOrder(root), divs->f, root->valor, divs->s);
	free(divs);

	printTreeInOrder(root->right);
}


	/** Mostram a árvore em pré ordem.  */

linked *branchLevelsPreOrder(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->right != NULL && parent->right != node)
		insertInList(&list, node->level*DEPTH_MULTIPLIER);

    return branchLevelsPreOrder(parent, list);
}

char *branchPreOrder(btree *node)
{
    if (node->level != 0) {
		linked *branch_levels = NULL;

		branch_levels = branchLevelsPreOrder(node, branch_levels);

        unsigned short int i;
		for (i = 1 ; i < node->level*DEPTH_MULTIPLIER ; ++i)
			printf(isInList(branch_levels, i) ? VERTICALBRANCH : BRANCHSPACES);
		freeList(&branch_levels);

		btree *parent = node->parent;
		char *branch;

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


	DIVS *divs = getDivs(root);

	printf("%s%c%d%c\n", branchPreOrder(root), divs->f, root->valor, divs->s);

	free(divs);
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
		insertInList(&list, node->level*DEPTH_MULTIPLIER);

    return branchLevelsPostOrder(parent, list);
}


char *branchPostOrder(btree *node)
{
    if (node->level != 0) {
		linked *branch_levels = NULL;

		branch_levels = branchLevelsPostOrder(node, branch_levels);

        unsigned short int i;
		for (i = 1 ; i < node->level*DEPTH_MULTIPLIER ; ++i)
			printf(isInList(branch_levels, i) ? VERTICALBRANCH : BRANCHSPACES);
		freeList(&branch_levels);

		btree *parent = node->parent;
		char *branch;

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

	DIVS *divs = getDivs(root);
	printf("%s%c%d%c\n", branchPostOrder(root), divs->f, root->valor, divs->s);
	free(divs);
}

