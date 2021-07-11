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

	if (f != NULL)
	{
		char nome[NOMEMAX];
		int ano, preco, qtdade;

		char *marca = getName(filename);
		b_tree **node = searchBrand(marca, &store->root);


		/* Se a marca não for encontrada na arvore, cria nova árvore */
		if ( node == NULL )
		{
			insertBrand(marca, store, false);
			if ( (node = searchBrand(marca, &store->root)) == NULL )
			{
				printf("\n Erro: nao foi possivel criar marca '%s' na arvore!", marca);
				fclose(f);
				return ;
			}
		}

		/* Liberta a variável marca não mais necessária. */
		free(marca);
		while ( fscanf(f, "%s %d %d %d", nome, &ano, &preco, &qtdade) != EOF )
		{
			if(_insert_model_in_list(&(*node)->brand.models, nome, ano, preco, qtdade))
			{
                (*node)->brand.qtdade_modelos++;
                (*node)->brand.valor_total += preco*qtdade;
                (*node)->brand.total_carros += qtdade;
                store->total_modelos++;
			}
		}

		fclose(f);
		char output[NOMEMAX*4];
		sprintf(output, "\n  Arquivo '%s' foi carregado para a arvore!\n", filename);
		animate(output, 45);
	}
	else
	{
		printf("\n Erro: Nao foi possivel abrir o arquivo: '%s'!\n", filename);
	}
}


b_tree *createBinaryNode(char *position, b_tree *parent)
{
	b_tree *node = (b_tree *) malloc(sizeof(b_tree));

	if (node != NULL)
	{
		node->level = parent == NULL ? 0 : parent->level+1;
		node->left = node->right = NULL;
		node->parent = parent;
		node->position = position;
	}

	return node;
}


bool _insert_brand_in_tree(const char *nome, b_tree **root, char *position, b_tree *parent)
{
	if (*root == NULL)
	{
		b_tree *node = createBinaryNode(position, parent);
        bool inserted = false;

		if (node != NULL)
		{
			strcpy(node->brand.nome, nome);
			node->brand.qtdade_modelos = 0;
			node->brand.valor_total = 0;
			node->brand.total_carros = 0;
			node->brand.models = NULL;

            inserted = true;
		}
		else
		{
            printf("\n Nao foi possivel alocar memoria para inserir a marca '%s'\n", nome);
        }

		*root = node;
		return inserted;

	}
	else if (strcmp(nome, (*root)->brand.nome) < 0) // LEFT
	{
		return _insert_brand_in_tree(nome, &(*root)->left, L, *root);
	}
	else if (strcmp(nome, (*root)->brand.nome) > 0) // RIGHT
	{
		return _insert_brand_in_tree(nome, &(*root)->right, R, *root);
	}
	else
	{
		printf("\n Marca: '%s' ja se encontra na arvore!\n", nome);
		return false;
	}
}


void insertBrand(const char *nome, STORE *store, bool verbose)
{
	if (_insert_brand_in_tree(nome, &store->root, "ROOT", NULL))
	{
        store->total_marcas++;
        if (verbose == true)
		{
            char output[NOMEMAX*2 + 1];
            sprintf(output, "\n Marca '%s' foi introduzida!\n", nome);
            animate(output, 10);
        }
    }
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

	if (node != NULL)
	{
		if (_insert_model_in_list(&(*node)->brand.models, nome, ano, preco, qtdade))
		{
			(*node)->brand.qtdade_modelos++;
			(*node)->brand.valor_total += preco*qtdade;
			(*node)->brand.total_carros += qtdade;
			store->total_modelos++;
		}
		else
		{
			printf("\n Nao foi possivel inserir o modelo '%s' na marca '%s'\n", nome, marca);
		}
	}
	else
	{
		printf("\n Marca: '%s' nao foi encontrada na arvore binaria!", marca);
	}
}


bool saveBrandInFile(STORE store, char *nome_marca)
{
	b_tree **brand = searchBrand(nome_marca, &store.root);

	if(brand != NULL)
	{
        char nome[NOMEMAX];
        strcpy(nome, nome_marca);
		FILE *f = fopen(strcat(nome, ".txt"), "wt");

		if(f != NULL)
		{
			model_llist *node = (*brand)->brand.models;
			while(node != NULL)
			{
				fprintf(f, "%s	%d	%d	%d\n", node->nome, node->ano,
					node->preco, node->qtdade);
				node = node->next;
			}

			fclose(f);
			return true;
		}
		else
		{
			printf("\n Nao foi possivel criar arquivo para guardar!");
		}
	}
	else
	{
		printf("\n Marca: '%s' nao foi encontrada na arvore!", nome_marca);
	}

	return false;
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
	if (brand != NULL)
		removeBinaryNode(brand);
    else
        printf("\n Marca '%s' nao foi encontrada na arvore! Impossivel eliminar.", marca);
}


void removeBinaryNode(b_tree **root)
{
	if (*root == NULL)
		return ;

	if ( (*root)->left == NULL && (*root)->right == NULL )
	{
		freeModelList(&(*root)->brand.models);
		free(*root);
		*root = NULL;
	}
	else if ( (*root)->left != NULL && (*root)->right == NULL )
	{
		b_tree *left = (*root)->left;
		_inherit_position(left, *root);

		freeModelList(&(*root)->brand.models);
		free(*root);
		*root = left;
	}
	else if ( (*root)->right != NULL && (*root)->left == NULL )
	{
		b_tree *right = (*root)->right;
		_inherit_position(right, *root);

		freeModelList(&(*root)->brand.models);
		free(*root);
		*root = right;
	}
	else
	{
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


void _list_brands(b_tree *node)
{
	if (node == NULL)
        return ;

	printf("\n  %s %s (%d modelos) ", VERTICAL_BRANCH,
                node->brand.nome, node->brand.qtdade_modelos);

	_list_brands(node->left);
	_list_brands(node->right);
}


void listBrands(STORE *store)
{
	if (store->root != NULL)
	{
        printf("\n     %s%s%s", RIGHT_BRANCH, LINE_BRANCH, LINE_BRANCH);
		printf("\n  %s%s Marcas Disponiveis", MIDDLE_BRANCH, VERTICAL_BRANCH);
		printf("\n  %s %s%s%s", VERTICAL_BRANCH, LEFT_BRANCH, LINE_BRANCH, LINE_BRANCH);
		_list_brands(store->root);
		printf("\n  %s%s%s\n", MIDDLE_BRANCH, LINE_BRANCH, LINE_BRANCH);
	}
}
