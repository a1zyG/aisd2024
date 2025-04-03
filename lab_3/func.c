#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int init(Table*ptab, int sz)
{
	ptab->first = NULL;
	ptab->ms = sz;
	ptab->cs = 0;
}

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

int is(Table *ptab, char*key)
{
	if(ptab->cs == 0)
	{
		return 0;
	}
	struct KeySpace *cur = ptab->first;
	while(cur)
	{
		if(strcmp(key, cur->key)==0)
		{
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

KeySpace *get_element(Table *ptab, char *key)
{
	KeySpace *cur = ptab->first;
	while(cur)
	{
		if(strcmp(key, cur->key)==0)
		{
			KeySpace* new = malloc(sizeof(KeySpace));;
			new->key = calloc(strlen(key)+1, sizeof(char));
			strcpy(new->key, key);
			new->info = calloc(strlen(cur->info)+1, sizeof(char));
			strcpy(new->info, cur->info);
			new->next = cur->next;
			return new;
		}
		cur = cur->next;
	}
	return NULL;
}

int add(Table *ptab, char *key, char *info)
{
	if(is(ptab, key) == 1)
	{
		return 1; 
	}

	if(ptab->cs == ptab->ms)
	{
		return 2;
	}

	if(key[0]=='\0')
	{
		return 3;
	}
	
	KeySpace *new = malloc(sizeof(KeySpace));
	new->key = key;
	new->info = info;
	new->next = NULL;
	
	if(ptab->cs == 0)
	{
		ptab->first = new;
		ptab->cs++;
		return 0;
	}
	
	KeySpace *cur = ptab->first;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}

	cur->next = new;
	ptab->cs++;
	return 0;
}

Table *ind_task(Table *ptab, char *kstart, char *kend)
{

	Table *rs = malloc(sizeof(Table));
	rs->first = NULL;
	rs->ms =  ptab->ms;
	rs->cs =  0;

	if(is(ptab, kstart)==0 || is(ptab, kend)==0)
	{
		return rs;
	}
	
	KeySpace *cur = get_element(ptab, kstart);
	KeySpace*del = cur;
	KeySpace *last = get_element(ptab, kend);
	
	while(cur != last->next)
	{
		char*newkey = calloc(strlen(cur->key)+1, sizeof(char));
		char*newinfo = calloc(strlen(cur->info)+1, sizeof(char));
		strcpy(newkey, cur->key);
		strcpy(newinfo, cur->info);
		add(rs, newkey, newinfo);
		cur = cur->next;
	}
	free(del->key);
	free(del->info);
	free(del);
	free(last->key);
	free(last->info);
	free(last);
	return rs;
}

int print_table(Table *ptab)
{	
	if(ptab->cs == 0)
	{
		printf("No elements!\n");
		return 0;
	}

	KeySpace *cur = ptab->first;

	while(cur!=NULL)
	{
		printf("key: %s| ", cur->key);
		printf("info: %s|\n", cur->info);
		cur = cur->next;
	}
	return 0;
}

int clear_mem(Table *ptab)
{
	if(ptab->cs == 0)
	{
		free(ptab);
		return 1;
	}

	KeySpace *cur = ptab->first;
	KeySpace *fr = NULL;
	
	while(cur!=NULL)
	{
		fr = cur;
		cur = cur->next;
		free(fr->key);
		free(fr->info);
		free(fr);
	}
	ptab->first = cur;
	free(ptab);
	return 1;
}

int del(Table *ptab, char *key)
{

	if(is(ptab, key)==0)
	{
		return 4;
	}

	KeySpace *del;

	KeySpace *cur = ptab->first;

	if(strcmp(key, cur->key) == 0)
	{
		del = cur;
		ptab->first = cur->next;
		free(del);
		ptab->cs--;
		return 0;
	}

	if(ptab->cs == 1)
	{
		free(cur->key);
		free(cur->info);
		free(cur);
		ptab->first = NULL;
		ptab->cs--;
		return 0;
	}

	
	while(strcmp(cur->next->key, key)!=0)
	{
		cur = cur->next;
	}

	del = cur->next;

	cur->next = cur->next->next;

	free(del->key);
	free(del->info);
	free(del);
	ptab->cs--;

	return 0;
}

char*get_str_from_file(FILE*fp)
{
        char *ptr = (char*)malloc(1);
        char buf[81];
        int n, len = 0;
        *ptr = '\0';
        do{
                n = fscanf(fp, "%80[^\n]", buf);
                if (n < 0){
                        free(ptr);
                        ptr = NULL;
                        continue;
                }
                if(n == 0)
                        fscanf(fp, "%*c");
                else{
                        len += strlen(buf);
                        ptr = (char*)realloc(ptr, len+1);
                        strcat(ptr, buf);
                }
        }while(n > 0);

        return ptr;
}

int import(Table* ptab, char*file)
{
	FILE*fp = fopen(file, "r");
	if(!fp)
	{
		return 5;
	}
	char*key;
	char*info;
	do
	{
		key = get_str_from_file(fp);
		info = get_str_from_file(fp);
		fscanf(fp, "%*c");
		add(ptab, key, info);
	}while(!feof(fp));
	fclose(fp);
	return 0;
}
