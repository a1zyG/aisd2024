#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int getInt(int*n);
int D_Add(Tree*tree);
int D_Find(Tree*tree);
int D_Delete(Tree*tree);
int D_Print(Tree*tree);
int D_Import(Tree*tree);
int D_IndFind(Tree*tree);
int D_Bypass(Tree*tree);


const char *msgs[ ] = {"0. Quit", "1. Add","2. Find", "3. Delete", "4. Print", "5. Import", "6. Individual find", "7. Bypass", "8. Find timing", "9. Insert timing", "10. Erase timing"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char *errmsgs[] = {"Ok", "Duplicate key", "Empty", "Key isnt found", "Cant open file"};

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

int D_Find_Timing(Tree*tree)
{
	Timing_Find();
	return 1;
}

int D_Insert_Timing(Tree*tree)
{
	Timing_Insert();
	return 1;
}

int D_Erase_Timing(Tree*tree)
{
	Timing_Erase();
	return 1;
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

int D_Add(Tree*tree)
{
        int rc;
        char* key;
        int info;
        printf("Enter key: -->");
        key = getstr();
        if(!key)
        	return 0;
        printf("Enter info: -->");
        if(getInt(&info) == 0)
        {
        	free(key);
        	return 0;
        }

        rc = Insert(tree, key, info);
        free(key);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Find(Tree*tree)
{
        int rc;
        char* key;
        printf("Enter key: -->");
        key = getstr();
        if(!key)
        	return 0;

		int n;
		Node**nodes = Find(tree, key, &n);
		rc = Print_Nodes(nodes, &n);
		free(nodes);
        free(key);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Delete(Tree*tree)
{
        int rc;
        char* key;
        int release;
        printf("Enter key: -->");
        key = getstr();
        if(!key)
        	return 0;
        	
        printf("Enter release: -->");
        if(getInt(&release) == 0)
        {
        	free(key);
        	return 0;
        }

        rc = Erase(tree, key, release);
		free(key);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Print(Tree*tree)
{
		printf("Tree\n");

        Show_Tree(tree->root, 0);

        return 1;
}

int D_Import(Tree*tree)
{
        int rc;
        char *file = NULL;
        printf("Enter file name: -->");
        file = getstr();
        if(file == NULL)
                return 0;

        rc = Import(tree, file);

        free(file);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_IndFind(Tree*tree)
{
        int rc;
        char* max;
        printf("Enter max key: -->");
        max = getstr();
        if(!max)
        	return 0;

		int n;
		Node**nodes = Individual_Find(tree, max, &n);
		rc = Print_Nodes(nodes, &n);
		free(nodes);
        free(max);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Bypass(Tree*tree)
{
	int rc;
	printf("Bypass:\n");
	Bypass(tree->root);
	return 1;
}

int main()
{
        int (*fptr[ ])(Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Print, D_Import, D_IndFind, D_Bypass, D_Find_Timing, D_Insert_Timing, D_Erase_Timing};
        Tree a = {NULL};
	
        int rc;
        while(rc = dialog(msgs, NMsgs))
                if(!fptr[rc](&a))
                        break; // обнаружен конец файла

        printf("End of file\n");
        Clear_Tree(a.root);
        return 0;

}
