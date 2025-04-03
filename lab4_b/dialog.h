#ifndef DIALOG_H
#define DIALOG_H

typedef struct Tree Tree;

int dialog_menu(const char **, const int);
int dialog_insert(Tree *);
int dialog_delete(Tree *);
int dialog_search(Tree *);
int dialog_special(Tree *);
int dialog_walk(Tree *);
int dialog_print(Tree *);
int dialog_import(Tree *);

#endif