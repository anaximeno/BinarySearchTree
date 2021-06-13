#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdbool.h>
/* Guarda códigos de lista ligadas usadas no trabalho. */

/* Estrutura de lista ligada com os campos:
    -> next (struct _linkedlist *): próxima estrutura,
    -> value (int): valor do nó. */
typedef struct _linkedlist
{
    struct _linkedlist *next;
    int value;
} linked;

/* cria e retorna um nó de uma lista. */
linked *createList(int value);

/* insere um valor na lista. */
void insertInList(linked **list, int value);

/* retorna se um valor está ou não numa lista. */
bool isInList(linked *list, int value);

/* elimina (free) todos os nós de uma lista ligada. */
void freeList(linked **list);
#endif // LINKEDLIST_H
