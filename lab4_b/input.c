#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

int get_int(int *num, int min, int max, const char *prompt)
{
    int n = 0;
    do
    {
        printf("%s", prompt);

        n = scanf("%d", num);
        if (n < 0)
            return 1;
        
        if (n == 0)
            printf("Error! Try Again.\n");
        else if (*num < min || *num > max)
        {
            printf("Number is out of the range.\n");
            n = 0;
        }

        scanf("%*[^\n]");
        scanf("%*c");
    }
    while (n == 0);
    
    return 0;
}

char *get_str(const char *prompt)
{
    char *str = calloc(1, sizeof(char));
    char buf[81] = {0};
    int n = 0;
    int len = 0;

    printf("%s", prompt);
    
    do
    {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            free(str);
            return NULL;
        }

        if (n == 0)
            scanf("%*c");
        else
        {
            len += strlen(buf);
            str = realloc(str, len + 1);
            strcat(str, buf);
        }
    }
    while (n > 0);

    return str;
}

char *fget_str(FILE *fptr)
{
    char *str = calloc(1, sizeof(char));
    char buf[81] = {0};
    int n = 0;
    int len = 0;

    do
    {
        n = fscanf(fptr, "%80[^\n]", buf);
        if (n < 0)
        {
            free(str);
            return NULL;
        }

        if (n == 0)
            fscanf(fptr, "%*c");
        else
        {
            len += strlen(buf);
            str = realloc(str, len + 1);
            strcat(str, buf);
        }
    }
    while (n > 0);

    return str;
}