#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdbool.h>
#include "common.h"


/* Guarda códigos de lista ligadas usadas no trabalho. */

/* Estrutura de lista ligada com os campos:
    -> next (struct _linkedlist *): próxima estrutura,
    -> value (int): valor do nó. */
typedef struct _numbered_linkedlist
{
    struct _numbered_linkedlist *next;
    int value;
} linked_number;


/* Estrutura de lista ligadas que representam um modelo de carro.

Tem os campos:
    -> next (struct _linkedModel *) : proximo nó da lista,
    -> nome (char []) : nome do modelo,
    -> ano (int) : ano de lançamento do modelo,
    -> preco (int) : preço do modelo,
    -> qtdade (int) : quantidade de carros desse modelo. */
typedef struct _linkedModel
{
    struct _linkedModel *next;
    char nome[NORMAL_STRING_SIZE];
    int ano, preco, qtdade;
} model_llist;


/* cria e retorna um nó de uma lista. */
linked_number *createNumberList(int value);

/* insere um valor na lista. */
void insertInNumberList(linked_number **lista, int value);

/* retorna se um valor está ou não numa lista. */
bool isInNumberList(linked_number *lista, int value);

/* elimina (free) todos os nós de uma lista ligada. */
void freeNumberList(linked_number **lista);


/* Cria e retorna um nó da lista de modelo. */
model_llist *createModelList(char *nome, int ano, int preco, int qtdade);


/* Tenta inserir um modelo numa lista e retorna bool. */
bool _insert_model_in_list(model_llist **root, char *nome, int ano, int preco, int qtdade);


/* Remove um modelo da lista. */
void removeModel(model_llist **root, const char *nome);


/* Liberta a memória usada para alocar a lista de modelos. */
void freeModelList(model_llist **root);


/* Mostra a lista de modelos. */
void printModels(model_llist *root);


/* Mostra listado todos os modelos de uma Marca. */
void listModels(model_llist *head);


/* Procura e retorna o nó do modelo a pesquisar. */
model_llist **searchModel(model_llist **head, const char *nome);
#endif // LINKEDLIST_H


