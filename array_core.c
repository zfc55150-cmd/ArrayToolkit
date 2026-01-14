#include "array_core.h"


void print_array(int* arr, int a)
{
	for (int x = 0; x < a; x++)
	{
		printf("%d\t", arr[x]);
	}
}                                 //打印一维数组
  
void reverse_array(int* arr, int len)
{
	for (int x = 0; x < len / 2; x++)
	{
		int temp;
		temp = arr[x];
		arr[x] = arr[len - 1 - x];
		arr[len - 1 - x] = temp;
	}
}                                //逆序一维数组

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
}                                          //两种冒泡排序，升序和降序

void get_A_matrix(int (*mat)[MAX_M], int* row, int* col)
{
	printf("请输入二维数组有几行：\n");
	get_int(row);
	while (*row > MAX_M || *row <= 0)
	{
		printf("输入的行数有问题，请重新输入：\n");
		get_int(row);
	}

	printf("请输入二维数组有几列：\n");
	get_int(col);
	while (*col > MAX_M || *col <= 0)
	{
		printf("输入的列数有问题，请重新输入（0，50]：\n");
		get_int(col);
	}

	printf("请输入%d个整数：\n", (*col) * (*row));
	int flag, total;
	total = *col * *row;

	do
	{
		char buf[200];
		char* p = buf;
		int used;

		flag = 0;

		if (fgets(buf, sizeof(buf), stdin) == NULL)
		{
			printf("未检测到输入，请重新输入\n");
			flag = 1;
			continue;
		}
		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入：\n");
			flag = 1;
			continue;
		}

		for (int count = 0; count < total; count++)
		{
			if (sscanf(p, "%d%n", &mat[count / (*col)][count % (*col)], &used) != 1)
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
}                                           //用于获取自定义的二维数组，但只支持一行输入

void print_matrix(int (*mat)[MAX_M], int row, int col)
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
}                                        //用于打印二维数组

void get_B_matrix(int (*mat)[MAX_M], int* row, int* col)
{
	printf("请输入二维数组有几行：\n");
	get_int(row);
	while (*row > MAX_M || *row <= 0)
	{
		printf("输入的行数有问题，请重新输入：\n");
		get_int(row);
	}

	printf("请输入二维数组有几列：\n");
	get_int(col);
	while (*col > MAX_M || *col <= 0)
	{
		printf("输入的列数有问题，请重新输入（0，50]：\n");
		get_int(col);
	}

	printf("请输入%d个整数（以矩阵的格式输入）：\n", (*col) * (*row));

	char buf[200];
	char* p;
	int count, used, x = 0;

	while (x < *row)
	{
		if (fgets(buf, sizeof(buf), stdin) == NULL)
		{
			printf("未检测到输入，请重新输入第%d行\n", x + 1);
			continue;
		}
		p = buf;
		p = skip_allspaces(p);
		if (*p == '\0')
		{
			printf("没有输入有效数据，请重新输入第%d行：\n", x + 1);
			continue;
		}
		for (count = 0; count < *col; count++)
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
		if (count != *col)
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
	printf("输入成功！\n");
}                                       //用于获取自定义的二维数组，支持多行输入

void get_matrix(int (*mat)[MAX_M], int* row, int* col)
{
	char choice;

	printf("请输入你想要的输入方式\nA/a：一行输入\nB/b：多行输入\n");
	get_twochoice(&choice);

	if (choice == 'A' || choice == 'a')
	{
		get_A_matrix(mat, row, col);
	}
	else
	{
		get_B_matrix(mat, row, col);
	}
}                                       //用于自主选择二维数组的输入方式

void matrix_flat(int (*mat)[MAX_M], int row, int col, int* flat)
{
	int x = 0;
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			flat[x++] = mat[a][b];
		}
	}
}                                       //用来将二维数组一维化

void matrix_unflat(int (*mat)[MAX_M], int* flat, int len, int* row, int* col)
{
	int flag;

	printf("请输入要转化的二维数组的列数：\n");
	do
	{
		flag = 0;
		get_int(col);
		if (*col <= 0 || *col > MAX_M || (len / *col) > MAX_M)
		{
			printf("输入的列数范围有问题，请重新输入：\n");
			flag = 1;
			continue;
		}
		if (len % *col != 0)
		{
			printf("该一维数组没法转换成该列数的二维数组，请重新输入：\n");
			flag = 1;
			continue;
		}
	} while (flag);

	*row = len / *col;

	for (int a = 0; a < len; a++)
	{
		mat[a / *col][a % *col] = flat[a];
	}
}                                       //用来将一维数组二维化


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
}                                   //选择排序，升序

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
}                                   //选择排序，降序

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
}                                          //用来选择选择排序是升序还是降序

void array_linear_search(int* arr, int len)
{
	int values;
	printf("请输入一个要查找的元素（整数）：\n");
	get_int(&values);

	for (int a = 0; a < len; a++)
	{
		if (arr[a] == values)
		{
			printf("找到了，他是这个数组的第%d个元素\n", a + 1);
			return;
		}
	}
	printf("未在数组中找到该元素\n");
}                                        //查找自己选定的元素

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
}                                     //封装了array_linear_search()函数，使其更具有交互性

void matrix_search(int (*mat)[MAX_M], int row, int col)
{
	int flat[MAX_M * MAX_M];
	matrix_flat(mat, row, col, flat);

	int values;
	printf("请输入一个要查找的元素（整数）：\n");
	get_int(&values);

	for (int a = 0; a < row * col; a++)
	{
		if (flat[a] == values)
		{
			printf("找到了，他在这个二维数组的第%d行，第%d列\n", (a / col) + 1, (a % col) + 1);
			return;
		}
	}
	printf("未在该数组中找到该元素\n");

}                                     //用来查找二维数组中的元素

void transpose_matrix(int (*mat)[MAX_M], int* row, int* col)
{
	int mat2[MAX_M][MAX_M];

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

	int temp;
	temp = *row;
	*row = *col;
	*col = temp;
}                                     //用来转置矩阵
