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


btree *createBinNode(int valor, char *position, int level, btree *parent)
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

		*root = createBinNode(valor, position, level, parent);
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


struct _binarytree *chargeFile(const char* filename)
{
	FILE *f = fopen(filename, "rt");

	if (f != NULL) {
		btree *tmp = (btree *) malloc(sizeof(btree));
		/**
		if (tmp != NULL) {
			while (fscanf(f, "%s %d %d %d"))
		} TODO: finish this! */

		return tmp;
	}

	return NULL;
}


btree *createBinaryNode(char *position, btree *parent)
{
	btree *node = (btree *) malloc(sizeof(btree));

	if (node != NULL) {
		node->level = parent == NULL ? 0 : parent->level+1;
		node->left = node->right = NULL;
		node->parent = parent;
		node->position = position;
	}

	return node;
}


void insertNewMarca(const char *nome, broot *root, char *position, btree *parent)
{
	if (*root == NULL) {
		btree *brand = createBinaryNode(position, parent);

		if (brand != NULL) {
			strcpy(brand->marca.nome, nome);
			brand->marca.qtdade_modelos = 0;
			brand->marca.valor_total = 0;
			brand->marca.modelos = NULL;
			brand->tipo = "MARCA";
		}

		printf("\n Marca '%s' foi introduzida na árvore!\n", nome);
	} else if (strcmp(nome, (*root)->marca.nome) < 0) { // LEFT
		insertNewMarca(nome, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->marca.nome) > 0) { // RIGHT
		insertNewMarca(nome, &(*root)->right, R, *root);
	} else {
		printf("\n Marca: '%s' já se encontra na árvore!\n", nome);
	}
}


void _insert_model_in_models(const char *nome, int ano, int preco, 
	int qtdade, broot *root, char *position, btree *parent)
{
	if (*root == NULL) {
		btree *model =createBinaryNode(position, parent);

		if (model != NULL) {
			strcpy(model->modelo.nome, nome);
			model->modelo.ano = ano;
			model->modelo.preco = preco;
			model->modelo.qtdade = qtdade;
			model->tipo = "MODELO";
		}

		printf("\n Modelo: '%s' foi introduzido na árvore!\n", nome);
	} else if (strcmp(nome, (*root)->modelo.nome) < 0) { // LEFT
		_insert_model_in_models(nome, ano, preco, qtdade, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->modelo.nome) > 0) { // RIGHT
		_insert_model_in_models(nome, ano, preco, qtdade, &(*root)->right, R, *root);
	} else {
		printf("\n Modelo: '%s' já se encontra na árvore!\n", nome);
	}
}


broot *searchMarca(const char *nome, broot *root)
{
	if (*root == NULL)
		return NULL;
	else if (strcmp(nome, (*root)->marca.nome) < 0) 
		return searchMarca(nome, &(*root)->left);
	else if (strcmp(nome, (*root)->marca.nome) > 0)
		return searchMarca(nome, &(*root)->left);
	else
		return root;
}


void insertNewModelo(const char *nome, const char *marca, 
	int ano, int preco, int qtdade, broot *root)
{
	broot *brand = searchMarca(marca, root);

	if (*brand != NULL) {
		_insert_model_in_models(nome, ano, preco, qtdade, &(*brand)->marca.modelos, "ROOT", NULL);
	} else {
		printf("\n Marca: '%s' não foi encontrada na árvore binária!", marca);
	}
}