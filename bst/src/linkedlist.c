#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedlist.h"
/*  Guarda códigos de lista ligadas usadas no trabalho.

    Apenas funções e/ou métodos utilizados no projeto foram
    criados.
*/


linked *createlist(int value)
{
    linked *tmp;
    tmp = (linked *) malloc(sizeof(linked));

    if (tmp != NULL) {
        tmp->value = value;
        tmp->next = NULL;
    }

    return tmp;
}


void insert_in_list(linked **list, int value)
{
    if (*list == NULL)
        *list = createlist(value);
    else
        insert_in_list(&(*list)->next, value);
}


bool is_in_list(linked *list, int value)
{
    linked *node = list;

    while (node != NULL) {

        if (node->value == value)
            return true;

        node = node->next;
    }

    return false;
}


void cleanlist(linked **list)
{
    if (*list == NULL)
        return ;

    cleanlist(&(*list)->next);

    free(*list);
}
