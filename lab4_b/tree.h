#ifndef TREE_H
#define TREE_H

typedef struct List List;

typedef struct TreeNode
{
    char *key;
    List *info;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
}
TreeNode;

typedef struct Tree
{
    TreeNode *root;
}
Tree;

void tree_create(Tree *);
void tree_destroy(Tree *);
int tree_search(Tree *, const char *, int, char **);
int tree_special(Tree *, const char *, int, char **);
void tree_insert(Tree *, const char *, const char *);
int tree_delete(Tree *, const char *, int);
void tree_walk(Tree *, const char *);
void tree_print(Tree *);
int tree_check(Tree *);

#endif