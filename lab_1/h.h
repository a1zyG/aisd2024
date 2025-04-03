#ifndef H_H
#define H_H


typedef struct Line {

	int n; // количество элементов в строке матрицы
	int *a; // массив элементов
} Line;

// структура для задания самой матрицы
typedef struct Matrix {

	int lines; // количество строк матрицы
	Line *matr; // массив строк матрицы
} Matrix;

int input(Matrix *rm);

#endif
