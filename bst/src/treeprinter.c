#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "treeprinter.h"
#include "forest.h"
#include "linkedlist.h"
#include "common.h"





#define DEPTH_MULTIPLIER 2


void printTree(STORE store, int tipo, const char *title)
{
  	switch (tipo)
  	{
  	case 1:
  		/* Mostra a árvore binária em ordem. */
          printf("\n\n BINARY SEARCH TREE - %s", title);
  		printf(" - Em Ordem\n\n");

  		_in_order(store.root);

  		putchar('\n');
  		break;
  	case 2:
  		/* Mostra a árvore binária em pré ordem. */
  		printf("\n\n BINARY SEARCH TREE - %s", title);
  		printf(" - Pre Ordem\n\n");

  		_pre_order(store.root);

  		putchar('\n');
  		break;
  	case 3:
  		/* Mostra a árvore binária em pós ordem. */
  		printf("\n\n BINARY SEARCH TREE - %s", title);
  		printf(" - Pós Ordem\n\n");

  		_post_order(store.root);

  		putchar('\n');
  		break;
  	default:
  		printf("\n erro: opcao desconhecida, escolha entre (1, 2 ou 3)!\n");
  		break;
  	}
}


struct _divs *_get_divs(b_tree *node)
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

linked_number *_in_order_branch_depths(b_tree *node, linked_number *list)
{
	/* Procura por posições contrárias reversamente na árvore. */
    char *search_position = !strcmp(node->position, R) ? L : R;
    b_tree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (!strcmp(parent->position, search_position))
		insertInNumberList(&list, parent->level*DEPTH_MULTIPLIER);

    return _in_order_branch_depths(parent, list);

}


char *_in_order_branch(b_tree *node)
{
    if (node->level != 0) {
		linked_number *branch_depths = NULL;

		branch_depths = _in_order_branch_depths(node, branch_depths);
        unsigned short int i;
		/* Profundidade visual do nó na árvore. */
		int depth = node->level*DEPTH_MULTIPLIER;
		for (i = 1 ; i < depth ; ++i)
			printf(isInNumberList(branch_depths, i) ? VERTICAL_BRANCH : BRANCH_SPACES);

		freeNumberList(&branch_depths);

		return !strcmp(node->position, R) ? LEFT_BRANCH : RIGHT_BRANCH;
	}

	else
		return ROOT_BRANCH;
}


void _in_order(b_tree *root)
{
    if (root == NULL)
		return ;

	_in_order(root->left);

    DIVS *divs = _get_divs(root);

	printf("%s%c%s%c\n", _in_order_branch(root), divs->f, root->brand.nome, divs->s);
	free(divs);

	_in_order(root->right);
}


	/** Mostram a árvore em pré ordem.  */

linked_number *_pre_order_branch_depths(b_tree *node, linked_number *list)
{
    b_tree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->right != NULL && parent->right != node)
		insertInNumberList(&list, node->level*DEPTH_MULTIPLIER);

    return _pre_order_branch_depths(parent, list);
}

char *_pre_order_branch(b_tree *node)
{
    if (node->level != 0) {
		char *branch;
		b_tree *parent = node->parent;
		linked_number *branch_depths = NULL;
        unsigned short int i, depth;


		branch_depths = _pre_order_branch_depths(node, branch_depths);


		/* Profundidade visual do nó na árvore. */
		depth = node->level*DEPTH_MULTIPLIER;

		for (i = 1 ; i < depth ; ++i)
			printf(isInNumberList(branch_depths, i) ? VERTICAL_BRANCH : BRANCH_SPACES);

		freeNumberList(&branch_depths);


		if (parent->left != NULL && parent->right != NULL && parent->left == node)
			branch = MIDDLE_BRANCH;
		else
			branch = LEFT_BRANCH;

		return branch;
	}

	else
		return ROOT_BRANCH;
}

void _pre_order(b_tree *root)
{
	if (root == NULL)
		return ;


	DIVS *divs = _get_divs(root);

	printf("%s%c%s%c\n", _pre_order_branch(root), divs->f, root->brand.nome, divs->s);

	free(divs);
	_pre_order(root->left);
	_pre_order(root->right);
}


	/** Mostram a árvore em pós ordem.  */

linked_number *_post_order_branch_depths(b_tree *node, linked_number *list)
{
    b_tree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->left != NULL && parent->left != node)
		insertInNumberList(&list, node->level*DEPTH_MULTIPLIER);

    return _post_order_branch_depths(parent, list);
}


char *_post_order_branch(b_tree *node)
{
    if (node->level != 0) {
		linked_number *branch_depths = NULL;
		b_tree *parent = node->parent;
		char *branch;

		branch_depths = _post_order_branch_depths(node, branch_depths);

        unsigned short int i;
		/* Profundidade visual do nó na árvore. */
		int depth = node->level*DEPTH_MULTIPLIER;
		for (i = 1 ; i < depth ; ++i)
			printf(isInNumberList(branch_depths, i) ? VERTICAL_BRANCH : BRANCH_SPACES);

		freeNumberList(&branch_depths);

		if (parent->right != NULL && parent->left != NULL && parent->right == node)
			branch = MIDDLE_BRANCH;
		else
			branch = RIGHT_BRANCH;

		return branch;
	}

	else
		return ROOT_BRANCH;
}


void _post_order(b_tree *root)
{
	if (root == NULL)
		return ;


	_post_order(root->left);
	_post_order(root->right);

	DIVS *divs = _get_divs(root);

	printf("%s%c%s%c\n", _post_order_branch(root), divs->f, root->brand.nome, divs->s);
	free(divs);
}
