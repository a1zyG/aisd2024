#ifndef FUNC_H
#define FUNC_H

typedef struct Node{
        char *key;
        int info;
        struct Node*right;
        struct Node*left;
}Node;

typedef struct Tree
{
        Node*root;
}Tree;

char *getstr();

int Insert(Tree *tree, const char* key, const int info);

Node** Find(Tree*tree, char*key, int*count);

Node*Get_Parent(Tree*tree, Node*x);

int Erase(Tree*tree, char*key, int release);

void Show_Tree(Node*n, int level);

char*get_str_from_file(FILE*fp);

int Import(Tree* tree, char*file);

int Bypass(Node*n);

Node**Individual_Find(Tree*tree, char*max, int*count);

int Print_Nodes(Node**n, int*count);

int Clear_Tree(Node*root);

int Timing_Find();

int Timing_Insert();

int Timing_Erase();

#endif
