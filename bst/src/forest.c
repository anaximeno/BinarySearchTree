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
	if (*root == NULL) return ;


	if ( !strcmp((*root)->tipo, "MARCA") )
		freetree(&(*root)->brand.modelos);


	freetree(&(*root)->left);
	freetree(&(*root)->right);

	free(*root);
	*root = NULL;
}


bool charge_file(char* filename, b_tree **root)
{
	char *marca = get_name(filename);
    b_tree *brand = NULL;

    /* Se a marca não for encontrada na arvore, cria nova árvore */
	if ( (brand = search_brand(marca, *root)) == NULL ) {
		insert_brand(marca, root);
		brand = search_brand(marca, *root);
	}

	free(marca);

	if (brand != NULL) {
		FILE *f = fopen(filename, "rt");

		if (f != NULL) {
			char modelo[NOMEMAX];
			int ano, preco, qtdade;

			while (fscanf(f, "%s %d %d %d", modelo, &ano, &preco, &qtdade) != EOF) {

				_insert_model_in_brand(&brand, modelo, ano, preco, qtdade,
                                         &brand->brand.modelos, "ROOT", NULL);

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
			node->brand.modelos = NULL;
			node->tipo = "MARCA";

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


void _insert_model_in_brand(b_tree **brand, const char *nome, int ano, int preco,
				int qtdade, b_tree **root, char *position, b_tree *parent)
{
	if (*root == NULL) {
		b_tree *model = create_binary_node(position, parent);

		if (model != NULL) {
			strcpy(model->model.nome, nome);
			model->model.ano = ano;
			model->model.preco = preco;
			model->model.qtdade = qtdade;
			model->tipo = "MODELO";

			(*brand)->brand.qtdade_modelos++;
			(*brand)->brand.valor_total += preco;

			//char output[51+strlen(nome)];
			//sprintf(output, "\n   Modelo : '%s' foi introduzido na marca '%s'!\n", nome);
			//animate(output, 30000);
		}

        *root = model;

	} else if (strcmp(nome, (*root)->model.nome) < 0) { // LEFT
		_insert_model_in_brand(brand, nome, ano, preco, qtdade, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->model.nome) > 0) { // RIGHT
		_insert_model_in_brand(brand, nome, ano, preco, qtdade, &(*root)->right, R, *root);
	} else {
		printf("\n Modelo: '%s' já se encontra na árvore!\n", nome);
	}
}


b_tree *search_brand(const char *nome, b_tree *root)
{
	if (root == NULL)
		return NULL;
	else if (strcmp(nome, root->brand.nome) < 0)
		return search_brand(nome, root->left);
	else if (strcmp(nome, root->brand.nome) > 0)
		return search_brand(nome, root->right);
	else
		return root;
}


void insert_model(const char *nome, const char *marca,
						int ano, int preco, int qtdade, b_tree **root)
{
	b_tree *brand = search_brand(marca, *root);

	if (brand != NULL) {
		_insert_model_in_brand(&brand, nome, ano, preco, qtdade, &brand->brand.modelos, "ROOT", NULL);
	} else {
		printf("\n Marca: '%s' não foi encontrada na árvore binária!", marca);
	}
}


void insert_brand(const char *nome, b_tree **root)
{
	_insert_brand_in_tree(nome, root, "ROOT", NULL);
}


