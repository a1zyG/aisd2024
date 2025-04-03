#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

int infix_expression(char *prefix);

int get_str(char**str);

int main()
{
    while(1)
    {
        char*str;
        int i;
        printf("Enter slove:\n");
        i = get_str(&str);
        if(i==-1)
        	break;
        else
        {
            infix_expression(str);
        }
	free(str);
    }
}

int infix_expression(char *prefix)
{
    int len = strlen(prefix);
    Stack *s = init_stack();
    int check;
    for (int i = len - 1; i >= 0; i--) {
        if(!( ((int)prefix[i]>=65 && (int)prefix[i]<=90) || ((int)prefix[i]>=97 && (int)prefix[i]<=122) || ((int)prefix[i]==42) || ((int)prefix[i]==43) || ((int)prefix[i]==45) || ((int)prefix[i]==47)))
        {
            printf("Error 1!\n");
            clear_list(s);
            return 1;
        }
        if (isalpha(prefix[i])) {
            char operand[100];
            operand[0] = prefix[i];
            operand[1] = '\0';
            check = push(s, operand);
        } else {
            if(count(s)<2)
            {
                printf("Error 2!\n");
                clear_list(s);
                return 2;
            }
            char *op1 = pop(s);
            char *op2 = pop(s);
            char pr = prefix[i];
            char*expr = malloc(sizeof(char)*(strlen(op1)+strlen(op2)+4));
            strcpy(expr, "(");
            strcat(expr, op1);
            strcat(expr, &pr);
            strcat(expr, op2);
            strcat(expr, ")");
            check = push(s, expr);
            free(expr);
            free(op1);
            free(op2);
            }
        if(check == 2)
        {
            clear_list(s);
            return -1;
        }
    }
    char*res = pop(s);
    if(!is_empty(s))
    {
        printf("Error 2!\n");
        free(res);
        clear_list(s);
        return 2;
    }
    printf("Infix expression: %s\n", res);
    free(res);
    clear_list(s);
    return 0;
}

int get_str(char**str)
{
    (*str) = malloc(sizeof(char));
    (*str)[0]='\0';
    char buffer[101]={'\0'};
    int length=1;
    int i;
    do
    {
        i = scanf("%100[^\n]", buffer);

        if(i == -1)
        {
            free(*str);
            return -1;
        }
        else if(i == 0)
        {
            scanf("%*c");
            return 0;
        }
        else if(i == 1)
        {
            length = length + strlen(buffer);
            (*str) = realloc((*str), sizeof(char)*length);
            strcat((*str), buffer);
        }
    }while(i==1);
    return 1;
}
