#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "get.h"
#include "array_alloc.h"
#include "array_core.h"
#include "status.h"

#define FLT_EPSILON 1e-6
#define EPS 1e-10

//打印一维数组
void print_array(int* arr, int a)
{
	for (int x = 0; x < a; x++)
	{
		printf("%d  ", arr[x]);
	}
	printf("\n");
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
ATKStatus bubble_sort(int* arr, int len,char* if_ascending)
{
	if (arr == NULL) {
		return Array_Input_NULL;
	}
	if (len <= 0) {
		return Arrray_InvalidSize;
	}

	if (strcmp(if_ascending, "yes") == 0 || strcmp(if_ascending, "Yes") == 0) {
		for (int a = 0; a < len - 1; a++){
			for (int b = 0; b < len - a - 1; b++){
				if (arr[b] > arr[b + 1]){
					int temp;
					temp = arr[b];
					arr[b] = arr[b + 1];
					arr[b + 1] = temp;
				}
			}
		}

		return Funk_Op_OK;
	}

	else if(strcmp(if_ascending, "no") == 0 || strcmp(if_ascending, "No") == 0){
		for (int a = 0; a < len - 1; a++){
			for (int b = 0; b < len - a - 1; b++){
				if (arr[b] < arr[b + 1]){
					int temp;
					temp = arr[b];
					arr[b] = arr[b + 1];
					arr[b + 1] = temp;
				}
			}
		}

		return Funk_Op_OK;
	}

	return Funk_Param_Err;
}

//用于打印二维数组
void print_array2D(int** mat, int row, int col)
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

//用来将二维数组一维化 (  使用后记得要释放！ ）
int* array2D_flat(int** mat, int row, int col)
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
int** array2D_unflat(int* flat, int len, int* row, int* col)
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

	int** mat = (int**)createContiguousArray2D(*row, *col, sizeof(int));
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
	int* flat = array2D_flat(mat, row, col);
	if (flat == NULL) {
		return;
	}

	int values;
	printf("请输入一个要查找的元素（整数）：\n");
	get_valid_int(&values);

	for (int a = 0; a < row * col; a++)
	{
		if (flat[a] == values)
		{
			printf("找到了，他在这个二维数组的第%d行，第%d列\n", (a / col) + 1, (a % col) + 1);
			free(flat);
			return;
		}
	}
	printf("未在该数组中找到该元素\n");

	free(flat);
}

//用来转置矩阵
double** transpose_matrix(double** mat, int* row, int* col)
{
	if (mat == NULL || row == NULL || col == NULL) {
		return NULL;
	}

	double** mat2 = (double**)createContiguousArray2D(*col, *row, sizeof(double));
	if (mat2 == NULL) {
		printf("转置辅助矩阵生成失败，转置失败\n");
		return NULL;
	}

	for (int a = 0; a < *row; a++) {
		for (int b = 0; b < *col; b++) {
			mat2[b][a] = mat[a][b];
		}
	}

	int temp;
	temp = *row;
	*row = *col;
	*col = temp;

	return mat2;
}

//用来计算n阶行列式
bool calculate_det(double** mat, int n, double* result)
{
	//输入检测
	assert(mat != NULL);
	assert(n > 0);
	assert(result != NULL);

	if (mat == NULL || n <= 0 || result == NULL) {
		return false;
	}

	//复制一个相同的二维数组用于计算
	double** mat2 = (double**)createContiguousArray2D(n, n, sizeof(double));
	if (mat2 == NULL) {
		return false;
	}

	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			mat2[a][b] = mat[a][b];
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

		if (fabs(mat2[Maxrow][b]) < EPS) {
			freeContiguousArray2D((void**)mat2);
			*result = 0.0;
			return true;
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

	freeContiguousArray2D((void**)mat2);
	*result = det * sign;
	return true;
}

ATKStatus matrix_to_rowechelon(double** mat, int row, int col)
{
	if (mat == NULL ) {
		return Matrix_Input_NULL;
	}

	if (row <= 0 || col <= 0) {
		return Matrix_InvalidSize;
	}

	int pivot_row = 0;
	for (int j = 0; j < col && pivot_row < row; j++) {
		int maxrow = pivot_row;
		for (int i = pivot_row + 1; i < row; i++) {
			if (fabs(mat[i][j]) > fabs(mat[maxrow][j])) {
				maxrow = i;
			}
		}

		if (fabs(mat[maxrow][j]) < EPS) {
			continue;
		}

		if (maxrow != pivot_row) {
			for (int x = 0; x < col; x++) {
				double temp = mat[maxrow][x];
				mat[maxrow][x] = mat[pivot_row][x];
				mat[pivot_row][x] = temp;
			}
		}

		for (int i = pivot_row + 1; i < row; i++) {
			double ratio = mat[i][j] / mat[pivot_row][j];
			for (int k = j; k < col; k++) {
				mat[i][k] -= ratio * mat[pivot_row][k];
			}
		}

		pivot_row++;
	}

	return Funk_Op_OK;
}

ATKStatus matrix_to_rowsimplest(double** mat, int row, int col)
{
	ATKStatus status = matrix_to_rowechelon(mat, row, col);
	if (status != Funk_Op_OK) {
		return status;
	}

	int rank = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (fabs(mat[i][j]) > EPS) {
				rank++;
				break;
			}
		}
	}

	int pivot_row = rank - 1;
	for (; pivot_row >= 0; pivot_row--) {
		int pivot_col = 0;
		for (; pivot_col < col; pivot_col++) {
			if (fabs(mat[pivot_row][pivot_col]) > EPS) {
				break;
			}
		}

		for (int j = pivot_col+1; j < col; j++) {
			mat[pivot_row][j] /= mat[pivot_row][pivot_col];
		}
		mat[pivot_row][pivot_col] = 1.0;

		int cur_row = pivot_row - 1;
		for (; cur_row >= 0; cur_row--) {
			if (fabs(mat[cur_row][pivot_col]) > EPS) {
				double ratio = mat[cur_row][pivot_col];
				for (int j = pivot_col + 1; j < col; j++) {
					mat[cur_row][j] -= ratio * mat[pivot_row][j];
				}

				mat[cur_row][pivot_col] = 0.0;
			}
		}

	}

	return Funk_Op_OK;
}

double** clone_matrix(double** mat, int row, int col) 
{
	if (mat == NULL || row < 0 || col <= 0) {
		return NULL;
	}

	double** mat2=(double**)createContiguousArray2D(row, col, sizeof(double));
	if (mat2 == NULL) {
		return NULL;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat2[i][j] = mat[i][j];
		}
	}
	
	return mat2;
}

int matrix_rank(double** mat, int row, int col)
{
	int rank = 0;
	
	double** mat2 = clone_matrix(mat, row, col);
	if (mat2 == NULL) {
		return -1;
	}

	ATKStatus status = matrix_to_rowechelon(mat2, row, col);
	if (status !=Funk_Op_OK) {
		freeContiguousArray2D(mat2);
		return -1;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (fabs(mat2[i][j]) > EPS) {
				rank++;
				break;
			}
		}
	}

	freeContiguousArray2D(mat2);
	return rank;
}

ATKStatus inverse_matrix(double** mat, int n)
{
	if (mat == NULL) {
		return Matrix_Input_NULL;
	}

	if (n <= 0) {
		return Matrix_InvalidSize;
	}

	//右添单位矩阵创建增广矩阵
	double** mat2 = (double**)createContiguousArray2D(n, 2 * n, sizeof(double));
	if (mat2 == NULL) {
		return Matrix_Alloc_Failed;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat2[i][j] = mat[i][j];
		}

		for (int j = 0; j < n; j++) {
			mat2[i][j + n] = (i == j) ? 1.0 : 0.0;
		}
	}

	ATKStatus status=matrix_to_rowsimplest(mat2, n, 2 * n);
	if (status != Funk_Op_OK) {
		freeContiguousArray2D(mat2);
		return status;
	}

	if (fabs(mat2[n - 1][n - 1]) < EPS) {
		freeContiguousArray2D(mat2);
		return Matrix_Singular;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat[i][j] = mat2[i][j + n];
		}
	}

	freeContiguousArray2D(mat2);
	return Funk_Op_OK;
}

void print_matrix(double** mat, int row, int col)
{
	int total = row * col;

	for (int count = 0; count < total; count++)
	{
		printf("%.3lf\t", mat[count / col][count % col]);
		if ((count + 1) % col == 0)
		{
			printf("\n");
		}
	}
}

