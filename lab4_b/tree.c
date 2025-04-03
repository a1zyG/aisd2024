#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "tree.h"

void tree_create(Tree *tree)
{
    tree->root = NULL;
}

void node_destroy(TreeNode *node)
{
    free(node->key);
    list_destroy(node->info);
    free(node->info);
    free(node);
}

void destroy(TreeNode *node)
{
    if (node == NULL)
        return;

    destroy(node->right);
    destroy(node->left);

    node_destroy(node);
}

void tree_destroy(Tree *tree)
{
    destroy(tree->root);
}

int tree_search(Tree *tree, const char *key, int version, char **info)
{
    TreeNode *ptr = tree->root;
    while (ptr != NULL)
    {
        int cmp = strcmp(key, ptr->key);
        if (cmp == 0)
        {
            *info = list_find(ptr->info, version);
            return (*info != NULL) ? 0 : 1;
        }

        ptr = cmp < 0 ? ptr->left : ptr->right;
    }

    return 1;
}

int tree_special(Tree *tree, const char *key, int version, char **info)
{
    TreeNode *ptr = tree->root;
    TreeNode *prev = NULL;
    while (ptr != NULL)
    {
        if (strcmp(ptr->key, key) > 0)
        {
            prev = ptr;
            ptr = ptr->left;
        }
        else
            ptr = ptr->right;
    }

    if (prev == NULL)
        return 1;

    *info = list_find(prev->info, version);

    return (*info != NULL) ? 0 : 1;
}

int height(TreeNode *node)
{
    return (node != NULL) ? node->height : 0;
}

int balance_factor(TreeNode *node)
{
    return (node != NULL) ? (height(node->left) - height(node->right)) : 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

TreeNode *rotate_left(TreeNode *node)
{
    TreeNode *right = node->right;
    node->right = right->left;
    right->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    right->height = max(height(right->left), height(right->right)) + 1;
    return right;
}

TreeNode *rotate_right(TreeNode *node)
{
    TreeNode *left = node->left;
    node->left = left->right;
    left->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    left->height = max(height(left->left), height(left->right)) + 1;
    return left;
}

TreeNode *insert(TreeNode *node, const char *key, const char *info)
{
    if (node == NULL)
    {
        node = calloc(1, sizeof(TreeNode));
        node->height = 1;
        node->key = strdup(key);
        node->info = calloc(1, sizeof(List));
        list_insert(node->info, info);
        return node;
    }

    int cmp = strcmp(key, node->key);
    if (cmp == 0)
    {
        list_insert(node->info, info);
        return node;
    }
    else if (cmp < 0)
        node->left = insert(node->left, key, info);
    else
        node->right = insert(node->right, key, info);

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = balance_factor(node);
    if (balance > 1)
    {
        if (strcmp(key, node->left->key) < 0)
            return rotate_right(node);
        else
        {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
    }
    else if (balance < -1)
    {
        if (strcmp(key, node->right->key) > 0)
            return rotate_left(node);
        else
        {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
    }

    return node;
}

void tree_insert(Tree *tree, const char *key, const char *info)
{
    tree->root = insert(tree->root, key, info);
}

void swap(TreeNode *node1, TreeNode *node2)
{
    char *tmp_key = node1->key;
    node1->key = node2->key;
    node2->key = tmp_key;

    List *tmp_info = node1->info;
    node1->info = node2->info;
    node2->info = tmp_info;
}

TreeNode *delete(TreeNode *node, const char *key, int version, int *status)
{
    if (node == NULL)
    {
        *status = 1;
        return NULL;
    }

    int cmp = strcmp(key, node->key);
    if (cmp == 0)
    {
        if (version != 0)
        {
            *status = list_delete(node->info, version);
            if (node->info->head != NULL)
                return node;
        }
        
        if (node->left == NULL)
        {
            TreeNode *tmp = node;
            node = node->right;
            node_destroy(tmp);
            return node;
        }
        else if (node->right == NULL)
        {
            TreeNode *tmp = node;
            node = node->left;
            node_destroy(tmp);
            return node;
        }
        else
        {
            TreeNode *tmp = node->right;
            while (tmp->left != NULL)
                tmp = tmp->left;
            swap(node, tmp);
            node->right = delete(node->right, key, 0, status);
        }
    }
    else if (cmp < 0)
        node->left = delete(node->left, key, version, status);
    else
        node->right = delete(node->right, key, version, status);

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = balance_factor(node);
    if (balance > 1)
    {
        if (balance_factor(node->left) >= 0)
            return rotate_right(node);
        else
        {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
    }
    else if (balance < -1)
    {
        if (balance_factor(node->right) <= 0)
            return rotate_left(node);
        else
        {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
    }

    return node;
}

int tree_delete(Tree *tree, const char *key, int version)
{
    int status = 0;
    tree->root = delete(tree->root, key, version, &status);
    return status;
}

void node_print(TreeNode *node)
{
    printf("\"%s\": {", node->key);
    list_print(node->info);
    printf("}\n");
}

void walk(TreeNode *node, const char *prefix)
{
    if (node == NULL)
        return;
    
    walk(node->right, prefix);

    if (strncmp(node->key, prefix, strlen(prefix)) == 0)
        node_print(node);

    walk(node->left, prefix);
}

void tree_walk(Tree *tree, const char *prefix)
{
    walk(tree->root, prefix);
}

void print(TreeNode *node, int depth)
{
    if (node == NULL)
        return;

    print(node->right, depth + 1);

    for (int i = 0; i < depth; i++)
        printf("        ");
    node_print(node);

    print(node->left, depth + 1);
}

void tree_print(Tree *tree)
{
    print(tree->root, 0);
}

int check(TreeNode *node, int *height)
{
    if (node == NULL)
    {
        *height = 0;
        return 0;
    }

    int left_height;
    if (check(node->left, &left_height))
        return 1;

    int right_height;
    if (check(node->right, &right_height))
        return 1;

    if (abs(left_height - right_height) > 1)
        return 1;

    *height = max(left_height, right_height) + 1;

    return 0;
}

int tree_check(Tree *tree)
{
    int height;
    return check(tree->root, &height);
}
