/* Guarda códigos de árvores binárias de pesquisa usadas no trabalho. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "linkedlist.h"
#include "treeprinter.h"

unsigned short int i;


void freeTree(broot *root)
{
	if (*root == NULL)
		return ;

	freeTree(&(*root)->left);
	freeTree(&(*root)->right);

	free(*root);
}


void printTree(btree *root, char tipo)
{
	printf("\n\n\t  BINARY SEARCH TREE");
	switch (tipo)
	{
	case 'a':
		printf(" - Em Ordem\n\n");
		/* Mostra a árvore binária em ordem. */
		printTreeInOrder(root);
		break;
	case 'b':
		printf(" - Pré Ordem\n\n");
		printTreePreOrder(root);
		break;
	case 'c':
		printf(" - Pós Ordem\n\n");
		printTreePostOrder(root);
		break;
	default:
		printf("\n erro: opção desconhecida, escolha entre (a, b ou c)!\n");
		break;
	}
}

struct _binarytree *createBinaryNode(int valor, char *position,
    int level, int depth, btree *parent)
{
	btree *tmp = (btree *) malloc(sizeof(btree));

	if (tmp != NULL) {
		tmp->valor = valor;
		tmp->depth = depth;
		tmp->level = level;
		tmp->position = position;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->parent = parent;
	}

	return tmp;
}


void append_in_tree(int valor, broot *root, btree *parent, char *position)
{
	if (*root == NULL) {
		int level, depth;
		level = parent == NULL ? 0 : parent->level+1;
		depth = level*DEPTH_MULTIPLIER;

		*root = createBinaryNode(valor, position, level, depth, parent);
	}
	else if ( valor < (*root)->valor )
		append_in_tree(valor, &(*root)->left, *root, L);
	else
		append_in_tree(valor, &(*root)->right, *root, R);
}


void insertInTree(broot *root, int valor)
{
    append_in_tree(valor, root, NULL, "ROOT");
}
