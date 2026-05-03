#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "get.h"
#include "array_alloc.h"



//获取一个自定义长度的一维数组
int* get_array(int* len)
{
	printf("请输入一维数组的长度：\n");
	get_valid_int(len);      //通过整型指针进行赋值

	while (*len <= 0) {
		printf("长度必须大于0，请重新输入：\n");
		get_valid_int(len);
	}

	int* arr = (int*)malloc((size_t)(*len) * sizeof(int));
	if (arr == NULL) {
		fprintf(stderr, "内存分配失败\n");
		return NULL;
	}

	// 预留足够的字符：每个int最多约11字符(含符号) + 空格；再加换行和\0,然后再多给一点
	size_t cap = (size_t)(*len) * 12 + 10;

	//创建输入缓存区
	char* buf = (char*)malloc(cap);
	if (buf == NULL) {
		fprintf(stderr, "缓存区内存分配失败\n");
		free(arr);
		return NULL;
	}

	printf("请输入%d个整数：\n", *len);
	int flag;
	do
	{
		char* p = buf;
		int used, index;
		flag = 0;

		if (fgets(buf, (int)cap, stdin) == NULL) {
			printf("没有检测到输入,出问题了：\n");
			free(arr);
			free(buf);
			return NULL;
		}

		//是否因输入长度过长被截断检测
		size_t buf_len = strlen(buf);
		if (buf_len > 0 && buf[buf_len - 1] != '\n') {
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
			printf("输入数据的长度有问题，长度太长了，请重新输入：\n");
			flag = 1;
			continue;
		}

		//输入是否为空检测
		p = skip_allspaces(p);
		if (*p == '\0') {
			printf("没有输入有效数据，请重新输入：\n");
			flag = 1;
			continue;
		}

		for (index = 0; index < *len; index++) {
			if (sscanf(p, "%d%n", &arr[index], &used) != 1)
			{
				flag = 1;
				p = skip_allspaces(p);
				if (*p == '\0')
					printf("输入的有效数据没有%d个，请重新输入：\n", *len);
				else
					printf("输入中的'%c'为违规输入，请重新输入：\n", *p);
				break;
			}
			p += used;
		}

		//输入数据超过所需要的
		if (!flag)
		{
			p = skip_allspaces(p);
			if (*p != '\0')
			{
				printf("输入数据过多,请重新输入%d个数字：\n", *len);
				flag = 1;
			}
		}

	} while (flag);

	free(buf);
	return arr;
}

//用于获取自定义的二维数组，但只支持一行输入
int** get_A_array2D(int row, int col)
{
	size_t total, cap;
	total = (size_t)row * col;
	cap = total * 12 + 2;

	//动态生成二维数组
	int** mat = (int**)createContiguousArray2D(row, col, sizeof(int));
	if (mat == NULL) {
		printf("二维数组生成失败，出问题了\n");
		return NULL;
	}

	//计算并生成缓存区可能的最大内存
	int flag;
	char* buf = (char*)malloc(cap);
	if (buf == NULL) {
		fprintf(stderr, "缓存区内存分配失败\n");
		free(mat[0]);
		free(mat);
		return NULL;
	}

	printf("请输入%zu个整数：\n", total);
	do
	{
		char* p = buf;
		int used;

		flag = 0;

		if (fgets(buf, (int)cap, stdin) == NULL)
		{
			printf("未检测到输入，出问题了：\n");
			free(mat[0]);
			free(mat);
			free(buf);
			return NULL;
		}

		//是否因输入长度过长被截断检测
		size_t len_buf = strlen(buf);
		if (len_buf > 0 && buf[len_buf - 1] != '\n') {
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
			if (c == EOF) {
				printf("检测到EOF，输入终止\n");
				free(buf);
				free(mat[0]);
				free(mat);
				return NULL;
			}
			printf("输入长度过长，请重新输入：\n");
			flag = 1;
			continue;
		}

		//输入空检测
		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入：\n");
			flag = 1;
			continue;
		}

		//将输入映射到二维数组上
		for (size_t count = 0; count < total; count++)
		{
			if (sscanf(p, "%d%n", &mat[count / (size_t)col][count % (size_t)col], &used) != 1)
			{
				flag = 1;
				p = skip_allspaces(p);
				if (*p == '\0')
				{
					printf("输入的有效数据不够，请重新输入\n");
					break;
				}
				else
				{
					printf("输入中有违规数据，请重新输入：\n");
					break;
				}
			}
			else
			{
				p += used;
			}
		}

		if (flag)
		{
			continue;
		}

		//判断输入数据是多于所需要的
		else
		{
			p = skip_allspaces(p);
			if (*p != '\0')
			{
				printf("输入数据过多，请重新输入：\n");
				flag = 1;
			}
		}

	} while (flag);

	free(buf);
	return mat;
}

//用于获取自定义的二维数组，多行输入
int** get_B_array2D(int row, int col)
{
	size_t cap, total;
	total = (size_t)row * col;
	cap = (size_t)col * 12 + 2;

	//动态生成二维数组
	int** mat = (int**)createContiguousArray2D(row, col, sizeof(int));
	if (mat == NULL) {
		printf("二维数组生成失败，出问题了\n");
		return NULL;
	}

	//生成缓存区内存
	char* buf = (char*)malloc(cap);
	if (buf == NULL) {
		printf("缓存区内存分配失败\n");
		free(mat[0]);
		free(mat);
		return NULL;
	}

	char* p;
	int count, used, x = 0;
	printf("请输入%zu个整数（以矩阵的格式输入）：\n", total);

	//将输入一行行录入
	while (x < row)
	{
		if (fgets(buf, (int)cap, stdin) == NULL)
		{
			printf("未检测到输入，出问题了\n");
			free(buf);
			free(mat[0]);
			free(mat);
			return NULL;
		}

		//是否因输入过长被截断检测
		size_t len_buf = strlen(buf);
		if (len_buf > 0 && buf[len_buf - 1] != '\n') {
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
			if (c == EOF) {
				printf("检测到EOF，输入终止\n");
				free(buf);
				free(mat[0]);
				free(mat);
				return NULL;
			}
			printf("输入长度过长，请重新输入：\n");
			continue;
		}

		//输入是否为空检测
		p = buf;
		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入第%d行：\n", x + 1);
			continue;
		}

		for (count = 0; count < col; count++)
		{
			if (sscanf(p, "%d%n", &mat[x][count], &used) != 1)
			{
				p = skip_allspaces(p);
				if (*p == '\0')
				{
					printf("输入的有效数据不够，请重新输入第%d行：\n", x + 1);
					break;
				}
				else
				{
					printf("输入中有违规数据，请重新输入第%d行：\n", x + 1);
					break;
				}
			}
			else
			{
				p += used;
			}
		}
		if (count != col)
		{
			continue;
		}
		p = skip_allspaces(p);
		if (*p != '\0')
		{
			printf("输入的数据过多，请重新输入第%d行：\n", x + 1);
			continue;
		}
		x++;
	}

	free(buf);
	return mat;
}

//用于自主选择二维数组的输入方式
int** get_array2D(int row, int col)
{
	char choice;

	printf("请输入你想要的输入方式\nA/a：一行输入\nB/b：多行输入\n");
	get_twochoice(&choice);

	if (choice == 'A' || choice == 'a') {
		return get_A_array2D(row, col);
	}
	else {
		return get_B_array2D(row, col);
	}
}

static MatrixInputStatus check_matrix_size(int row, int col, size_t* total, size_t* cap)
{
	if (total == NULL || cap == NULL) {
		return Matrix_Input_NULL;
	}

	if (row <= 0 || col <= 0) {
		return Matrix_InvalidSize;
	}

	*total = (size_t)row * (size_t)col;
	if (*total > 1000000) {
		return Matrix_TooLarge;
	}
	*cap = *total * 64 + 2;         //每个double类型预留64个位置

	return Matrix_Input_OK;
}

static MatrixInputStatus parse_matrix_line(char* line, double** mat, int row, int col)
{
	if (line == NULL || mat == NULL) {
		return Matrix_Input_NULL;
	}

	if (row <= 0 || col <= 0) {
		return Matrix_InvalidSize;
	}

	int used = 0;
	size_t total = (size_t)row * (size_t)col;

	//输入空检测
	char* p = skip_allspaces(line);
	if (*p == '\0') {
		return Matrix_Input_Empty;
	}

	//将输入映射到二维数组上
	for (size_t count = 0; count < total; count++) {
		if (sscanf(p, "%lf%n", &mat[count / (size_t)col][count % (size_t)col], &used) != 1) {
			p = skip_allspaces(p);
			if (*p == '\0') {
				return Matrix_Input_NotEnough;
			}
			else {
				return Matrix_Input_InvalidData;
			}
		}
		else {
			p += used;
		}
	}

	p = skip_allspaces(p);
	if (*p != '\0') {
		return Matrix_Input_TooMany;
	}

	return Matrix_Input_OK;
}

static void print_matrix_input_error(MatrixInputStatus status)
{
	switch (status) {
	case Matrix_Input_OK:
		break;
	case Matrix_Alloc_Failed:
		printf("内存分配失败\n");
		break;
	case Matrix_Input_Empty:
		printf("没有输入有效数据\n");
		break;
	case Matrix_Input_EOF:
		printf("输入结束或读取失败\n");
		break;
	case Matrix_InvalidSize:
		printf("输入行列数非法\n");
		break;
	case Matrix_Input_NotEnough:
		printf("输入的有效数据不够\n");
		break;
	case Matrix_Output_NULL:
		printf("程序错误，函数输出参数传入空指针\n");
		break;
	case Matrix_Input_TooMany:
		printf("输入数据太多了\n");
		break;
	case Matrix_TooLarge:
		printf("申请矩阵规模过大\n");
		break;
	case Matrix_Input_NULL:
		printf("程序错误，解析时传入空指针\n");
		break;
	case Matrix_Input_InvalidData:
		printf("输入中有非法数据\n");
		break;
	default:
		printf("未知错误，退出检查一下吧\n");
		break;
	}
}

static MatrixInputStatus parse_matrix_row_line(char* line, double* mat_row, int col)
{
	if (line == NULL || mat_row == NULL) {
		return Matrix_Input_NULL;
	}

	if (col <= 0) {
		return Matrix_InvalidSize;
	}

	int used = 0;
	size_t total = (size_t)col;

	//输入空检测
	char* p = skip_allspaces(line);
	if (*p == '\0') {
		return Matrix_Input_Empty;
	}

	//将输入映射到二维数组上
	for (size_t count = 0; count < total; count++) {
		if (sscanf(p, "%lf%n", &mat_row[count], &used) != 1) {
			p = skip_allspaces(p);
			if (*p == '\0') {
				return Matrix_Input_NotEnough;
			}
			else {
				return Matrix_Input_InvalidData;
			}
		}
		else {
			p += used;
		}
	}

	p = skip_allspaces(p);
	if (*p != '\0') {
		return Matrix_Input_TooMany;
	}

	return Matrix_Input_OK;
}

//用于获取自定义的矩阵，但只支持一行输入
MatrixInputStatus get_A_matrix(double*** output_mat, int row, int col)
{
	if (output_mat == NULL) {
		return Matrix_Output_NULL;
	}

	*output_mat = NULL;

	size_t total, cap;
	MatrixInputStatus check_status = check_matrix_size(row, col, &total, &cap);
	if (check_status != Matrix_Input_OK) {
		return check_status;
	}

	//动态生成二维数组
	double** mat = (double**)createContiguousArray2D(row, col, sizeof(double));
	if (mat == NULL) {
		fprintf(stderr, "矩阵内存分配失败，出问题了\n");
		return Matrix_Alloc_Failed;
	}

	//计算并生成缓存区可能的最大内存
	char* buf = (char*)malloc(cap);
	if (buf == NULL) {
		fprintf(stderr, "缓存区内存分配失败\n");
		freeContiguousArray2D(mat);
		return Matrix_Alloc_Failed;
	}

	while (1) {
		printf("输入%zu个实数：\n", total);
		if (fgets(buf, (int)cap, stdin) == NULL) {
			freeContiguousArray2D(mat);
			free(buf);
			return Matrix_Input_EOF;
		}

		//是否因输入长度过长被截断检测
		size_t len_buf = strlen(buf);
		if (len_buf > 0 && buf[len_buf - 1] != '\n' && len_buf == cap - 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
			if (c == EOF) {
				freeContiguousArray2D(mat);
				free(buf);
				return Matrix_Input_EOF;
			}
			printf("输入内容过长,导致输入被截断了\n");
			continue;
			
		}

		MatrixInputStatus parse_status = parse_matrix_line(buf, mat, row, col);
		if (parse_status == Matrix_Input_OK) break;
		print_matrix_input_error(parse_status);
		printf("请重新");
	}

	free(buf);
	*output_mat = mat;
	return Matrix_Input_OK;
}

//用于获取自定义的二维数组，多行输入
MatrixInputStatus get_B_matrix(double*** output_mat, int row, int col)
{
	if (output_mat == NULL) {
		return Matrix_Output_NULL;
	}

	*output_mat = NULL;

	size_t cap, total;
	MatrixInputStatus status = check_matrix_size(row, col, &total, &cap);
	if (status != Matrix_Input_OK) {
		return status;
	}
	cap = (size_t)col * 64 + 2;

	//动态生成二维数组
	double** mat = (double**)createContiguousArray2D(row, col, sizeof(double));
	if (mat == NULL) {
		return Matrix_Alloc_Failed;
	}

	//生成缓存区内存
	char* buf = (char*)malloc(cap);
	if (buf == NULL) {
		freeContiguousArray2D(mat);
		return Matrix_Alloc_Failed;
	}

	int x = 0;
	printf("请输入%zu个实数（以矩阵的格式输入）：\n", total);

	//将输入一行行录入
	while (x < row) {
		if (fgets(buf, (int)cap, stdin) == NULL) {
			free(buf);
			freeContiguousArray2D(mat);
			return Matrix_Input_EOF;
		}

		//是否因输入过长被截断检测
		size_t len_buf = strlen(buf);
		if (len_buf > 0 && buf[len_buf - 1] != '\n' && len_buf == cap - 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
			if (c == EOF) {
				free(buf);
				freeContiguousArray2D(mat);
				return Matrix_Input_EOF;
			}
			printf("输入长度过长，请重新输入第%d行\n",x+1);
			continue;
		}

		MatrixInputStatus parse_status = parse_matrix_row_line(buf, mat[x],col);
		if (parse_status == Matrix_Input_OK) x++;

		else {
			print_matrix_input_error(parse_status);
			printf("请重新输入第%d行\n", x + 1);
		}
	}

	free(buf);
	*output_mat = mat;
	return Matrix_Input_OK;
}

//用于自主选择矩阵的输入方式
double** get_matrix(int row, int col)
{
	char choice;
	double** mat = NULL;

	printf("请输入你想要的输入方式\nA/a：一行输入\nB/b：多行输入\n");
	get_twochoice(&choice);

	if (choice == 'A' || choice == 'a') {
		if (get_A_matrix(&mat, row, col) == Matrix_Input_OK) {
			return mat;
		}
		return NULL;
	}
	else {
		if (get_B_matrix(&mat, row, col) == Matrix_Input_OK) {
			return mat;
		}
		return NULL;
	}
}

//用于创建一个连续存储的二维数组
void** createContiguousArray2D(int row, int col, size_t element_size)
{
	//生成二维数组的行指针
	void** mat = (void**)malloc((size_t)row * sizeof(void*));
	if (mat == NULL) {
		return NULL;
	}

	//生成二维数组的总内存
	char* data = (char*)malloc((size_t)row * col * element_size);
	if (data == NULL) {
		free(mat);
		return NULL;
	}

	//将申请到的内存按列数切分，计算并设置第一行到最后一行的起始地址
	for (int a = 0; a < row; a++) {
		mat[a] = (void*)(data + a * col * element_size);
	}

	return mat;
}

//用于释放一个连续存储的二维数组的内存
void freeContiguousArray2D(void** mat)
{
	if (mat != NULL) {
		free(mat[0]);
		free(mat);
	}
}

//用来获取一个自定义大小的方阵
double** get_determinant(int* n)
{
	do {
		printf("请输入行列式是几阶的\n");
		get_valid_int(n);

		if (*n > 0) {
			break;
		}
		printf("行列式大小要大于零，请重新输入\n");
	} while (1);
	double** mat = get_matrix(*n, *n);

	return mat;
}
