#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

int main(void)
{
	SetConsoleOutputCP(65001);
	int len;
	printf("数组长度:\n");
	scanf("%d", &len);

	int arr[1000];
	for (int a = 0; a < len; a++) {
		scanf("%d", &arr[a]);
	}

	for (int a = 0; a < len; a++) {
		for (int b = 0; b < len - a - 1; b++) {
			if (arr[b] < arr[b + 1]) {
				int temp = arr[b];
				arr[b] = arr[b + 1];
				arr[b + 1] = temp;
			}
		}
	}

	for (int a = 0; a < len; a++) {
		printf("%-2d ", arr[a]);
	}
}