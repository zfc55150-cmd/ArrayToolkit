#include<stdio.h>
#include<stdlib.h>
#include "array_alloc.h"

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
}                                 //获取一个自定义长度的一维数组
