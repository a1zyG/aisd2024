#include "h.h"
#include <stdio.h>

int main()
{
	Matrix matr;
	int c = input(&matr);
	if (c == -2)
		printf("Ошибка ввода");
	return 0;
}
