#include <stdlib.h>
#include "tree.h"
#include "dialog.h"

int main()
{
    const char *menu[] =
    {
        "Quit",
        "Insert",
        "Delete",
        "Search",
        "Special",
        "Walk",
        "Print",
        "Import"
    };

    const int len = sizeof(menu) / sizeof(menu[0]);
    
    int (*fptr[])(Tree *) =
    {
        NULL,
        dialog_insert,
        dialog_delete,
        dialog_search,
        dialog_special,
        dialog_walk,
        dialog_print,
        dialog_import
    };

    Tree tree;
    tree_create(&tree);

    int opt;
    while ((opt = dialog_menu(menu, len)))
        if (fptr[opt](&tree))
            break;

    tree_destroy(&tree);

    return 0;
}