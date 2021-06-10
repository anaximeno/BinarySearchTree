/* Guarda códigos de árvores binárias de pesquisa usadas no trabalho. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "linkedlist.h"


void freetree(broot *root)
{
	if (*root == NULL)
		return ;

	freetree(&(*root)->left);
	freetree(&(*root)->right);

	free(*root);
}


// TODO: terminar esse código!
void print_tree(btree *root, char tipo);
