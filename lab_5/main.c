#include <stdlib.h>
#include <stdio.h>
#include "func.h"

int getInt(int*n);
int D_Add_person(Gcom*graph);
int D_Add_connection(Gcom*graph);
int D_Delete_person(Gcom*graph);
int D_Delete_connection(Gcom*graph);
int D_Edit_name(Gcom*graph);
int D_Edit_relationship(Gcom*graph);
int D_Printf_graph(Gcom*graph);
int D_Bypass(Gcom*graph);
int D_Find_shortest_path(Gcom*graph);
int D_Find_KSS(Gcom*graph);


const char *msgs[ ] = {"0. Quit", "1. Add person","2. Add connection", "3. Delete person", "4. Delete connection", "5. Edit name", "6. Edit relationship", "7. Printf graph", "8. Bypass graph", "9. Find shortest path", "10. Find KSS"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char *errmsgs[] = {"Ok", "Duplicate name", "Wrong value of relation", "Couldnt find name", "Dublicate edge", "Couldnt find edge", "Empty graph"};

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

int D_Add_person(Gcom*graph)
{
        int rc;
        char* name;
        printf("Enter name: -->");
        name = getstr();
        if(!name)
        	return 0;

        rc = add_person(graph, name);
        free(name);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Add_connection(Gcom*graph)
{
        int rc, relation;
        printf("Enter first name: -->");
        char* name1 = getstr();
        if(!name1)
        	return 0;

        printf("Enter second name: -->");
        char* name2 = getstr();
        if(!name2)
        {	
        	free(name1);
        	return 0;
        }

        printf("Enter relation: -->");
        if(getInt(&relation) == 0)
        {
        	free(name1);
        	free(name2);
        	return 0;
        }
		int n;
		rc = add_connection(graph, name1, name2, relation);
		free(name1);
        free(name2);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Delete_person(Gcom*graph)
{
        int rc;
        char* name;
        printf("Enter name: -->");
        name = getstr();
        if(!name)
        	return 0;

        rc = delete_person(graph, name);
		free(name);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Delete_connection(Gcom*graph)
{
        int rc;
        printf("Enter first name: -->");
        char* name1 = getstr();
        if(!name1)
        	return 0;

        printf("Enter second name: -->");
        char* name2 = getstr();
        if(!name2)
        {
        	free(name1);
        	return 0;
        }

        rc = delete_connection(graph, name1, name2);
		free(name1);
		free(name2);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Edit_name(Gcom*graph)
{
        int rc;
        printf("Enter old name: -->");
        char* oldname = getstr();
        if(oldname == NULL)
	        return 0;

        printf("Enter new name: -->");
        char* newname = getstr();
        if(newname == NULL)
        {	
        	free(oldname);	
        	return 0;
        }

        rc = edit_name(graph, oldname, newname);

        free(oldname);
        free(newname);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Edit_relationship(Gcom*graph)
{
        int rc, relation;
        printf("Enter first name: -->");
        char* name1 = getstr();
        if(!name1)
        	return 0;

        printf("Enter second name: -->");
        char* name2 = getstr();
        if(!name2)
        {
        	free(name1);
        	return 0;
        }

        printf("Enter new relation: -->");
        if(getInt(&relation) == 0)
        {
        	free(name1);
        	free(name2);
        	return 0;
        }

		rc = edit_relation(graph, name1, name2, relation);
		free(name1);
        free(name2);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Printf_graph(Gcom*graph)
{
		int rc;
		printf("Graph:\n");
		rc = print_graph(graph);
		printf("%s\n", errmsgs[rc]);
		return 1;
}

int D_Bypass(Gcom*graph)
{
        int rc;
        char* name;
        printf("Enter name: -->");
        name = getstr();
        if(!name)
        	return 0;

        rc = bypass_dfs(graph, name);

		free(name);
		printf("%s\n", errmsgs[rc]);
		return 1;
}

int D_Find_shortest_path(Gcom*graph)
{
        int rc;
        printf("Enter from-name: -->");
        char* from_name = getstr();
        if(!from_name)
        	return 0;

        printf("Enter to-name: -->");
        char* to_name = getstr();
        if(!to_name)
        {
        	free(from_name);
        	return 0;
        }

        rc = shortest_path_djkstra(graph, from_name, to_name);
        free(from_name);
        free(to_name);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Find_KSS(Gcom*graph)
{
	int rc;
	rc = find_kss(graph);
	return 1;
}

int main()
{
        int (*fptr[ ])(Gcom *) = {NULL, D_Add_person, D_Add_connection, D_Delete_person, D_Delete_connection, D_Edit_name, D_Edit_relationship, D_Printf_graph, D_Bypass, D_Find_shortest_path, D_Find_KSS};
        Gcom* graph = init_gcom();
	
        int rc;
        while(rc = dialog(msgs, NMsgs))
                if(!fptr[rc](graph))
                        break; // обнаружен конец файла

        printf("End of file\n");
        clear_graph(graph);
        return 0;

}
