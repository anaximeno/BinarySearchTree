#ifndef LINKEDLIST_H
#define LINKEDLIST_H
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
linked *createlist(int value);

/* insere um valor na lista. */
void insert_in_list(linked **list, int value);

/* retorna se um valor está ou não numa lista. */
bool is_in_list(linked *list, int value);

/* elimina (free) todos os nós de uma lista ligada. */
void cleanlist(linked **list);
#endif // LINKEDLIST_H
