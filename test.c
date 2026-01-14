#include<stdio.h>
#include"array_core.h"
#include"array_alloc.h"
#include"get.h"

int mat[MAX_M][MAX_M];
int flat[MAX_M * MAX_M];

int main(void)
{
	int len, row, col;
	int* arr=get_array(&len);
	if(!arr)
	{
		return 1;
	}
	printf("输入的一维数组为：\n");	
	print_array(arr, len);
	free(arr);	
	return 0;
}
