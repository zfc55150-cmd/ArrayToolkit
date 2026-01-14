#include<stdio.h>
#include"array_core.h"
#include"array_alloc.h"
#include"get.h"

int mat[MAX_M][MAX_M];
int flat[MAX_M * MAX_M];

int main(void)
{
	int len, row, col;
	int* arr=get_array(&len);
	if(!arr)
	{
		return 1;
	}
	printf("输入的一维数组为：\n");	
	print_array(arr, len);
	free(arr);	
	return 0;
}
//#include<stdio.h>
//#include<stdlib.h>
//
//int main(void)
//{
//	int n;
//	printf("请输入想要的数组大小：\n");
//	scanf("%d", &n);
//	if (!n) {
//		fprintf(stderr, "数组大小要大于零\n");
//		return 1;
//	}
//	int* arr = malloc(n * sizeof(*arr));
//	if (!arr) {
//		fprintf(stderr, "动态数组生成失败\n");
//		return 1;
//	}
//	printf("输入%d个整数：\n",n);
//	for (int a = 0; a < n; a++) {
//		scanf("%d", arr + a);
//	}
//	printf("输入你想要扩容多少\n");
//	int p;
//	scanf("%d", &p);
//	if (!p) {
//		fprintf(stderr, "扩容的大小要大于零\n");
//		free(arr);
//		return 1;
//	}
//	int* temp = realloc(arr, (n + p) * sizeof(*arr));
//	if (!temp) {
//		fprintf(stderr, "扩容失败\n");
//		free(arr);
//		return 1;
//	}
//	arr = temp;
//	printf("输入%d个整数：\n",p);
//	for (int a = 0; a < p; a++) {
//		scanf("%d", arr + n + a);
//	}
//	n += p;
//	for (int a = 0; a < n; a++) {
//		printf("%d ", *(arr + a));
//	}
//	free(arr);
//	arr = NULL;
//	return 0;
//}