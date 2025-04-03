#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 10

typedef struct Item Item;

typedef struct Stack Stack;

Stack*init_stack();

int push(Stack*s, char*data);

char*pop(Stack*s);
 
int is_empty(Stack*s);

int count(Stack*s);

char*peek(Stack*s);

int clear_list(Stack*s);

#endif
