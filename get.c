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

void get_int(int* a)
{
	while (1)
	{
		char buf[200];
		char* p = buf;
		int used;

		if (fgets(buf, sizeof(buf), stdin) == NULL)
		{
			printf("没有检测到输入，请重新输入：\n");
			continue;
		}
		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入：\n");
			continue;
		}
		if (sscanf(p, "%d%n", a, &used) != 1)
		{
			printf("输入有问题，请重新输入：\n");
			continue;
		}
		else
		{
			p = skip_allspaces(p + used);
			if (*p != '\0')
			{
				printf("输入值太多了，请重新输入:\n");
				continue;
			}
			break;
		}
	}
}                                       //获取一个整数

void get_char(char* x)
{
	while (1)
	{
		char buf[200];
		char* p = buf;
		int used;

		if (fgets(buf, sizeof(buf), stdin) == NULL)
		{
			printf("没有检测到输入，请重新输入：\n");
			continue;
		}
		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入：\n");
			continue;
		}
		if (sscanf(p, "%c%n", x, &used) != 1)
		{
			printf("输入有问题，请重新输入：\n");
			continue;
		}
		else
		{
			p = skip_allspaces(p + used);
			if (*p != '\0')
			{
				printf("输入值不干净，请重新输入:\n");
				continue;
			}
			break;
		}
	}
}                                       //用来获取一个字符

void get_twochoice(char* x)
{
	get_char(x);
	while (*x != 'A' && *x != 'B' && *x != 'a' && *x != 'b')
	{
		printf("输入有问题，请重新选择（A/a或者B/b）：\n");
		get_char(x);
	}
}                                      //用来做获取用户的二选一