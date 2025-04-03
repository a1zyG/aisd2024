#ifndef FUNC_H
#define FUNC_H

typedef struct Connect Connect;

typedef struct Person Person;

typedef struct Gcom Gcom;

char *getstr();

Gcom*init_gcom();

int add_person(Gcom*g, char*name);

int is_adjacent(Gcom*g, int id1, int id2);

int add_connection(Gcom*g, char*name1, char*name2, int relation);

int delete_person(Gcom*g, char*name);

int delete_connection(Gcom*g, char*name1, char*name2);

int edit_name(Gcom*g, char*name, char*newname);

int edit_relation(Gcom*g, char*name1, char*name2, int relation);

int print_graph(Gcom*g);

int dfs_visit(Gcom*g, int id, int*col, int*pred);

int bypass_dfs(Gcom*g, char*name);

int shortest_path_djkstra(Gcom*g, char*from_name, char*to_name);

int find_kss(Gcom*g);

int clear_graph(Gcom*g);

#endif
