#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

typedef struct Item
{
    char*data;
    struct Item*prev;
}Item;

typedef struct Stack
{
    Item*head;
}Stack;

Stack* init_stack()
{
	Stack*st = (Stack*)malloc(sizeof(Stack));
    st->head = NULL;
    return st;
}

int push(Stack*s, char*data)
{
    if(!s)
    {
        return 1;
    }
    Item*new = malloc(sizeof(Item));
    new->data = malloc(sizeof(char)*(strlen(data)+1));
    strcpy(new->data, data);
    new->prev = s->head;
    s->head = new;
    return 0;
}

char*pop(Stack*s)
{
    if(!s->head)
    {
        return NULL;
    }
    char*res = malloc(sizeof(char)*(strlen(s->head->data)+1));
    strcpy(res, s->head->data);
    Item*rm = s->head;
    s->head = s->head->prev;
    free(rm->data);
    free(rm);
    return res;
}

int is_empty(Stack*s)
{
    if(s->head == NULL)
        return 1;
    else
        return 0;
}

char*peek(Stack*s)
{
    return s->head->data;
}

int count(Stack*s)
{
	int n=0;
	for(Item*t = s->head; t; t=t->prev)
	{
		n++;
	}
	return n;
}

int clear_list(Stack*s)
{
        if(!s)
        {
        		free(s);
                return 1;
        }
        Item*rm = s->head;
        Item*buf;
        while(rm!=NULL)
        {
                buf = rm;
                rm = rm->prev;
                free(buf->data);
                free(buf);
        }
        free(s);
        return 0;
}
