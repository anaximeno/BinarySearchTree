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

		_printTreeInOrder(root);

		putchar('\n');
		break;
	case 'b':
		/* Mostra a árvore binária em pré ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Pré Ordem\n\n");

		_printTreePreOrder(root);

		putchar('\n');
		break;
	case 'c':
		/* Mostra a árvore binária em pós ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Pós Ordem\n\n");

		_printTreePostOrder(root);

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


struct _divs *_getDivs(btree *node)
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

linked *_branchLevelsInOrder(btree *node, linked *list)
{
	/* Procura por posições contrárias reversamente na árvore. */
    char *search_position = !strcmp(node->position, R) ? L : R;
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (!strcmp(parent->position, search_position))
		insertInList(&list, parent->level*DEPTH_MULTIPLIER);

    return _branchLevelsInOrder(parent, list);

}


char *_branchInOrder(btree *node)
{
    if (node->level != 0) {
		linked *branch_levels = NULL;

		branch_levels = _branchLevelsInOrder(node, branch_levels);
        unsigned short int i;
		for (i = 1 ; i < node->level*DEPTH_MULTIPLIER ; ++i)
			printf(isInList(branch_levels, i) ? VERTICALBRANCH : BRANCHSPACES);

		freeList(&branch_levels);

		return !strcmp(node->position, R) ? LEFTBRANCH : RIGHTBRANCH;
	}

	else
		return ROOTBRANCH;
}


void _printTreeInOrder(btree *root)
{
    if (root == NULL)
		return ;

	_printTreeInOrder(root->left);

    DIVS *divs = _getDivs(root);
	printf("%s%c%d%c\n", _branchInOrder(root), divs->f, root->valor, divs->s);
	free(divs);

	_printTreeInOrder(root->right);
}


	/** Mostram a árvore em pré ordem.  */

linked *_branchLevelsPreOrder(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->right != NULL && parent->right != node)
		insertInList(&list, node->level*DEPTH_MULTIPLIER);

    return _branchLevelsPreOrder(parent, list);
}

char *_branchPreOrder(btree *node)
{
    if (node->level != 0) {
		linked *branch_levels = NULL;

		branch_levels = _branchLevelsPreOrder(node, branch_levels);

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

void _printTreePreOrder(btree *root)
{
	if (root == NULL)
		return ;


	DIVS *divs = _getDivs(root);

	printf("%s%c%d%c\n", _branchPreOrder(root), divs->f, root->valor, divs->s);

	free(divs);
	_printTreePreOrder(root->left);
	_printTreePreOrder(root->right);
}


	/** Mostram a árvore em pós ordem.  */

linked *_branchLevelsPostOrder(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->left != NULL && parent->left != node)
		insertInList(&list, node->level*DEPTH_MULTIPLIER);

    return _branchLevelsPostOrder(parent, list);
}


char *_branchPostOrder(btree *node)
{
    if (node->level != 0) {
		linked *branch_levels = NULL;

		branch_levels = _branchLevelsPostOrder(node, branch_levels);

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


void _printTreePostOrder(btree *root)
{
	if (root == NULL)
		return ;


	_printTreePostOrder(root->left);
	_printTreePostOrder(root->right);

	DIVS *divs = _getDivs(root);
	printf("%s%c%d%c\n", _branchPostOrder(root), divs->f, root->valor, divs->s);
	free(divs);
}

