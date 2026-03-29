#include<stdio.h>
#include<windows.h>
#include"array_core.h"
#include"array_alloc.h"
#include"get.h"

int main(void)
{
	SetConsoleOutputCP(65001);
	int n;
	int** mat = (int**)get_Determinant(&n);
	double det = caculateDeterminant(mat,n);
	freeContiguousMatrix(mat);
	printf("该行列式的值= %lf\n", det);
}
