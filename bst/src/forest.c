/* Guarda códigos de árvores binárias de pesquisa usadas no trabalho. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "linkedlist.h"


char *get_name_from_file(char *txtname)
{
        char *txt = txtname;
        int i, size = 0;

        while (*txt != '.' && *txt != '\0' && ++size && ++txt) ;

        size += 1;	// Adiciona mais um espaço para '\0'
        char *name = (char *) malloc(sizeof(char)*size);

        txt = txtname;
        for (i = 0 ; txt[i] != '.' && txt[i] != '\0' ; ++i)
            name[i] = txt[i];

		name[i] = '\0';  // Adiciona o final da string

		return name;
}


void freeTree(btree **root)
{
	if (*root == NULL)
		return ;

	if ( !strcmp((*root)->tipo, "MARCA") )
		freeTree(&(*root)->marca.modelos);


	freeTree(&(*root)->left);
	freeTree(&(*root)->right);

	free(*root);
	*root = NULL;
}


bool chargeFile(char* filename, btree **root)
{
	char *nome_da_marca = get_name_from_file(filename);
    btree *brand = NULL;
    /* Se a marca não for encontrada na arvore, cria nova árvore */
	if ( (brand = searchMarca(nome_da_marca, *root)) == NULL ) {
		insertNewMarca(nome_da_marca, root);
		brand = searchMarca(nome_da_marca, *root);
	}

	if (brand != NULL) {
		FILE *f = fopen(filename, "rt");

		if (f != NULL) {
			char modelo[NOMEMAX];
			int ano, preco, qtdade;

			while (fscanf(f, "%s %d %d %d", modelo, &ano, &preco, &qtdade) != EOF) {

				_insert_modelo_in_marca(modelo, ano, preco, qtdade,
                                        &brand->marca.modelos, "ROOT", NULL);

			}

			fclose(f);

			return true;
		}
	}

	return false;
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


void _insert_marca_in_tree(const char *nome, btree **root, char *position, btree *parent)
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

		*root = brand;

		printf("\n Marca '%s' foi introduzida na árvore!\n", nome);
	} else if (strcmp(nome, (*root)->marca.nome) < 0) { // LEFT
		_insert_marca_in_tree(nome, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->marca.nome) > 0) { // RIGHT
		_insert_marca_in_tree(nome, &(*root)->right, R, *root);
	} else {
		printf("\n Marca: '%s' já se encontra na árvore!\n", nome);
	}
}


void _insert_modelo_in_marca(const char *nome, int ano, int preco,
				int qtdade, btree **root, char *position, btree *parent)
{
	if (*root == NULL) {
		btree *model = createBinaryNode(position, parent);

		if (model != NULL) {
			strcpy(model->modelo.nome, nome);
			model->modelo.ano = ano;
			model->modelo.preco = preco;
			model->modelo.qtdade = qtdade;
			model->tipo = "MODELO";
		}

        *root = model;
		printf("\n   Modelo : '%s' foi introduzido!\n", nome);
	} else if (strcmp(nome, (*root)->modelo.nome) < 0) { // LEFT
		_insert_modelo_in_marca(nome, ano, preco, qtdade, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->modelo.nome) > 0) { // RIGHT
		_insert_modelo_in_marca(nome, ano, preco, qtdade, &(*root)->right, R, *root);
	} else {
		printf("\n Modelo: '%s' já se encontra na árvore!\n", nome);
	}
}


btree *searchMarca(const char *nome, btree *root)
{
	if (root == NULL)
		return NULL;
	else if (strcmp(nome, root->marca.nome) < 0)
		return searchMarca(nome, root->left);
	else if (strcmp(nome, root->marca.nome) > 0)
		return searchMarca(nome, root->right);
	else
		return root;
}


void insertNewModelo(const char *nome, const char *marca,
						int ano, int preco, int qtdade, btree **root)
{
	btree *brand = searchMarca(marca, *root);

	if (brand != NULL) {
        printf("\n Tentando inserir '%s' na marca '%s'\n", nome, marca);
		_insert_modelo_in_marca(nome, ano, preco, qtdade, &brand->marca.modelos, "ROOT", NULL);
	} else {
		printf("\n Marca: '%s' não foi encontrada na árvore binária!", marca);
	}
}


void insertNewMarca(const char *nome, btree **root)
{
	_insert_marca_in_tree(nome, root, "ROOT", NULL);
}
