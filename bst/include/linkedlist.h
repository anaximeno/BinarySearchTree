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


typedef struct _model_linkedlist
{
    struct _model_linkedlist *next;
    char nome[NOMEMAX];
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


void insertModelInList(model_llist **root, char *nome, int ano, int preco, int qtdade);


void removeModel(model_llist **root, const char *nome);


void freeModelList(model_llist **root);


void mostra_modelos(model_llist *root);
#endif // LINKEDLIST_H


