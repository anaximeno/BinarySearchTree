/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdbool.h>

#ifndef FOREST_H
#define FOREST_H


#define R "RIGHT"
#define L "LEFT"
#define DEPTH_MULTIPLIER 2

#define NOMEMAX 32


/* Retorna o nome sem a extensão. */
char *get_name_from_file(char *txtname);  /** TODO: transforma isso em split */


/** Estrutura de árvore binária, com os campos:
 *    -> parent (struct _binarytree *) : estrutura pai do nó atual
 *    -> left (struct _binarytree *) : estrutura do lado esquerdo
 *    -> right (struct _binarytree *) : estrutura do lado direita
 *    -> valor (int) : guarda um valor inteiro
 *    -> level (int) : nivel do nó na árvore
 *    -> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT"
 *    -> modelo (union struct _modelo) : estrutura que representa um modelo
 *    -> marca (union struct _marca) : estrutura que representa uma marca.
 * */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    char *position, *tipo;
    int level;

    union
    {
        struct _modelo
        {
            char nome[NOMEMAX];
            int ano, preco, qtdade;
        } modelo;
        struct _marca
        {
            char nome[NOMEMAX];
            int qtdade_modelos, valor_total;
            /* modelos aponta para uma árvore binária, 
               contendo todos os modelos dessa marca. */
            struct _binarytree *modelos;
        } marca;
    };
} b_tree;


/* Elimina um valor da árvore. */
void eliminateBinaryNode(int valor, b_tree **root);


/* Carrega um nó binário guardado no arquivo de nome [marca].txt com os elementos,
e retorna se conseguiu ou não carregar (bool).

Organização do arquivo a ser lido:
    [nome do modelo]    [ano de lançamento]     [preço]     [quantidate]

*/
bool charge_file(char *filename, b_tree **root);


/* Cria e retorna um nó binário. */
b_tree *createBinaryNode(char *position, b_tree *parent);


/* Insere uma nova marca caso não existir na árvore binária. */
void insertNewMarca(const char *nome, b_tree **root);
/* Insere recursivamente uma marca na árvore */
void _insert_marca_in_tree(const char *nome, b_tree **root, char *position,
    b_tree *parent);


/* Procura e retorna o indereço da Marca na árvore. */
b_tree *searchMarca(const char *nome, b_tree *root);


/* Insere um novo modelo caso não existir na árvore binária. */
void insertNewModelo(const char *nome, const char *marca, int ano,
    int preco, int qtdade, b_tree **root);
/* Função recursiva que insere um modelo no marca determinada.  */
void _insert_modelo_in_marca(const char *nome, int ano, int preco,
	int qtdade, b_tree **root, char *position, b_tree *parent);


/* Procura e retorna um modelo em na árvore que se encontra dentro de uma marca. */
b_tree *searchModelo(const char *nome, b_tree *marca_root);


/* Limpa recursivamente uma árvore binária. */
void freetree(b_tree **root);


#endif // FOREST_H
