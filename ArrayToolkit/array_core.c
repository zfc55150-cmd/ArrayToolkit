#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include "array_core.h"

#define FLT_EPSILON 1e-6
#define DBL_EPSILON 1e-14

//打印一维数组
void print_array(int* arr, int a)
{
	for (int x = 0; x < a; x++)
	{
		printf("%d\t", arr[x]);
	}
}

//逆序一维数组
void reverse_array(int* arr, int len)
{
	for (int x = 0; x < len / 2; x++)
	{
		int temp;
		temp = arr[x];
		arr[x] = arr[len - 1 - x];
		arr[len - 1 - x] = temp;
	}
}

//两种冒泡排序，升序和降序
void bubble_sort(int* arr, int len)
{
	char choice;
	printf("请选择升序还是降序\nA/a：升序\nB/b：降序\n");
	get_twochoice(&choice);

	if (choice == 'A' || choice == 'a')
	{
		for (int a = 0; a < len - 1; a++)
		{
			for (int b = 0; b < len - a - 1; b++)
			{
				if (arr[b] > arr[b + 1])
				{
					int temp;
					temp = arr[b];
					arr[b] = arr[b + 1];
					arr[b + 1] = temp;
				}
			}
		}
	}
	else
	{
		for (int a = 0; a < len - 1; a++)
		{
			for (int b = 0; b < len - a - 1; b++)
			{
				if (arr[b] < arr[b + 1])
				{
					int temp;
					temp = arr[b];
					arr[b] = arr[b + 1];
					arr[b + 1] = temp;
				}
			}
		}
	}
}

//用于打印二维数组
void print_matrix(int** mat,int row, int col)
{
	int total = row * col;

	for (int count = 0; count < total; count++)
	{
		printf("%d\t", mat[count / col][count % col]);
		if ((count + 1) % col == 0)
		{
			printf("\n");
		}
	}
}

//用来将二维数组一维化
int* matrix_flat(int** mat, int row, int col)
{
	int* flat = (int*)malloc((size_t)row * col * sizeof(int));
	if (flat == NULL) {
		printf("二维数组一维化失败，内存不够了\n");
		return NULL;
	}

	int x = 0;
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			flat[x++] = mat[a][b];
		}
	}

	return flat;
}                                       

//用来将一维数组二维化
int** matrix_unflat(int* flat, int len, int* row, int* col)
{
	if (flat == NULL) {
		printf("为传入有效的一维数组地址\n");
		return NULL;
	}

	printf("请输入要转化的二维数组的列数：\n");
	do
	{
		get_valid_int(col);
		if (*col <= 0 || *col > len)
		{
			printf("输入的列数范围有问题，请重新输入：\n");
			continue;
		}
		if (len % *col != 0)
		{
			printf("该一维数组没法转换成该列数的二维数组，请重新输入：\n");
			continue;
		}

		break;
	} while (1);
	
	*row = len / *col;

	int** mat = (int**)createContiguousMatrix(*row, *col,sizeof(int));
	if (mat == NULL) {
		printf("二维数组生成失败，一维数组二维化失败\n");
		return NULL;
	}

	for (int a = 0; a < len; a++)
	{
		mat[a / *col][a % *col] = flat[a];
	}
	return mat;
}                                       

//选择排序，升序
void select_Asort(int* arr, int len)
{
	for (int a = 0; a < len; a++)
	{
		int min = a;
		for (int b = a + 1; b < len; b++)
		{
			if (arr[b] < arr[min])
			{
				min = b;
			}
		}
		if (min != a)
		{
			int temp = arr[a];
			arr[a] = arr[min];
			arr[min] = temp;
		}
	}
}                                   

//选择排序，降序
void select_Bsort(int* arr, int len)
{
	for (int a = 0; a < len; a++)
	{
		int max = a;
		for (int b = a + 1; b < len; b++)
		{
			if (arr[b] > arr[max])
			{
				max = b;
			}
		}
		if (max != a)
		{
			int temp = arr[a];
			arr[a] = arr[max];
			arr[max] = temp;
		}
	}
}                                   

//用来选择选择排序是升序还是降序
void select_sort(int* arr, int len)
{
	char choice;
	printf("请输入你想要的排序方式\nA/a：升序排序\nB/b：降序排序\n");
	get_twochoice(&choice);

	if (choice == 'A' || choice == 'a')
	{
		select_Asort(arr, len);
	}
	else
	{
		select_Bsort(arr, len);
	}
}                                          

//查找自己选定的元素
void array_linear_search(int* arr, int len)
{
	int values;
	printf("请输入一个要查找的元素（整数）：\n");
	get_valid_int(&values);

	for (int a = 0; a < len; a++)
	{
		if (arr[a] == values)
		{
			printf("找到了，他是这个数组的第%d个元素\n", a + 1);
			return;
		}
	}
	printf("未在数组中找到该元素\n");
}

//封装了array_linear_search()函数，使其更具有交互性
void array_search_ui(int* arr, int len)
{
	array_linear_search(arr, len);

	while (1)
	{
		char choice;
		printf("是否重新查找：\nA/a：是\nB/b：否");
		get_twochoice(&choice);

		if (choice == 'A' || choice == 'a')
		{
			array_linear_search(arr, len);
		}
		else
		{
			return;
		}
	}
}                                     

//用来查找二维数组中的元素
void matrix_search(int** mat, int row, int col)
{
	int* flat = (int*)malloc((size_t)row * col * sizeof(int));
	if (flat == NULL) {
		printf("查找元素时将二维数组一维化失败,查找失败！\n");
		return;
	}

	flat=matrix_flat(mat, row, col);

	int values;
	printf("请输入一个要查找的元素（整数）：\n");
	get_valid_int(&values);

	for (int a = 0; a < row * col; a++)
	{
		if (flat[a] == values)
		{
			printf("找到了，他在这个二维数组的第%d行，第%d列\n", (a / col) + 1, (a % col) + 1);
			return;
		}
	}
	printf("未在该数组中找到该元素\n");

}                                     

//用来转置矩阵
void transpose_matrix(int** mat, int* row, int* col)
{
	int** mat2 = (int**)createContiguousMatrix(*col, *row,sizeof(int));
	if (mat2 == NULL) {
		printf("转置辅助矩阵生成失败，转置失败\n");
		return;
	}

	for (int a = 0; a < *row; a++)
	{
		for (int b = 0; b < *col; b++)
		{
			mat2[b][a] = mat[a][b];
		}
	}

	for (int a = 0; a < *col; a++)
	{
		for (int b = 0; b < *row; b++)
		{
			mat[a][b] = mat2[a][b];
		}
	}

	free(mat2[0]);
	free(mat2);
	int temp;
	temp = *row;
	*row = *col;
	*col = temp;
}

//用来计算n阶行列式
double caculateDeterminant(int** mat, int n)
{
	//复制一个相同的二维数组用于计算
	double** mat2 = (double**)createContiguousMatrix(n, n, sizeof(double));
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			mat2[a][b] = (double)mat[a][b];
		}
	}
   
	double det = 1.0;
	int sign = 1;

	//将行列式进行排序，将每列的绝对值最大的元素作为该列主元
	for (int b = 0; b < n; b++) {
		int Maxrow = b;
		for (int a = b + 1; a < n; a++) {
			if (fabs(mat2[a][b]) > fabs(mat2[Maxrow][b])) {
				Maxrow = a;
			}
		}

		if (fabs(mat2[Maxrow][b]) < DBL_EPSILON) {
			freeContiguousMatrix(mat2);
			return 0.0;
		}

		//判断并处理行列式的行交换
		if (Maxrow != b) {
			for (int i = 0; i < n; i++) {
				double temp = mat2[Maxrow][i];
				mat2[Maxrow][i] = mat2[b][i];
				mat2[b][i] = temp;
			}
			sign *= -1;
		}

		//用循环嵌套将行列式化为上三角类型
		for (int x = b + 1; x < n; x++) {
			double ratio = mat2[x][b] / mat2[b][b];
			for (int y = b; y < n; y++) {
				mat2[x][y] -= ratio * mat2[b][y];
			}
		}

	}

	//计算主对角线元素的乘积
	for (int a = 0; a < n; a++) {
		det *= mat2[a][a];
	}

	freeContiguousMatrix(mat2);
	return det * sign;
}
