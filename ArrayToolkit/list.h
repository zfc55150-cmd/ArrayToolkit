#ifndef list_h
#define list_h

#include <stdbool.h>

//用来存储一维数组信息
typedef struct {
	int* arr;
	int len;
}Array1D;

//用来存储二维数组信息
typedef struct {
	int** arr;
	int row;
	int col;
}Array2D;

typedef struct {
	int** mat;
	int row;
	int col;
}Matrix;

//用来存储数组类型信息
typedef enum {
	Array_1D,
	Array_2D,
	matrix
}ArrayType;

//用来存储一维数组或二维数组
typedef union {
	Array1D array1D;
	Array2D array2D;
	Matrix matrix;
}ArrayData;

//用链表来存储数组链表
typedef struct Node{
	ArrayType type;
	ArrayData data;
	struct Node* next;
}Node;

typedef struct {
	int array1D_count;
	int array2D_count;
	int matrix_count;
}DataStats;

//系统状态栏
typedef struct {
	Node* head;
	int count;
	bool running;
	DataStats stats;
}SystemState;

typedef void (*commandfunc) (SystemState* state);
typedef bool (*checkfunc) (const SystemState* state);

typedef struct {
	const char* description;
	commandfunc execute;
	checkfunc is_available;
}Command;

typedef struct {
	Command* cmd;
	int count;
}Menu;

void free_list(Node* head);
Node* get_arrlist(int len);
void print_arrlist(Node* head);

#endif
