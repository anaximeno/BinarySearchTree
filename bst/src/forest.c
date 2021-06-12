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


linked *profundidade_reversa_em_ordem(btree *node, char* position, linked* list)
{
	char *search_pos = !strcmp(position, R) ? L : R;
	if (node->parent == NULL)
		return list;
	else if (!strcmp(node->parent->position, search_pos)) {
		insert_in_list(&list, node->parent->depth);
		return profundidade_reversa_em_ordem(node->parent, search_pos, list);
	}
	else
		return profundidade_reversa_em_ordem(node->parent, position, list);
}


char *ramo_em_order(broot node)
{
	if (node->depth != 0) {
		unsigned short int i;
		linked *branch_levels = NULL;

		branch_levels = profundidade_reversa_em_ordem(node, node->position, branch_levels);

		for (i = 1 ; i < node->depth ; ++i)
			printf(list_search(branch_levels, i) ? "│ " : "  ");

		clean_list(&branch_levels);

		return !strcmp(node->position, R) ? "└──" : "┌──";
	}

	else
		return "━";
}


void mostrar_em_ordem(btree *root)
{
	if (root == NULL) return ; 

	mostrar_em_ordem(root->left);

	char div01, div02;
	if (root->nivel == 0) {
		div01 = '[';
		div02 = ']';
	} else {
		div01 = '<';
		div02 = '>';
	}

	printf("%s%c%d%c\n", ramo_em_order(root), div01, root->valor, div02);

	mostrar_em_ordem(root->right);
}


// TODO: terminar esse código!
void print_tree(btree *root, char tipo)
{
	switch (tipo)
	{
	printf("\n\n\t  BINARY SEARCH TREE \n\n");
	case 'a':
		/* Mostra a árvore binária em ordem. */
		mostrar_em_ordem(root);
		break;
	case 'b':
		break;
	case 'c':
		break;
	default:
		break;
	}
}