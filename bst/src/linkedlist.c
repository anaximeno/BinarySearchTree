#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedlist.h"
/*  Guarda códigos de lista ligadas usadas no trabalho.
*
*   Apenas funções e/ou métodos utilizados no projeto foram
*   criados.
*/


linked *createList(int value)
{
    linked *tmp;
    tmp = (linked *) malloc(sizeof(linked));

    if (tmp != NULL) {
        tmp->value = value;
        tmp->next = NULL;
    }

    return tmp;
}


void insertInList(linked **list, int value)
{
    if (*list == NULL)
        *list = createList(value);
    else
        insertInList(&(*list)->next, value);
}


bool isInList(linked *list, int value)
{
    linked *node = list;

    while (node != NULL) {

        if (node->value == value)
            return true;

        node = node->next;
    }

    return false;
}


void freeList(linked **list)
{
    if (*list == NULL)
        return ;

    freeList(&(*list)->next);

    free(*list);
}
