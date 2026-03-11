#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "array_alloc.h"

//获取一个自定义长度的一维数组
int* get_array(int* len)
{
	printf("请输入一维数组的长度：\n");
	get_int(len);      //通过整型指针进行赋值

	while (*len <= 0)
	{
		printf("长度必须大于0，请重新输入：\n");
		get_int(len);
	}
     
	int* arr = (int*)malloc((size_t)(*len) * sizeof(int));
	if (arr == NULL)
	{
		fprintf(stderr, "内存分配失败\n");
		return NULL;
	}
	                                                      
	// 预留足够的字符：每个int最多约11字符(含符号) + 空格；再加换行和\0,然后再多给一点
	size_t cap = (size_t)(*len) * 12 + 10;

	//创建输入缓存区
	char* buf = (char*)malloc(cap);
	if (buf == NULL)
	{
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

		if (fgets(buf, (int)cap, stdin) == NULL)
		{
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
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入：\n");
			flag = 1;
			continue;
		}

		for (index = 0; index < *len; index++)
		{
			if (sscanf(p, "%d%n", &arr[index], &used) != 1)
			{
				flag = 1;
				p = skip_allspaces(p);
				if (*p == '\0')
					printf("输入的有效数据没有%d个，请重新输入：\n",*len);
				else
					printf("输入中的'%c'为违规输入，请重新输入：\n",*p);
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
int** get_A_matrix(int* row, int* col)
{
	size_t cap, total;
	do
	{
		printf("请输入二维数组有几行：\n");
		get_int(row);
		while (*row <= 0)
		{
			printf("行数必须大于零，请重新输入：\n");
			get_int(row);
		}

		printf("请输入二维数组有几列：\n");
		get_int(col);
		while (*col <= 0)
		{
			printf("列数必须大于零，请重新输入：\n");
			get_int(col);
		}

		if (*col > INT_MAX / *row) {
			printf("请求的矩阵过大，系统分配失败，请重新规划行列数。\n");
			continue;
		}

		total = *col * *row;
		cap = total * 12 + 2;
		if (cap > (size_t)INT_MAX) {
			printf("请求的矩阵过大，系统分配失败，请重新规划行列数。\n");
			continue;
		}

		break;
	} while (1);

	//生成二维数组的行指针
	int** mat = (int**)malloc((size_t)(*row * sizeof(int*)));
	if (mat == NULL) {
		fprintf(stderr, "内存分配失败\n");
		return NULL;
	}

	//生成二维数组的总内存
	mat[0] = (int*)malloc((size_t)(total * sizeof(int)));
	if (mat[0] == NULL) {
		fprintf(stderr, "内存分配失败\n");
		free(mat);
		return NULL;
	}

	//将申请的连续内存按列数切分，计算并设置第一行到最后一行的起始地址
	for (int a = 1; a < *row; a++) {
		mat[a] = mat[0] + a * *col;
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
			if (sscanf(p, "%d%n", &mat[count / (size_t)(*col)][count % (size_t)(*col)], &used) != 1)
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

	printf("输入成功！\n");
	free(buf);
	return mat;
}                                           
