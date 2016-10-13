#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "list.h"

static node_t *node_new(val_t val, node_t *next)
{
    /* allocate node */
    node_t *node = malloc(sizeof(node_t));
    node->data = val;
    node->next = next;
    return node;
}

void node_free(node_t *the_node)
{
    free(the_node);
}

llist_t *list_new()
{
    /* allocate list */
    llist_t *list = malloc(sizeof(llist_t));
    list->head = NULL;
    list->size = 0;
    return list;
}


void list_free(llist_t *the_list)
{
    free(the_list->head);
    free(the_list);
}


/*
 * list_add inserts a new node with the given value val in the list and return the length of list
 * (if the value was absent) or does nothing (if the value is already present).
 */
int list_add(llist_t *list, val_t val)
{
    node_t *e = node_new(val, NULL);
    e->next = list->head;
    list->head = e;
    list->size++;
    return list->size;
}

/*
 * get the node specify by index
 * if the index is out of range, it will return NULL
 */
node_t *list_get(llist_t *list, uint32_t idx)
{
    if (idx > list->size)
        return NULL;
    node_t *head = list->head;
    while (idx--)
        head = head->next;
    return head;
}

void list_print(llist_t *list)
{
    node_t *cur = list->head;
    /* FIXME: we have to validate the sorted results in advance. */
    printf("\nsorted results:\n");
    while (cur) {
        printf("[%ld] ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

entry *findName(char lastname[], entry *pHead)
{
    size_t len = strlen(lastname);
    while (pHead != NULL) {
        if (strncasecmp(lastname, pHead->lastName, len) == 0
                && (pHead->lastName[len] == '\n' ||
                    pHead->lastName[len] == '\0')) {
            pHead->lastName = (char *) malloc(sizeof(char) *
                                              MAX_LAST_NAME_SIZE);
            memset(pHead->lastName, '\0', MAX_LAST_NAME_SIZE);
            strcpy(pHead->lastName, lastname);
            pHead->dtl = (pdetail) malloc(sizeof(detail));
            return pHead;
        }
        dprintf("find string = %s\n", pHead->lastName);
        pHead = pHead->pNext;
    }
    return NULL;
}
