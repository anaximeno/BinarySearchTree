/* Guarda códigos de árvores binárias de pesquisa usadas no trabalho. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "forest.h"
#include "linkedlist.h"
#include "common.h"


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


void freetree(b_tree **root)
{
	if (*root == NULL) return ;


	if ( !strcmp((*root)->tipo, "MARCA") )
		freetree(&(*root)->marca.modelos);


	freetree(&(*root)->left);
	freetree(&(*root)->right);

	free(*root);
	*root = NULL;
}


bool charge_file(char* filename, b_tree **root)
{
	char *marca = get_name_from_file(filename);
    b_tree *brand = NULL;

    /* Se a marca não for encontrada na arvore, cria nova árvore */
	if ( (brand = searchMarca(marca, *root)) == NULL ) {
		insertNewMarca(marca, root);
		brand = searchMarca(marca, *root);
	}

	free(marca);

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


b_tree *createBinaryNode(char *position, b_tree *parent)
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


void _insert_marca_in_tree(const char *nome, b_tree **root, char *position, b_tree *parent)
{
	if (*root == NULL) {
		b_tree *brand = createBinaryNode(position, parent);

		if (brand != NULL) {
			strcpy(brand->marca.nome, nome);
			brand->marca.qtdade_modelos = 0;
			brand->marca.valor_total = 0;
			brand->marca.modelos = NULL;
			brand->tipo = "MARCA";
		}

		*root = brand;

        char output[43+NOMEMAX];
        sprintf(output, "\n Marca '%s' foi introduzida na árvore!\n", nome);
        animate(output, 25000);

	} else if (strcmp(nome, (*root)->marca.nome) < 0) { // LEFT
		_insert_marca_in_tree(nome, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->marca.nome) > 0) { // RIGHT
		_insert_marca_in_tree(nome, &(*root)->right, R, *root);
	} else {
		printf("\n Marca: '%s' já se encontra na árvore!\n", nome);
	}
}


void _insert_modelo_in_marca(const char *nome, int ano, int preco,
				int qtdade, b_tree **root, char *position, b_tree *parent)
{
	if (*root == NULL) {
		b_tree *model = createBinaryNode(position, parent);

		if (model != NULL) {
			strcpy(model->modelo.nome, nome);
			model->modelo.ano = ano;
			model->modelo.preco = preco;
			model->modelo.qtdade = qtdade;
			model->tipo = "MODELO";
		}

        *root = model;

		char output[37+NOMEMAX];
		sprintf(output, "\n   Modelo : '%s' foi introduzido!\n", nome);
		animate(output, 30000);

	} else if (strcmp(nome, (*root)->modelo.nome) < 0) { // LEFT
		_insert_modelo_in_marca(nome, ano, preco, qtdade, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->modelo.nome) > 0) { // RIGHT
		_insert_modelo_in_marca(nome, ano, preco, qtdade, &(*root)->right, R, *root);
	} else {
		printf("\n Modelo: '%s' já se encontra na árvore!\n", nome);
	}
}


b_tree *searchMarca(const char *nome, b_tree *root)
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
						int ano, int preco, int qtdade, b_tree **root)
{
	b_tree *brand = searchMarca(marca, *root);

	if (brand != NULL) {
		_insert_modelo_in_marca(nome, ano, preco, qtdade, &brand->marca.modelos, "ROOT", NULL);
	} else {
		printf("\n Marca: '%s' não foi encontrada na árvore binária!", marca);
	}
}


void insertNewMarca(const char *nome, b_tree **root)
{
	_insert_marca_in_tree(nome, root, "ROOT", NULL);
}
