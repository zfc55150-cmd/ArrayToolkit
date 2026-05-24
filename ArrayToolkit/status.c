#include <stdio.h>

#include "status.h"

void print_ATK_Err(ATKStatus status)
{
	switch (status) {
	case Funk_Param_Err: printf("函数参数输入错误\n"); break;
	case Matrix_InvalidSize: printf("矩阵的大小有问题\n"); break;
	case Matrix_Alloc_Failed: printf("矩阵分配内存失败\n"); break;
	case Matrix_Input_EOF: printf("矩阵获取时输入流关闭\n"); break;
	case Matrix_TooLarge: printf("矩阵申请的太大了\n"); break;
	case Matrix_Output_NULL: printf("矩阵指针指向NULL\n"); break;
	case Matrix_Input_Empty: printf("获取矩阵时输入为空\n"); break;
	case Matrix_Input_NotEnough: printf("获取矩阵时输入的有效数据不够\n"); break;
	case Matrix_Input_InvalidData: printf("获取矩阵时输入非法数据\n"); break;
	case Matrix_Input_TooMany: printf("矩阵获取时输入太多数据了\n"); break;
	case Matrix_Singular: printf("矩阵为奇异矩阵，不可逆\n"); break;
	case Array_Input_NULL: printf("数组指针指向NULL\n"); break;
	case Arrray_InvalidSize: printf("数组申请的大小有问题\n"); break;
	case String_Input_NULL: printf("输入的字符串指针的地址为NULL\n"); break;
	case String_Alloc_Failed: printf("获取字符串时动态分配内存失败\n"); break;
	case String_Input_EOF:printf("获取字符串时输入流关闭\n"); break;
	default:printf("未知错误\n");
	}
}