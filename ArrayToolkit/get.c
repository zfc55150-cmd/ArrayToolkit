#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include "get.h"

char* skip_midspaces(char* x)
{
	while (*x == ' ' || *x == '\t')
	{
		x++;
	}
	return x;
}                       //跳过空格和Tab键

char* skip_allspaces(char* x)
{
	while (*x == ' ' || *x == '\t' || *x == '\n')
	{
		x++;
	}
	return x;
}                       //跳过空格、Tab键和回车键

//通过整型指针给整型数据赋值
int get_int(int* a)
{
	char buf[200];
	char* p = buf;
	int used;

	if (fgets(buf, sizeof(buf), stdin) == NULL)
	{
		return -1;        //未检测到输入
	}

	if (strchr(buf, '\n') == NULL && !feof(stdin)) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
		return -2;
	}                     //输入被截断

	p = skip_allspaces(p);
	if (*p == '\0')
	{
		return -3;        //输入为空
	}

	if (sscanf(p, "%d%n", a, &used) != 1)
	{
		return -4;        //输入数据有问题
	}

	else
	{
		p = skip_allspaces(p + used);
		if (*p != '\0')
		{
			return -5;     //输入数据过多
		}
	}

	return 1;
}

//交互式获取合法整数，直至成功或程序退出
void get_valid_int(int* x)
{
	while (1)
	{
		int status = get_int(x);
		if (status == 1) {
			break;
		}

		switch (status) {
		case -1:printf("检测到输入流关闭，请重新运行程序\n"); exit(1);
		case -2:printf("输入太长了,请重新输入：\n"); break;
		case -3:printf("未检测到有效输入，请重新输入：\n"); break;
		case -4:printf("输入数据格式不对，请输入整型数据：\n"); break;
		case -5:printf("输入数据过多，请重新输入一个整型数据：\n"); break;
		default:printf("发现了未知错误\n"); exit(1);
		}
	}
}

//用来获取一个字符
int get_char(char* x)
{
	char buf[200];
	char* p = buf;
	int used;

	if (fgets(buf, sizeof(buf), stdin) == NULL)
	{
		return -1;              //未检测到输入
	}

	if (strchr(buf, '\n') == NULL && !feof(stdin)) {
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
		return -2;             //输入过长被截断
	}

	p = skip_allspaces(p);
	if (*p == '\0')
	{
		return -3;             //输入为空
	}

	if (sscanf(p, "%c%n", x, &used) != 1)
	{
		return -4;             //输入数据格式有问题
	}

	else
	{
		p = skip_allspaces(p + used);
		if (*p != '\0')
		{
			return -5;          //输入数据过多
		}
	}

	return 1;
}

//交互式获取合法字符，直至成功或程序退出
void get_valid_char(char* x)
{
	while (1)
	{
		int status = get_char(x);
		if (status == 1) {
			break;
		}

		switch (status) {
		case -1:printf("检测到输入流关闭，请重新运行程序\n"); exit(1);
		case -2:printf("输入太长了,请重新输入：\n"); break;
		case -3:printf("未检测到有效输入，请重新输入：\n"); break;
		case -4:printf("输入数据格式不对，请输入字符类型数据：\n"); break;
		case -5:printf("输入数据过多，请重新输入一个字符类型数据：\n"); break;
		default:printf("发现了未知错误\n"); exit(1);
		}
	}

}

void get_twochoice(char* x)
{
	get_valid_char(x);
	while (*x != 'A' && *x != 'B' && *x != 'a' && *x != 'b')
	{
		printf("输入有问题，请重新选择（A/a或者B/b）：\n");
		get_valid_char(x);
	}
}                                      //用来做获取用户的二选一

void get_array_len(int* len)
{

}

//用来获取二维数组的行列数
void get_matrix_dimensions(int* row, int* col)
{
	size_t cap, total;
	do
	{
		printf("请输入二维数组有几行：\n");
		get_valid_int(row);
		while (*row <= 0)
		{
			printf("行数必须大于零，请重新输入：\n");
			get_valid_int(row);
		}

		printf("请输入二维数组有几列：\n");
		get_valid_int(col);
		while (*col <= 0)
		{
			printf("列数必须大于零，请重新输入：\n");
			get_valid_int(col);
		}

		if (*col > INT_MAX / *row) {
			printf("请求的矩阵过大，系统分配失败，请重新规划行列数。\n");
			continue;
		}

		total = (size_t)*col * *row;
		cap = total * 12 + 2;
		if (cap > (size_t)INT_MAX) {
			printf("请求的矩阵过大，系统分配失败，请重新规划行列数。\n");
			continue;
		}

		break;
	} while (1);
}