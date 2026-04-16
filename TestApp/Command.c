#include <stdbool.h>
#include <stdio.h>

#include "Command.h"


//用来存储一维数组信息
typedef struct {
	int* arr;
	int len;
}Array1D;

//用来存储二维数组信息
typedef struct {
	int** mat;
	int row;
	int col;
}Array2D;

//用来存储数组类型信息
typedef enum {
	Array_1D,
	Array_2D
}ArrayType;

//用来存储一维数组或二维数组
typedef union {
	Array1D arr;
	Array2D mat;
}ArrayData;

//用链表来存储数组链表
typedef struct Node {
	ArrayType type;
	ArrayData data;
	struct Node* next;
}Node;

//系统状态栏
typedef struct {
	Node* head;
	int count;
	bool running;
}SystemState;



typedef struct {
	const char* description;
	commandfunc execute;
}Command;

typedef struct {
	Command* cmd;
	int count;
}Menu;

void print_menu(SystemState* state)
{
	printf("这是一个数组工具交互系统\n");
	printf("现在拥有%d个数组,你可以进行以下操作：\n", state->count);
	printf("==============================================\n");
}

void print_Command(Menu* menu)
{
	for (int a = 0; a < menu->count; a++) {
		printf("%d.%s", a + 1, menu->cmd[a].description);
	}
}

void cmd_exit(SystemState* state)
{
	state->running = false;
}

