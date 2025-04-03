#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Connect
{
	int from;
	int to;
	int relation;
	struct Connect*next;
}Connect;

typedef struct Person
{
	char*name;
	Connect*con;
}Person;

typedef struct Gcom
{
	int size;
	Person*persons;
}Gcom;

char *getstr(){
        char *ptr = (char*)malloc(1);
        char buf[81];
        int n, len = 0;
        *ptr = '\0';
        do{
                n = scanf("%80[^\n]", buf);
                if (n < 0){
                        free(ptr);
                        ptr = NULL;
                        continue;
                }
                if(n == 0)
                        scanf("%*c");
                else{
                        len += strlen(buf);
                        ptr = (char*)realloc(ptr, len+1);
                        strcat(ptr, buf);
                }
        }while(n > 0);

        return ptr;
}

Gcom*init_gcom()
{
	return calloc(1, sizeof(Gcom));
} 

int add_person(Gcom*g, char*name)
{
	if(!g)
		return 1;
	for(int i=0; i<g->size; i++)
		if(strcmp(name, g->persons[i].name) == 0)
			return 1;
	g->size++;
	g->persons = realloc(g->persons, sizeof(Person)*g->size);
	g->persons[g->size-1].name = strdup(name);
	g->persons[g->size-1].con = NULL;
	return 0;
}

int is_adjacent(Gcom*g, int id1, int id2)
{
	Connect*cur = g->persons[id1].con;
	while(cur)
	{
		if(cur->to == id2)
			return 1;
		cur = cur->next;
	}
	return 0;
}

int add_connection(Gcom*g, char*name1, char*name2, int relation)
{
	if(!g)
		return 1;
	if(relation>10 || relation<-10)
		return 2;
	int id1 = -1, id2 = -1;
	for(int i=0; i<g->size; i++)
	{
		if(strcmp(g->persons[i].name, name1) == 0)
			id1 = i;
		if(strcmp(g->persons[i].name, name2) == 0)
			id2 = i;
	}
	if(id1 == -1 || id2 == -1)
		return 3;

	if(is_adjacent(g, id1, id2))
		return 4;
		
	Connect*con = malloc(sizeof(Connect));
	con->next = g->persons[id1].con;
	g->persons[id1].con = con;
	con->from = id1;
	con->to = id2;
	con->relation = relation;

	con = malloc(sizeof(Connect));
	con->next = g->persons[id2].con;
	g->persons[id2].con = con;
	con->from = id2;
	con->to = id1;
	con->relation = relation;
	return 0;
}

int delete_person(Gcom*g, char*name)
{
	if(!g)
		return 1;
	int id = -1;
	for(int i=0; i<g->size; i++)
		if(strcmp(g->persons[i].name, name) == 0)
			id = i;
	if(id == -1)
		return 3;
	Connect*del;
	Connect*cur = g->persons[id].con;
	while(cur)
	{
		Connect*prev = NULL;
		Connect*tmp = g->persons[cur->to].con;
		while(tmp)
		{
			if(tmp->to == id)
			{
				if(prev)
					prev->next = tmp->next;
				else
					g->persons[cur->to].con = tmp->next;
				free(tmp);
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		del = cur;
		cur = cur->next;
		free(del);
	}

	free(g->persons[id].name);
	for(int i=0; i<g->size-1; i++)
	{
		if(i>=id)
			g->persons[i] = g->persons[i+1];
		Connect*tmp = g->persons[i].con;
		while(tmp)
		{
			if(tmp->to > id)
				tmp->to--;
			if(tmp->from > id)
				tmp->from--;
			tmp = tmp->next;
		}
	}
	g->size--;
	g->persons = realloc(g->persons, sizeof(Person)*g->size);
	
	return 0;
}

int delete_connection(Gcom*g, char*name1, char*name2)
{
	if(!g)
		return 1;
	int id1 = -1, id2 = -1;
	for(int i=0; i<g->size; i++)
	{
		if(strcmp(g->persons[i].name, name1) == 0)
			id1 = i;
		if(strcmp(g->persons[i].name, name2) == 0)
			id2 = i;
	}
	if(id1 == -1 || id2 == -1)
		return 3;

	if(!is_adjacent(g, id1, id2))
		return 5;

	Connect*prev = NULL;
	Connect*cur = g->persons[id1].con;
	while(cur)
	{
		if(cur->to == id2)
		{
			if(prev)
				prev->next = cur->next;
			else
				g->persons[id1].con = cur->next;
			free(cur);
			break;
		}
	}

	prev = NULL;
	cur = g->persons[id2].con;
	while(cur)
	{
		if(cur->to == id1)
		{
			if(prev)
				prev->next = cur->next;
			else
				g->persons[id2].con = cur->next;
			free(cur);
			break;
		}
	}
	
	return 0;
}

int edit_name(Gcom*g, char*name, char*newname)
{
	if(!g)
		return 1;
	for(int i=0; i<g->size; i++)
		if(strcmp(g->persons[i].name, name) == 0)
		{
			free(g->persons[i].name);
			g->persons[i].name = strdup(newname);
			return 0;
		}
	return 3;
}

int edit_relation(Gcom*g, char*name1, char*name2, int relation)
{
	if(!g)
		return 1;
	if(relation>10 || relation<-10)
		return 2;
	int id1 = -1, id2 = -1;
	for(int i=0; i<g->size; i++)
	{
		if(strcmp(g->persons[i].name, name1) == 0)
			id1 = i;
		if(strcmp(g->persons[i].name, name2) == 0)
			id2 = i;
	}
	if(id1 == -1 || id2 == -1)
		return 3;

	if(!is_adjacent(g, id1, id2))
		return 5;
	Connect*cur = g->persons[id1].con;
	while(cur)
	{
		if(cur->to == id2)
			cur->relation = relation;
		cur = cur->next;
	}
	cur = g->persons[id2].con;
	while(cur)
	{
		if(cur->to == id1)
			cur->relation = relation;
		cur = cur->next;
	}
	return 0;
}

int print_graph(Gcom*g)
{
	if(!g)
		return 1;
	for(int i=0; i<g->size; i++)
	{
		printf("%s", g->persons[i].name);
		Connect*cur = g->persons[i].con;
		while(cur)
		{
			printf(" -|%d|-> %s",cur->relation , g->persons[cur->to].name);
			cur = cur->next;
		}
		printf("\n");
	}
	return 0;
}

int dfs_visit(Gcom*g, int id, int*col, int time, int*openTime, int*closeTime)
{
	col[id]++;
	time++;
	openTime[id] = time;
	Connect*edge = g->persons[id].con;
	while(edge)
	{
		if(edge->relation >= 0 && col[edge->to] == 0)
		{
			dfs_visit(g, edge->to, col, time, openTime, closeTime);
		}
		edge = edge->next;
	}
	col[id]++;
	time++;
	closeTime[id] = time;
}

int bypass_dfs(Gcom*g, char*name) // возвращает цепочку вершин  обход в глубину
{
	if(!g)
		return 1;
	int id = -1;
	for(int i=0; i<g->size; i++)
		if(strcmp(g->persons[i].name, name) == 0)
		{
			id = i;
			break;
		}
	if(id == -1)
		return 3;

	int *col = calloc(g->size, sizeof(int));
	int time = 0;
	int *openTime = malloc(sizeof(int)*g->size);
	int *closeTime = malloc(sizeof(int)*g->size);
	
	for(int i=0; i<g->size; i++){
		openTime[i] = -1;
		closeTime[i] = -1;
	}

	dfs_visit(g, id, col, time, openTime, closeTime);
			
	printf("Potential friend for %s:\n", name);
	for(int i=0; i<g->size; i++)
	{
		if(i != id && closeTime[i] != -1)
			printf("%s\n", g->persons[i].name);
	}
	printf("\n");
	
	free(col);
	free(openTime);
	free(closeTime);
	return 0;
}

int shortest_path_djkstra(Gcom*g, char*from_name, char*to_name)
{
	if(!g)
		return 1;
	int from = -1, to = -1;
	for(int i=0; i<g->size; i++)
	{
		if(strcmp(g->persons[i].name, from_name) == 0)
			from = i;
		if(strcmp(g->persons[i].name, to_name) == 0)
			to = i;
	}
	if(from == -1 || to == -1)
		return 3;

	int*d = calloc(g->size, sizeof(int));
	int*pred = calloc(g->size, sizeof(int));
	int*S = calloc(g->size, sizeof(int));
	
	for(int i=0; i<g->size; i++)
	{
		d[i] = INF;
		pred[i] = -1;
		S[i] = 0;
	}
	d[from] = 0;
	
	for(int i=0; i<g->size; i++)
	{
		int min = INF;
		int x;
		for(int j=0; j<g->size; j++)
		{
			if(S[j] == 0 && d[j]<=min)
			{
				min = d[j];
				x = j;
			}
		}
		S[x] = 1;
		Connect*edge = g->persons[x].con;
		while(edge)
		{
			if(edge->relation > 0 && d[edge->to] > d[edge->from] + edge->relation)
			{
				d[edge->to] = d[edge->from] + edge->relation;
				pred[edge->to] = edge->from;
			}
			edge = edge->next;
		}
	}
	
	if(d[to] == INF)
	{
		printf("No chain!\n");
	}
	else
	{
		int last = to;
		while(last != -1)
		{
			printf("%s", g->persons[last].name);
			if(pred[last] != -1)
				printf("<--");
			last = pred[last];
		}
		printf("\n");
	}
	free(d);
	free(pred);
	free(S);
	return 0;
}

int find_kss(Gcom*g)//всевозможные цепочки
{
	if(!g || g->size == 0)
		return 6;
	int id;
	int flag = g->size;
	int *used = calloc(g->size, sizeof(int));
	printf("Components:\n");
	while(flag > 0)
	{
		for(int i=0; i<g->size; i++)
			if(used[i] == 0)
			{
				id = i;
				flag--;
				used[id] = 1;
				break;
			}
		int *col = calloc(g->size, sizeof(int));
		int time = 0;
		int *openTime = malloc(sizeof(int)*g->size);
		int *closeTime = malloc(sizeof(int)*g->size);
		for(int i=0; i<g->size; i++){
			openTime[i] = -1;
			closeTime[i] = -1;
		}

		dfs_visit(g, id, col, time, openTime, closeTime);
		
		for(int i=0; i<g->size; i++)
		{
			if(closeTime[i] != -1){
				printf("%s, ", g->persons[i].name);
				used[i] = 1;
				flag--;
			}
		}
		printf(";\n");
		free(col);
		free(openTime);
		free(closeTime);
	}
	free(used);
	return 0;
}

int clear_graph(Gcom*g)
{
	if(!g)
		return 0;
	for(int i=0; i<g->size; i++)
	{
		free(g->persons[i].name);
		Connect*ptr = g->persons[i].con;
		while(ptr)
		{
			Connect*pred = ptr;
			ptr= ptr->next;
			free(pred);
		}
	}
	free(g->persons);
	free(g);
	return 0;
}
