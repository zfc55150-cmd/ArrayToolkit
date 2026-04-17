#ifndef Command_h
#define Command_h

#include "ArrayToolkit.h"

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
	Array1D array;
	Array2D matrix;
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

typedef void (*commandfunc) (SystemState* state);

typedef struct {
	const char* description;
	commandfunc execute;
}Command;

typedef struct {
	Command* cmd;
	int count;
}Menu;

void print_menu(SystemState* state);
void print_Command(Menu* menu);
void cmd_exit(SystemState* state);
void cmd_get_array(SystemState* state);

#endif
