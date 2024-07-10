#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/linkedlist.h"
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
    if (lista == NULL)
        return false;
    else if (lista->value == value)
        return true;
    else
        return isInNumberList(lista->next, value);
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

    if (node != NULL)
    {
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
    if (*root == NULL)
    {
        *root = createModelList(nome, ano, preco,  qtdade);
        return (bool) (*root != NULL);
    }
    else
    {
        return _insert_model_in_list(&(*root)->next, nome, ano, preco, qtdade);
    }
}


void removeModel(model_llist **head, const char *nome)
{
    if (!strcmp((*head)->nome, nome))
    {
        model_llist *next = (*head)->next;
        free(*head);
        *head = next;
    }
    else
    {
        removeModel(&(*head)->next, nome);
    }
}


void printModels(model_llist *head)
{
    model_llist *node = NULL;
    printf(" [");
    for (node=head ; node != NULL ; node=node->next)
        printf(" %s", node->nome);
    printf(" ]\n");
}


void listModels(model_llist *head)
{
    if (head == NULL)
        return ;

    printf("\n\n   # '%s'\n\t-> Ano : %d\n\t-> Preco : %d$00\n\t-> Quantidade : %d",
        head->nome, head->ano, head->preco, head->qtdade);

    listModels(head->next);
}


model_llist **searchModel(model_llist **head, const char *nome)
{
    if (*head == NULL)
        return NULL;
    else if (!strcmp(nome, (*head)->nome))
        return head;
    else
        return searchModel(&(*head)->next, nome);
}