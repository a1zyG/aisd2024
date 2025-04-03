#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void list_create(List *list)
{
    list->head = list->tail = NULL;
}

void list_destroy(List *list)
{
    ListNode *ptr = list->head, *prev;
    while (ptr != NULL)
    {
        prev = ptr;
        ptr = ptr->next;
        free(prev->data);
        free(prev);
    }
}

char *list_find(List *list, int version)
{
    ListNode *ptr = list->head;
    int cnt = 1;
    while (ptr != NULL && cnt != version)
    {
        ptr = ptr->next;
        cnt++;
    }

    if (ptr == NULL)
        return NULL;

    return ptr->data;
}

void list_insert(List *list, const char *data)
{
    ListNode *new = calloc(1, sizeof(ListNode));
    new->data = strdup(data);

    if (list->head == NULL)
        list->head = new;
    else
        list->tail->next = new;

    list->tail = new;
}

int list_delete(List *list, int version)
{
    ListNode *ptr = list->head, *prev = NULL;
    int cnt = 1;
    while (ptr != NULL && cnt != version)
    {
        prev = ptr;
        ptr = ptr->next;
        cnt++;
    }

    if (ptr == NULL)
        return 1;

    if (list->head == ptr)
        list->head = ptr->next;
    else
        prev->next = ptr->next;

    if (list->tail == ptr)
        list->tail = prev;

    free(ptr->data);
    free(ptr);

    return 0;
}

void list_print(List *list)
{
    ListNode *ptr = list->head;
    int cnt = 1;
    while (ptr != NULL)
    {
        printf("%d: \"%s\"", cnt, ptr->data);
        if (ptr->next != NULL)
            printf(", ");
        ptr = ptr->next;
        cnt++;
    }
}