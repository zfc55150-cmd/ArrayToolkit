#include "array_alloc.h"

int* get_array(int* len)
{
	printf("请输入一维数组的长度：\n");
	get_int(len);

	while (*len <= 0)
	{
		printf("长度必须大于0，请重新输入：\n");
		get_int(len);
	}

	printf("请输入%d个整数：\n", *len);

	int* arr = (int*)malloc((size_t)(*len) * sizeof(int));
	if (arr == NULL)
	{ 
		fprintf(stderr, "内存分配失败\n");
		return NULL;
	} 
	
	// 预留足够的字符：每个int最多约11字符(含符号) + 空格；再加换行和\0
	size_t cap = (size_t)(*len) * 12 + 2;

	int flag;
	do
	{
		char* buf = (char*)malloc(cap);
		if (buf == NULL)
		{
			fprintf(stderr, "内存分配失败\n");
			free(arr);
			return NULL;
		}

		char* p = buf;
		int used, index;
		flag = 0;

		if (fgets(buf, (int)cap, stdin) == NULL)
		{
			printf("没有检测到输入,请重新输入：\n");
			free(buf);
			flag = 1;
			continue;
		}

		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入：\n");
			free(buf);
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
					printf("输入的有效数据不够，请重新输入：\n");
				else
					printf("输入中有违规输入，请重新输入：\n");
				break;
			}
			p += used;
		}

		if (!flag)
		{
			p = skip_allspaces(p);
			if (*p != '\0')
			{
				printf("输入数据过多,请重新输入%d个数字：\n", *len);
				flag = 1;
			}
		}

		free(buf);

	} while (flag);

	return arr;
}                                 //获取一个自定义长度的一维数组
一个编码问题搞半天，我也是无语了
