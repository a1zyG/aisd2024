#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int getInt(int*n);
int D_Add(Table*ptab);
int D_Find(Table*ptab);
int D_Delete(Table*ptab);
int D_Show(Table*ptab);
int D_Import(Table*ptab);
int D_IndTask(Table*ptab);


const char *msgs[ ] = {"0. Quit", "1. Add","2. Find", "3. Delete", "4. Show", "5. Import", "6. Individual task"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow", "Empty", "Key isnt found", "Cant open file"};

int dialog(const char *msgs[ ], int N){
	char *errmsg = "";
	int rc;
	int i, n;
	do{
		puts(errmsg);
		errmsg = "You are wrong. Repeat, please!";
		for(i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("Make your choice: --> ");
		n = getInt(&rc); // ввод номера  альтернативы
		if(n == -1)
			rc = -1;
		if(n == 0) // конец файла – конец работы
			rc = 0;
	} while(rc < 0 || rc >= N);
	return rc;
}

int getInt(int*n)
{
	int flag = scanf("%d", n);
	if(flag == 0)
	{
		scanf("%*c");
		return -1;
	}
	else if(flag == 1)
	{
		scanf("%*c");
		return 1;
	}
	if(flag == -1)
	{
		return 0;
	}
}

int D_Add(Table*ptab)
{
	int rc;
	char *key = NULL; 
	char *info = NULL;
	printf("Enter key: -->");
	key = getstr();
	if(key == NULL)
		return 0;
	printf("Enter info: -->");
	info = getstr();
	if (info == NULL)
		return 0; 
	rc = add(ptab, key, info);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Find(Table*ptab)
{
	int rc;
	char *key = NULL; 
	printf("Enter key: -->");
	key = getstr();
	if(key == NULL)
		return 0; 

	KeySpace *el = get_element(ptab, key);
	if(!el)
	{
		free(key);
		rc = 4;
		printf("%s\n", errmsgs[rc]);
		return 1;
	}
	else
	{
		rc = 0;
		printf("key:%s| info:%s|", el->key, el->info);
	}
	free(key);
	free(el->key);
	free(el->info);
	free(el);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Delete(Table*ptab)
{
	int rc;
	char *key = NULL; 
	printf("Enter key: -->");
	key = getstr();
	if(key == NULL)
		return 0; 

	rc = del(ptab, key);
	
	free(key);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Show(Table*ptab)
{

	printf("Table\n");
	
	int rc = print_table(ptab);
	
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Import(Table*ptab)
{
	int rc;
	char *file = NULL; 
	printf("Enter file name: -->");
	file = getstr();
	if(file == NULL)
		return 0; 

	rc = import(ptab, file);
	
	free(file);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_IndTask(Table*ptab)
{
	int rc;
	char *key1 = NULL; 
	printf("Enter key1: -->");
	key1 = getstr();
	if(key1 == NULL)
		return 0; 

	char *key2 = NULL; 
	printf("Enter key2: -->");
	key2 = getstr();
	if(key2 == NULL)
	{
		free(key1);
		return 0;
	}

	Table*res = ind_task(ptab, key1, key2);

	if(!res)
	{
		rc = 4;
	}
	else
	{
		rc = print_table(res);
	}

	free(key1);
	free(key2);
	clear_mem(res);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int main()
{
	int (*fptr[ ])(Table *) = {NULL, D_Add, D_Find,D_Delete, D_Show, D_Import, D_IndTask };
	Table*table = malloc(sizeof(Table));
	init(table, 100);
	int rc;
	while(rc = dialog(msgs, NMsgs))
		if(!fptr[rc](table))
			break; // обнаружен конец файла

	printf("End of file\n");
	clear_mem(table);
	return 0;

}
