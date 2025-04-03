#ifndef LIST_H
#define LIST_H

typedef struct ListNode
{
    char *data;
    struct ListNode *next;
}
ListNode;

typedef struct List
{
    ListNode *head;
    ListNode *tail;
}
List;

void list_create(List *);
void list_destroy(List *);
char *list_find(List *, int);
void list_insert(List *, const char *);
int list_delete(List *, int);
void list_print(List *);

#endif