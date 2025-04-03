#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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

int Insert(Tree *tree, char* key, int info){
	Node *ptr = tree->root;
	Node *parr = NULL;
	while (ptr){
		parr = ptr;
		if (strcmp(key, ptr->key) <= 0)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	
	}
	Node *new = malloc(sizeof(Node));
	new->key = strdup(key);
	new->info = info;
	new->left = new->right = NULL;

	if (parr == NULL)
		tree->root = new;
	else if (strcmp(key, parr->key) <= 0)
		parr->left = new;
	else
		parr->right = new;
	return 0;
}

Node** Find(Tree*tree, char*key, int*count)
{
	if(!key)
		return NULL;
	 Node**res = NULL;
	 *count = 0;
	 Node*ptr = tree->root;
	 Node *parr = NULL;
	 while(ptr)
	 {
	 	parr = ptr;
	 	if(strcmp(key, ptr->key) == 0)
	 	{
	 		(*count)++;
	 		res = realloc(res, sizeof(Node*)*(*count));
	 		res[(*count)-1] = ptr;
	 	}
	 	if(strcmp(key, ptr->key) <= 0)
	 		ptr = ptr->left;
	 	else
	 		ptr = ptr->right;
	 }
	 return res;
}

Node*Get_Parent(Tree*tree, Node*x)
{
	Node*ptr = tree->root;
	while(ptr)
	{
		if(x == ptr->left || x == ptr->right)
			return ptr;
		if(strcmp(x->key, ptr->key) <= 0)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return ptr;
}

int Erase(Tree*tree, char*key, int release)
{
	int n;
	Node**rel = Find(tree, key, &n);
	if(rel == NULL)
	{
		return 3;
	}
	if(n<release || release<=0)
	{
		free(rel);
		return 3;
	}
	Node*x =rel[release-1];
	Node*parr = Get_Parent(tree, x);
	if(x->left == NULL && x->right == NULL)
	{
		if(parr == NULL)
			tree->root = NULL;
		else if(parr->left == x)
			parr->left = NULL;
		else
			parr->right = NULL;
		free(x->key);
		free(x);
	}
	else if(x->left == NULL && x->right != NULL)
	{
		if(parr == NULL)
			tree->root = x->right;
		else if(parr->left == x)
			parr->left = x->right;
		else
			parr->right = x->right;
		free(x->key);
		free(x);
	}
	else if(x->left != NULL && x->right == NULL)
	{
		if(parr == NULL)
			tree->root = x->left;
		else if(parr->left == x)
			parr->left = x->left;
		else 
			parr->right = x->left;
		free(x->key);
		free(x);
	}
	else
	{
		Node*new_p = x;
		Node*new_x = x->right;
		while(new_x->left)
		{
			new_p = new_x;
			new_x = new_x->left;
		}
		
		free(x->key);
		x->key = new_x->key;
		x->info = new_x->info;
		
		if(new_p == x)
		{
			x->right = new_x->right;
		}
		else
		{
			new_p->left = new_x->right;
		}
		free(new_x);
	}
	free(rel);
	return 0;
}



void Show_Tree(Node*n, int level)
{
	if(n!=NULL)
	{
		Show_Tree(n->left, level+1);
		for(int i=0; i<level; i++)
			printf("	");
		printf("\"%s\"(%d)\n", n->key, n->info);
		Show_Tree(n->right, level+1);
	}
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
		//printf("  %s\n", ptr);
        return ptr;
}

int Import(Tree*tree, char*file)
{
        FILE*fp = fopen(file, "r");
        if(!fp)
        {
                return 4;
        }
        char*key;
        int info;
        do
        {
                key = get_str_from_file(fp);
                fscanf(fp, "%d", &info);
                fscanf(fp, "%*c");
                if(!key)
                {
                	fclose(fp);
                	return 0;
                }
                Insert(tree, key, info);
                free(key);
        }while(!feof(fp));
        fclose(fp);
        return 0;
}


int Bypass(Node*n)
{
	if(n)
	{
		Bypass(n->left);
		Bypass(n->right);
		printf("\"%s\"(%d)\n", n->key, n->info);
	}
}

Node**Individual_Find(Tree*tree, char*max, int*count)
{
	Node*ptr = tree->root;
	char*key = NULL;
	while(ptr)
	{
		if(strcmp(ptr->key, max)<=0)
		{
			if(key == NULL)
				key = ptr->key;
			if(strcmp(key, ptr->key) < 0)
				key = ptr->key;
			ptr = ptr->right;
		}
		else
			ptr = ptr->left;
	}
	return Find(tree, key, count);
}

int Print_Nodes(Node**n, int*count)
{
	if(n == NULL)
		return 3;
	for(int i=0; i<(*count); i++)
	{
		printf("№%d:\"%s\"(%d)\n", i+1, n[i]->key, n[i]->info);
	}
	return 0;
}

int Clear_Tree(Node*root)
{
	if(!root)
		return 1;
	Clear_Tree(root->left);
	Clear_Tree(root->right);	
	free(root->key);
	free(root);
}

int Timing_Find()
{
	Tree tree = {NULL};
	int n = 10, cnt = 100000, i, m;
	char key[10000][4], k[4];
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0){
		for (i = 0; i < 10000; ++i)
		{
			key[i][0] = (1 + rand()%255);
			key[i][1] = (1 + rand()%255);
			key[i][2] = (1 + rand()%255);
			key[i][3] = '\0';
			
		}
		for (i = 0; i < cnt; i++){
			k[0] = (1 + rand()%255);
			k[1] = (1 + rand()%255);
			k[2] = (1 + rand()%255);
			k[3] = '\0';
			Insert(&tree, k, 1);
		}
		m = 0;
		int count;
		first = clock();
		for (i = 0; i < 10000; ++i)
		{
			Node**x;
			if ((x = Find(&tree, key[i], &count)) != NULL)
				++m;
			free(x);
		}
		last = clock();
		printf("%d items was found\n", m);
		printf("test #%d, number of nodes = %d, time = %d\n", 10 - n, (10 - n)*cnt, (last - first));
	}
	Clear_Tree(tree.root);
	return 1;
}

int Timing_Insert()
{
	Tree tree = {NULL};
	int n = 10, cnt = 100000, i, m;
	char key[10000][4], k[4];
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0){
		for (i = 0; i < 10000; ++i)
		{
			key[i][0] = (1 + rand()%255);
			key[i][1] = (1 + rand()%255);
			key[i][2] = (1 + rand()%255);
			key[i][3] = '\0';
			
		}
		for (i = 0; i < cnt; i++){
			k[0] = (1 + rand()%255);
			k[1] = (1 + rand()%255);
			k[2] = (1 + rand()%255);
			k[3] = '\0';
			Insert(&tree, k, 1);
		}
		//m = 0;
		int count;
		first = clock();
		for (i = 0; i < 10000; ++i)
			Insert(&tree, key[i], 1);
		last = clock();
		printf("1000 items was added\n");
		printf("test #%d, number of nodes = %d, time = %d\n", 10 - n, (10 - n)*cnt, (last - first));
	}
	Clear_Tree(tree.root);
	return 1;
}

int Timing_Erase()
{
	Tree tree = {NULL};
	int n = 10, cnt = 100000, i, m;
	char key[10000][4], k[4];
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0){
		for (i = 0; i < 10000; ++i)
		{
			key[i][0] = (1 + rand()%255);
			key[i][1] = (1 + rand()%255);
			key[i][2] = (1 + rand()%255);
			key[i][3] = '\0';
			
		}
		for (i = 0; i < cnt; i++){
			k[0] = (1 + rand()%255);
			k[1] = (1 + rand()%255);
			k[2] = (1 + rand()%255);
			k[3] = '\0';
			Insert(&tree, k, 1);
		}
		m = 0;
		int count;
		first = clock();
		for (i = 0; i < 10000; ++i)
		{
			if(Erase(&tree, key[i], 1) == 0)
				m++;
		}
		last = clock();
		printf("%d items was deleted\n", m);
		printf("test #%d, number of nodes = %d, time = %d\n", 10 - n, (10 - n)*cnt, (last - first));
	}
	Clear_Tree(tree.root);
	return 1;
}
