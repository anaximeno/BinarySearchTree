/**
 * Guarda códigos de árvores binárias de pesquisa usadas no trabalho.
*/
#include <stdbool.h>

#ifndef FOREST_H
#define FOREST_H


#define R "RIGHT"
#define L "LEFT"
#define DEPTH_MULTIPLIER 2


/* Estrutura de árvore binária, com os campos:
 *    -> parent (struct _binarytree *) : estrutura pai do nó atual
 *    -> left (struct _binarytree *) : estrutura do lado esquerdo
 *    -> right (struct _binarytree *) : estrutura do lado direita
 *    -> valor (int) : guarda um valor inteiro
 *    -> level (int) : nivel do nó na árvore
 *    -> position (char *) : posicao da árvore pode ser "RIGHT", "LEFT" ou "ROOT" */
typedef struct _binarytree
{
    struct _binarytree *parent, *left, *right;
    int valor, level;
    char *position;
    // TODO: criar mais campos!
} btree;


/* Ponteiro para árvore binária. */
typedef btree* broot;


/* Cria um nó da árvore binária. */
btree *createBinaryNode(int valor, char *position, int level, btree *parent);



/* Insere um valor na árvore binária. */
void insertInTree(broot *root, int valor);


/* Procura por um valor e retorna o nó que contém esse valor */
void searchInTree(btree *root, int valor);


/* Salva a árvore num arquivo. */
void saveTreeOnFile(btree *root, const char *filename);


/* Salva um nó binário num arquivo. */
void saveBinaryNodeOnFile(btree *node, const char *filename);


/* Elimina um valor da árvore. */
void eliminateBinaryNode(int valor, broot *root);


/* Carrega um nó binário guardado no arquivo. */
struct _binarytree *chargeFile(const char filename);


/* Limpa recursivamente uma árvore binária. */
void freeTree(broot *root);


#endif // FOREST_H
