#ifndef FUNC_H
#define FUNC_H

typedef struct KeySpace
{
        char *key;
        char *info;
        struct KeySpace *next;
}KeySpace;

typedef struct Table
{
        struct KeySpace *first;
        int ms;
        int cs;
}Table;

int init(Table*ptab, int sz);

char *getstr();

int is(Table *ptab, char*key);

KeySpace *get_element(Table *ptab, char *key);

int add(Table *ptab, char *key, char *info);

Table*ind_task(Table *ptab, char *kstart, char *kend);

int print_table(Table *ptab);

int clear_mem(Table *ptab);

int del(Table *ptab, char *key);

char*get_str_from_file(FILE*fp);

int import(Table* ptab, char*file);

#endif
