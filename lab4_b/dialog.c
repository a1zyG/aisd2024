#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "input.h"
#include "tree.h"
#include "dialog.h"

int dialog_menu(const char **menu, const int len)
{
    for (int i = 0; i < len; ++i)
        printf("%d. %s\n", i, menu[i]);

    int opt;
    if (get_int(&opt, 0, len - 1, "Choose menu option: "))
        opt = 0;

    return opt;
}

int dialog_insert(Tree *tree)
{
    char *key = get_str("Enter key: ");
    if (key == NULL)
        return 1;

    char *info = get_str("Enter info: ");
    if (info == NULL)
    {
        free(key);
        return 1;
    }

    tree_insert(tree, key, info);

    free(key);
    free(info);

    return 0;
}

int dialog_delete(Tree *tree)
{
    char *key = get_str("Enter key: ");
    if (key == NULL)
        return 1;

    int version;
    if (get_int(&version, 1, INT_MAX, "Enter version: "))
    {
        free(key);
        return 1;
    }

    if (tree_delete(tree, key, version))
        printf("Not found.\n");

    free(key);

    return 0;
}

int dialog_search(Tree *tree)
{
    char *key = get_str("Enter key: ");
    if (key == NULL)
        return 1;

    int version;
    if (get_int(&version, 1, INT_MAX, "Enter version: "))
    {
        free(key);
        return 1;
    }

    char *info;
    if (tree_search(tree, key, version, &info))
        printf("Not found.\n");
    else
        printf("Found: \"%s\"\n", info);
    
    free(key);

    return 0;
}

int dialog_special(Tree *tree)
{
    char *key = get_str("Enter key: ");
    if (key == NULL)
        return 1;

    int version;
    if (get_int(&version, 1, INT_MAX, "Enter version: "))
    {
        free(key);
        return 1;
    }

    char *info;
    if (tree_special(tree, key, version, &info))
        printf("Not found.\n");
    else
        printf("Found: \"%s\"\n", info);
    
    free(key);

    return 0;
}

int dialog_walk(Tree *tree)
{
    char *prefix = get_str("Enter prefix: ");
    if (prefix == NULL)
        return 1;

    tree_walk(tree, prefix);

    free(prefix);

    return 0;
}

int dialog_print(Tree *tree)
{
    tree_print(tree);
    if (tree_check(tree))
        printf("Tree is not valid.\n");

    return 0;
}

int dialog_import(Tree *tree)
{
    char *fname = get_str("Enter file name: ");
    if (fname == NULL)
        return 1;

    FILE *fptr = fopen(fname, "r");
    free(fname);
    if (fptr == NULL)
    {
        printf("Not found.\n");
        return 0;
    }

    for (;;)
    {
        char *key = fget_str(fptr);
        if (key == NULL)
            break;

        char *info = fget_str(fptr);
        if (info == NULL)
        {
            free(key);
            break;
        }

        tree_insert(tree, key, info);

        free(key);
        free(info);
    }
    fclose(fptr);

    return 0;
}