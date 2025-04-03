#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

typedef struct Item
{
    char*data;
}Item;

typedef struct Stack
{
    int top;
    int size;
    Item*items;
}Stack;

Stack*init_stack()
{
    Stack*st = malloc(sizeof(Stack));
    st->top = 0; // top = 0
    st->items = malloc(sizeof(Item)*STACK_SIZE);
    st->size = STACK_SIZE;

    return st;
}

int push(Stack*s, char*data)
{
    if(!s)
    {
        return 1;
    }
    if(s->top == s->size-1)
    {
        printf("stack overflow\n");
        return 2;
    }
    s->items[s->top].data = malloc(sizeof(char)*(strlen(data)+1));
    strcpy(s->items[s->top].data, data);
    s->top++;
    return 0;
}

char*pop(Stack*s)
{
    if(s->top==0)
    {
        return NULL;
    }
    s->top--;
    char*res = malloc(sizeof(char)*(strlen(s->items[s->top].data)+1));
    strcpy(res, s->items[s->top].data);
    free(s->items[s->top].data);
    return res;
}

char*peek(Stack*s)
{
    return s->items[s->top].data;
}

int is_empty(Stack*s)
{
    if(s->top == 0)
        return 1;
    else
        return 0;
}

int count(Stack*s)
{
	return s->top;
}

int clear_list(Stack*s)
{
        if(s->top==0)
        {
        		free(s->items);
        		free(s);
                return 1;
        }
        while(s->top!=0)
        {
        		s->top--;
                free(s->items[s->top].data);
        }
        free(s->items);
        free(s);
        return 0;
}
