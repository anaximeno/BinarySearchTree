/* Guarda códigos de árvores binárias de pesquisa usadas no trabalho. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "linkedlist.h"
#include "common.h"



void freetree(b_tree **root)
{
	if (*root == NULL)
		return ;

	freeModelList(&(*root)->brand.models);

	freetree(&(*root)->left);
	freetree(&(*root)->right);

	free(*root);
	*root = NULL;
}


bool charge_file(char* filename, STORE *store)
{
	char *marca = get_name(filename);
    b_tree **node = search_brand(marca, &store->root);

    /* Se a marca não for encontrada na arvore, cria nova árvore */
	if ( *node == NULL ) {
		insert_brand(marca, store);
		node = search_brand(marca, &store->root);
	}

	free(marca);

	if ( *node != NULL ) {
		FILE *f = fopen(filename, "rt");

		if ( f != NULL ) {
			char nome[NOMEMAX];
			int ano, preco, qtdade;

			while (fscanf(f, "%s %d %d %d", nome, &ano, &preco, &qtdade) != EOF) {
				insertModelInList(&(*node)->brand.models, nome, ano, preco, qtdade);
				(*node)->brand.qtdade_modelos++;
				(*node)->brand.valor_total += preco;
			}

			fclose(f);
			return true;
		} else {
            printf("\n Não foi possível abrir: '%s'!\n", filename);
		}
	}

	return false;
}


b_tree *create_binary_node(char *position, b_tree *parent)
{
	b_tree *node = (b_tree *) malloc(sizeof(b_tree));

	if (node != NULL) {
		node->level = parent == NULL ? 0 : parent->level+1;
		node->left = node->right = NULL;
		node->parent = parent;
		node->position = position;
	}

	return node;
}


void _insert_brand_in_tree(const char *nome, b_tree **root, char *position, b_tree *parent)
{
	if (*root == NULL) {
		b_tree *node = create_binary_node(position, parent);

		if (node != NULL) {
			strcpy(node->brand.nome, nome);
			node->brand.qtdade_modelos = 0;
			node->brand.valor_total = 0;
			node->brand.models = NULL;

			//char output[43+strlen(nome)];
			//sprintf(output, "\n Marca '%s' foi introduzida na árvore!\n", nome);
			//animate(output, 25000);
		}

		*root = node;

	} else if (strcmp(nome, (*root)->brand.nome) < 0) { // LEFT
		_insert_brand_in_tree(nome, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->brand.nome) > 0) { // RIGHT
		_insert_brand_in_tree(nome, &(*root)->right, R, *root);
	} else {
		printf("\n Marca: '%s' já se encontra na árvore!\n", nome);
	}
}


b_tree **search_brand(const char *nome, b_tree **root)
{
	if (root == NULL)
		return NULL;
	else if (strcmp(nome, (*root)->brand.nome) < 0)
		return search_brand(nome, &(*root)->left);
	else if (strcmp(nome, (*root)->brand.nome) > 0)
		return search_brand(nome, &(*root)->right);
	else
		return root;
}


void insert_model(char *nome, char *marca,
						int ano, int preco, int qtdade, b_tree **root)
{
	b_tree **node = search_brand(marca, root);

	if (*node != NULL) {
		insertModelInList(&(*node)->brand.models, nome, ano, preco, qtdade);
		(*node)->brand.qtdade_modelos++;
		(*node)->brand.valor_total += preco;
	} else {
		printf("\n Marca: '%s' não foi encontrada na árvore binária!", marca);
	}
}


void insert_brand(const char *nome, STORE *store)
{
	_insert_brand_in_tree(nome, &store->root, "ROOT", NULL);
}


void inherit_position(b_tree *filho, b_tree *pai)
{
	filho->parent = pai->parent;
	filho->level = pai->level;
	filho->position = pai->position;
}



b_tree **_leftest_node(b_tree **node)
{
	if ((*node)->left == NULL)
		return node;
	else return _leftest_node(&(*node)->left);
}


void remove_brand(b_tree **root, const char *marca)
{
	b_tree **brand = search_brand(marca, root);
	if (*brand != NULL)
		remove_binary_node(brand);
    else
        printf("\n Marca '%s' não foi encontrada ná árvore! Impossível eliminar.", marca);
}


void remove_binary_node(b_tree **root)
{
	if (*root == NULL)
		return ;

	if ( (*root)->left == NULL && (*root)->right == NULL ) {
		free(*root);
		*root = NULL;
	} else if ( (*root)->left != NULL && (*root)->right == NULL ) {
		b_tree *left = (*root)->left;
		inherit_position(left, *root);
		free(*root);
		*root = left;
	} else if ( (*root)->right != NULL && (*root)->left == NULL ) {
		b_tree *right = (*root)->right;
		inherit_position(right, *root);
		free(*root);
		*root = right;
	} else {
		b_tree **tmp = _leftest_node(&(*root)->right);

		/* Copiando a informação para o nó atual. */
		strcpy((*root)->brand.nome, (*tmp)->brand.nome);
		(*root)->brand.qtdade_modelos = (*tmp)->brand.qtdade_modelos;
		(*root)->brand.valor_total = (*tmp)->brand.valor_total;
		(*root)->brand.models = (*tmp)->brand.models;
		/* Desconecta tmp com a raíz dos modelos. */
		(*tmp)->brand.models = NULL;

		remove_binary_node(tmp);
	}
}

