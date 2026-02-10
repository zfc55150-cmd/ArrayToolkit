#include<stdio.h>
#include<windows.h>
#include"array_core.h"
#include"array_alloc.h"
#include"get.h"

int mat[MAX_M][MAX_M];
int flat[MAX_M * MAX_M];
 
int main(void)
{
	SetConsoleOutputCP(65001);
	int len, row, col, x, y;
	x = y = 0;
	printf("这是一个C程序，功能是整型数组的创建及其各种操作。\n");
	printf("===================================================\n");
	while (1) {
		printf("你现在有%d个一维数组，%d个二维数组。请选择以下操作：\n", x, y);
		printf("A:创建一个一维数组\nB:创建一个二维数组\nC:退出程序\n");
		char choice;
		get_char(&choice);
		switch (choice) {
		case 'A':
		case 'a': {
			int* arr = get_array(&len);
			if (!arr)
			{
				printf("生成失败，请重试\n");
				continue;
			}
			break;
		}
		case 'b':
		case 'B': {

		}
		}


		free(arr);
	}
}
