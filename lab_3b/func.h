#ifndef FUNC_H
#define FUNC_H

typedef struct KeySpace
{
        int offset;
        int klen;
        int ilen;
        struct KeySpace*next;
}KeySpace;

typedef struct Table
{
        int ms;
        int cs;
        KeySpace*first;
        FILE*fd;
}Table;

char *getstr();

int clear_mem(Table*ptab);

int save(Table*ptab);

int create(Table*ptab, char*filename, int size);

int load(Table*ptab, char*filename);

int is(Table *ptab, char *key);

KeySpace *get_element(Table *ptab, char *key);

int add(Table*ptab, char*key, char*info);

int print_table(Table*ptab);

int print_element(Table*ptab, KeySpace*el);

int del(Table*ptab, char* key);

Table *ind_task(Table *ptab, char*kstart, char*kend);

char*get_str_from_file(FILE*fp);

int import(Table* ptab, char*file);

#endif
