/* Guarda códigos de árvores binárias de pesquisa usadas no trabalho. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "linkedlist.h"

unsigned short int i;


void freeTree(broot *root)
{
	if (*root == NULL)
		return ;

	freeTree(&(*root)->left);
	freeTree(&(*root)->right);

	free(*root);
	*root = NULL;
}


btree *createBinaryNode(int valor, char *position, int level, btree *parent)
{
	btree *tmp = (btree *) malloc(sizeof(btree));

	if (tmp != NULL) {
		tmp->valor = valor;
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
		int level;
		level = parent == NULL ? 0 : parent->level+1;

		*root = createBinaryNode(valor, position, level, parent);
	}
	else if ( valor < (*root)->valor )
		append_in_tree(valor, &(*root)->left, *root, L);
	else if ( valor > (*root)->valor )
		append_in_tree(valor, &(*root)->right, *root, R);
    else
        return ;    // Não adiciona valores repitidos
}


void insertInTree(broot *root, int valor)
{
    append_in_tree(valor, root, NULL, "ROOT");
}
