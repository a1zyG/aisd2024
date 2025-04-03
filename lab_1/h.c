#include <stdio.h>
#include <stdlib.h>
//#include "h.h"

typedef struct Line {

        int n; 
        int *a; // массив элементов
} Line;

typedef struct Matrix {

        int lines; // количество строк матрицы
        Line *matr; // массив строк матрицы
} Matrix;

void pamyat(Matrix *rm){
	if (rm->lines && rm->lines > 0){
                for(int i = 0; i < rm->lines; i++)
                        free(rm->matr[i].a);
                free(rm->matr);
        }

}

void output(Matrix *rm, int m){
	for (int j = 0; j < m; j++){
                for (int i = 0; i < rm->matr[j].n; i++)
                        printf("%d ", rm->matr[j].a[i]);
                printf("\n");
        }

}

void individual(Matrix *rm, int i1, int i2, int m){
	Line swap = rm->matr[i1];
        rm->matr[i1] =rm->matr[0];
        rm->matr[0] = swap;
        if (i2 >= 0){
                Line swap2 = rm->matr[i2];
                rm->matr[i2] = rm->matr[m-1];
                rm->matr[m-1] = swap2;
        }

}

int input(Matrix *rm)
{
        const char *pr = "";
        int m=0, i, j, n, i1, i2;
        int ch;
	i1 = 0;
	i2 = -1;
	int k1 =  0;
	int k2 =  0;
	printf("Введите кол-во строк матрицы");
	printf("\n");
	int res1 = scanf("%d", &m);
        while(res1!=1 || m <= 0){
                printf("Введите верный размер");
		printf("\n");
		if (res1 == -1)
			exit(1);
		scanf("%*[^\n]%*c");
		m=0;
		res1 = scanf("%d", &m);
        }
	if (m == 0){
		printf("Введите верный размер");
		printf("\n");
		return -1;
	}
	int pol = 0 ;
	int otr = 0;
        rm->matr = (Line *) calloc(m, sizeof(Line));
        rm->lines = m;  
        for (j = 0; j < m; j++){
		printf("Введите кол-во элементов строки");
		printf("\n");
		int res2 = scanf("%d", &n) ;
                if (res2 != 1 || n < 0){
                        printf("Введите верный рамер строки");
			printf("\n");
			if (res2 == -1)
                        	return -2;
			scanf("%*[^\n]%*c");
	                n = 0;
			res2 = scanf("%d", &n) ;
                }
                rm->matr[j].n = n;
                rm->matr[j].a = (int *) malloc(n * sizeof(int)); 
                for (i = 0; i < n; i++){
			int res3 = scanf("%d",&ch);
                        while (res3!= 1){
				if (res3 == -1)
                        		return -2;
                                printf("Введено не число");
				printf("\n");
				scanf("%*[^\n]%*c");
				res3 = scanf("%d",&ch);
			}
                        (rm->matr[j].a[i]) = ch;
			if (ch > 0)
				k1++;
			if (ch < 0)
                                k2++;
                }
		if (k1 > pol){
			pol = k1;
			i1 = j;
		}
		if (k2 > otr){
			otr = k2;
			i2 = j;
		}
		k1 = 0;
		k2 = 0;
        }
	individual(rm, i1, i2, m);
	output(rm, m);
	pamyat(rm);
        return 1;
}

