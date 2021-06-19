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


void chargeBrandFromFile(char* filename, STORE *store)
{
	FILE *f = fopen(filename, "rt");
	if ( f != NULL ) {
		char nome[NOMEMAX];
		int ano, preco, qtdade;

		char *marca = getName(filename);
		b_tree **node = searchBrand(marca, &store->root);


		/* Se a marca não for encontrada na arvore, cria nova árvore */
		if ( *node == NULL ) {
			insertBrand(marca, store);
			if ( (node = searchBrand(marca, &store->root)) == NULL ) {
				printf("\n Erro: não foi possível criar marca '%s' na árvore!", marca);
				fclose(f);
				return ;
			}
		}

		/* Liberta a variável marca não mais necessária. */
		free(marca);
		while ( fscanf(f, "%s %d %d %d", nome, &ano, &preco, &qtdade) != EOF ) {
			_insert_model_in_list(&(*node)->brand.models, nome, ano, preco, qtdade);
			(*node)->brand.qtdade_modelos++;
			(*node)->brand.valor_total += preco;
			(*node)->brand.total_carros += qtdade;
			store->total_carros += qtdade;
		}

		fclose(f);
		printf("\n  Arquivo '%s' foi carregado para a árvore!\n", filename);
	} else {
		printf("\n Erro: Não foi possível abrir o arquivo: '%s'!\n", filename);
	}
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


bool _insert_brand_in_tree(const char *nome, b_tree **root, char *position, b_tree *parent)
{
	if (*root == NULL) {
		b_tree *node = createBinaryNode(position, parent);
        bool inserted = false;

		if (node != NULL) {
			strcpy(node->brand.nome, nome);
			node->brand.qtdade_modelos = 0;
			node->brand.valor_total = 0;
			node->brand.models = NULL;

            inserted = true;

			char output[NOMEMAX*2 + 1];
			sprintf(output, "\n  Marca '%s' foi introduzida!\n", nome);
			animate(output, 10);
		} else {
            printf("\n Não foi possível alocar memória para inserir a marca '%s'\n", nome);
        }

		*root = node;
		return inserted;

	} else if (strcmp(nome, (*root)->brand.nome) < 0) { // LEFT
		return _insert_brand_in_tree(nome, &(*root)->left, L, *root);
	} else if (strcmp(nome, (*root)->brand.nome) > 0) { // RIGHT
		return _insert_brand_in_tree(nome, &(*root)->right, R, *root);
	} else {
		printf("\n Marca: '%s' já se encontra na árvore!\n", nome);
		return false;
	}
}


void insertBrand(const char *nome, STORE *store)
{
	if (_insert_brand_in_tree(nome, &store->root, "ROOT", NULL))
        store->total_marcas++;
}


b_tree **searchBrand(const char *nome, b_tree **root)
{
	if (root == NULL)
		return NULL;
	else if (strcmp(nome, (*root)->brand.nome) < 0)
		return searchBrand(nome, &(*root)->left);
	else if (strcmp(nome, (*root)->brand.nome) > 0)
		return searchBrand(nome, &(*root)->right);
	else
		return root;
}




void insertModel(char *nome, char *marca,
						int ano, int preco, int qtdade, STORE *store)
{
	b_tree **node = searchBrand(marca, &store->root);

	if (*node != NULL) {
		if (_insert_model_in_list(&(*node)->brand.models, nome, ano, preco, qtdade)) {
			(*node)->brand.qtdade_modelos++;
			(*node)->brand.valor_total += preco;
			store->total_carros += qtdade;
			printf("\n Modelo '%s' inserido na marca '%s'\n", nome, marca);
		} else {
			printf("\n Não foi possível inserir o modelo '%s' na marca '%s'\n", nome, marca);
		}
	} else {
		printf("\n Marca: '%s' não foi encontrada na árvore binária!", marca);
	}
}




void _inherit_position(b_tree *filho, b_tree *pai)
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


void removeBrand(b_tree **root, const char *marca)
{
	b_tree **brand = searchBrand(marca, root);
	if (*brand != NULL)
		removeBinaryNode(brand);
    else
        printf("\n Marca '%s' não foi encontrada ná árvore! Impossível eliminar.", marca);
}


void removeBinaryNode(b_tree **root)
{
	if (*root == NULL)
		return ;

	if ( (*root)->left == NULL && (*root)->right == NULL ) {
		freeModelList(&(*root)->brand.models);
		free(*root);
		*root = NULL;
	} else if ( (*root)->left != NULL && (*root)->right == NULL ) {
		b_tree *left = (*root)->left;
		_inherit_position(left, *root);

		freeModelList(&(*root)->brand.models);
		free(*root);
		*root = left;
	} else if ( (*root)->right != NULL && (*root)->left == NULL ) {
		b_tree *right = (*root)->right;
		_inherit_position(right, *root);

		freeModelList(&(*root)->brand.models);
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

		removeBinaryNode(tmp);
	}
}

