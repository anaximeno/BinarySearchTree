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


void freeModelList(model_llist **root)
{
    if (*root == NULL)
        return ;

    freeModelList(&(*root)->next);
    free(*root);
    *root = NULL;
}


linked_number *createNumberList(int value)
{
    linked_number *tmp;
    tmp = (linked_number *) malloc(sizeof(linked_number));

    if (tmp != NULL) {
        tmp->value = value;
        tmp->next = NULL;
    }

    return tmp;
}


void insertInNumberList(linked_number **lista, int value)
{
    if (*lista == NULL)
        *lista = createNumberList(value);
    else
        insertInNumberList(&(*lista)->next, value);
}


bool isInNumberList(linked_number *lista, int value)
{
    linked_number *node = lista;

    while (node != NULL) {

        if (node->value == value)
            return true;

        node = node->next;
    }

    return false;
}


void freeNumberList(linked_number **lista)
{
    if (*lista == NULL)
        return ;

    freeNumberList(&(*lista)->next);

    free(*lista);
}


model_llist *createModelList(char *nome, int ano, int preco, int qtdade)
{
    model_llist *node = (model_llist *) malloc(sizeof(model_llist));

    if (node != NULL) {
        strcpy(node->nome, nome);
        node->ano = ano;
        node->preco = preco;
        node->qtdade = qtdade;
        node->next = NULL;
    }

    return node;
}


bool _insert_model_in_list(model_llist **root, char *nome, int ano, int preco, int qtdade)
{
    if (*root == NULL) {
        *root = createModelList(nome, ano, preco,  qtdade);
        return *root != NULL ? true : false;
    } else {
        return _insert_model_in_list(&(*root)->next, nome, ano, preco, qtdade);
    }
}


void removeModel(model_llist **root, const char *nome)
{
    if (!strcmp((*root)->nome, nome)) {
        model_llist *next = (*root)->next;
        free(*root);
        *root = next;
    } else {
        removeModel(&(*root)->next, nome);
    }
}


void printModels(model_llist *root)
{
    model_llist *node = NULL;
    printf(" [");
    for (node=root ; node != NULL ; node=node->next)
        printf(" %s", node->nome);
    printf(" ]\n");
}


void listModels(model_llist *head)
{
    if (head == NULL)
        return ;

    printf("\n\n   # '%s' - Ano : %d - Preco : %d$00 - Quantidade : %d",
        head->nome, head->ano, head->preco, head->qtdade);

    listModels(head->next);
}


model_llist **searchModel(model_llist **head, const char *nome)
{
    if (*head == NULL)
        return head;
    else if (!strcmp(nome, (*head)->nome))
        return head;
    else
        return searchModel(&(*head)->next, nome);
}