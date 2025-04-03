#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int clear_mem(Table*ptab)
{
	KeySpace *cur = ptab->first;
	KeySpace *prev = NULL;
	while(cur!=NULL)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	ptab->fd = NULL;
}

int save(Table*ptab)
{
	fseek(ptab->fd, sizeof(int), SEEK_SET);
	fwrite(&ptab->cs, sizeof(int), 1, ptab->fd);
	KeySpace*cur = ptab->first;
	for(int i=0; i<ptab->cs; i++)
	{
		fwrite(cur, sizeof(KeySpace), 1, ptab->fd);
		cur = cur->next;
	}
	fclose(ptab->fd);
	clear_mem(ptab);
	ptab->fd = NULL;
	return 1;
}

int create(Table*ptab, char*filename, int size)
{
	ptab->ms = size;
	ptab->cs = 0;
	ptab->first = NULL;
	ptab->fd = fopen(filename, "r+b");
	if(!ptab->fd)
	{
		ptab->first = NULL;
		return 0;
	}
	KeySpace *ks = calloc(ptab->ms, sizeof(KeySpace));
	fwrite(&ptab->ms, sizeof(int), 1, ptab->fd);
	fwrite(&ptab->cs, sizeof(int), 1, ptab->fd);
	fwrite(ks, sizeof(KeySpace), ptab->ms, ptab->fd);
	free(ks);
	return 1;
}

int load(Table*ptab, char*filename)
{
	ptab->fd = fopen(filename, "r+b");
	if(!ptab->fd)
	{
		return 0;
	}
	fread(&ptab->ms, sizeof(int), 1, ptab->fd);
	fread(&ptab->cs, sizeof(int), 1, ptab->fd);
	ptab->first = calloc(1,sizeof(KeySpace));
	fread(ptab->first, sizeof(KeySpace), 1, ptab->fd);
	KeySpace*prev = ptab->first;
	for(int i=1; i<ptab->cs; i++)
	{
		KeySpace*cur = calloc(1, sizeof(KeySpace));
		fread(cur, sizeof(KeySpace), 1, ptab->fd);
		prev->next = cur;
		prev = cur;
	}
	return 1;
}

int is(Table *ptab, char *key)
{
	if(ptab->cs == 0)
	{
		return 0;
	}
	KeySpace*cur = ptab->first;
	while(cur)
	{
		fseek(ptab->fd, cur->offset, SEEK_SET);
		char*curkey = calloc(cur->klen+1, sizeof(char));
		fread(curkey, sizeof(char), cur->klen, ptab->fd);
		if(strcmp(key, curkey) == 0)
		{
			free(curkey);
			return 1;
		}
		cur = cur->next;
		free(curkey);
	}
	return 0;
}

KeySpace *get_element(Table *ptab, char *key)
{
	KeySpace*cur = ptab->first;
	while(cur)
	{
		fseek(ptab->fd, cur->offset, SEEK_SET);
		char*curkey = calloc(cur->klen+1, sizeof(char));
		fread(curkey, sizeof(char), cur->klen, ptab->fd);
		if(strcmp(key, curkey) == 0)
		{
			KeySpace *res = malloc(sizeof(KeySpace));
			res->offset = cur->offset;
			res->klen = cur->klen;
			res->ilen = cur->ilen;
			res->next = cur->next;
			free(curkey);
			return res;
		}
		cur = cur->next;
		free(curkey);
	}
	return NULL;
}


int add(Table*ptab, char*key, char*info)
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
	fseek(ptab->fd, 0, SEEK_END);
	KeySpace*new = calloc(1,sizeof(KeySpace));
	new->offset = ftell(ptab->fd);
	new->klen = strlen(key);
	new->ilen = strlen(info);
	new->next = ptab->first;
	ptab->first = new;

	fwrite(key, sizeof(char), new->klen, ptab->fd);
	fwrite(info, sizeof(char), new->ilen, ptab->fd);

	ptab->cs++;
	return 0;
}

int print_table(Table*ptab)
{
	if(ptab->cs == -1)
	{
		return 4;
	}
	KeySpace*cur = ptab->first;
	while(cur!=NULL)
	{
		char*curkey = malloc(sizeof(char)*(cur->klen+1));
		char*curinfo = malloc(sizeof(char)*(cur->ilen+1));
		curkey[cur->klen]='\0';
		curinfo[cur->ilen]='\0';
		fseek(ptab->fd, cur->offset, SEEK_SET);
		fread(curkey, sizeof(char), cur->klen, ptab->fd);
		fread(curinfo, sizeof(char), cur->ilen, ptab->fd);
		printf("key: %s| ", curkey);
		printf("info: %s|\n", curinfo);
		cur = cur->next;
		free(curkey);
		free(curinfo);
	}
	return 0;
}

int print_element(Table*ptab, KeySpace*el)
{
	char*elkey = malloc(sizeof(char)*(el->klen+1));
	char*elinfo = malloc(sizeof(char)*(el->ilen+1));
	fseek(ptab->fd, el->offset, SEEK_SET);
	fread(elkey, sizeof(char), el->klen, ptab->fd);
	fread(elinfo, sizeof(char), el->ilen, ptab->fd);
	elkey[el->klen]='\0';
	elinfo[el->ilen]='\0';
	printf("key: %s| ", elkey);
	printf("info: %s\n", elinfo);
	return 1;
}

int del(Table*ptab, char* key)
{
	if(is(ptab, key)==0)
	{
		return 4;
	}
	KeySpace *el = get_element(ptab, key);
	KeySpace *cur = ptab->first;
	KeySpace *remove;
	int el_len = el->klen + el->ilen;
	fseek(ptab->fd, 0, SEEK_END);
	int file_end = ftell(ptab->fd);
	char*new = calloc(file_end - el->offset - el_len, sizeof(char));
	fseek(ptab->fd, el->offset + el_len, SEEK_SET);
	fread(new, sizeof(char), file_end - el->offset - el_len, ptab->fd);
	fseek(ptab->fd, el->offset, SEEK_SET);
	fwrite(new, sizeof(char), file_end - el->offset - el_len, ptab->fd);
	ftruncate(fileno(ptab->fd), file_end - el_len);
	
	if(el->offset == cur->offset)
	{
		ptab->first = ptab->first->next;
		free(cur);
	}
	else
	{
		while(cur->next->offset != el->offset)
		{
			cur=cur->next;
		}
		remove = cur->next;
		cur->next = cur->next->next;
		free(remove);
	}

	cur=ptab->first;
	while(cur!=NULL)
	{
		if(cur->offset > el->offset)
		{
			cur->offset = cur->offset - el_len;
		}
		cur=cur->next;
	}
	free(new);
	free(el);
	ptab->cs--;
	return 0;
}

Table *ind_task(Table *ptab, char*kstart, char*kend)
{
	Table*rs = malloc(sizeof(Table));
	rs->fd = ptab->fd;
	rs->ms = ptab->ms;
	rs->cs = 0;
	rs->first = NULL;
	
	if(is(ptab, kstart) == 0 || is(ptab, kend) == 0)
	{
		rs->cs = -1;
		return rs;
	}
	
	KeySpace *cur = get_element(ptab, kstart);
	KeySpace *last = get_element(ptab, kend);
	if(cur->offset == last->offset)
	{
		rs->first = cur;
		free(last);
		rs->first->next = NULL;
		return rs;
	}
	if(cur->offset < last->offset)
	{
		KeySpace *chg = cur;
		cur = last;
		last = chg;
		chg = cur;
	}
	rs->first = cur;
	KeySpace*add = cur;
	cur = cur->next;
	while(cur->offset != last->offset)
	{
		add->next = malloc(sizeof(KeySpace));
		add->next->offset = cur->offset;
		add->next->klen = cur->klen;
		add->next->ilen = cur->ilen;
		add = add->next;
		cur = cur->next;
	}
	add->next = last;
	last->next = NULL;
	return rs;
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
                free(key);
                free(info);
        }while(!feof(fp));
        fclose(fp);
        return 0;
}
