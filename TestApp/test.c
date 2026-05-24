#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#include "ArrayToolkit.h"
#include "Command.h"

Command cmd[] = {
    {"获取一个一维数组",cmd_get_array,always_available},
	{"获取一个二维数组",cmd_get_array2D,always_available},
	{"获取一个自定义矩阵",cmd_get_matrix,always_available},
	{"打印一个一维数组",cmd_print_array,has_array1D},
	{"打印一个二维数组",cmd_print_array2D,has_array2D},
	{"打印一个矩阵",cmd_print_matrix,has_matrix},
	{"将一维数组按大小进行排序",cmd_array_sort,has_array1D},
	{"计算一个方阵的行列式",cmd_calculate_det,has_matrix},
	{"求一个矩阵的秩",cmd_matrix_rank,has_matrix},
	{"选择一个矩阵进行转置",cmd_matrix_transpose,has_matrix},
	{"选择一个方阵进行求逆",cmd_inverse_matrix,has_matrix},
	{"选择一个矩阵将它化成行阶梯形",cmd_matrix_to_rowechelon,has_matrix},
	{"选择一个矩阵将他化成行最简形",cmd_matrix_to_rowsimplest,has_matrix},
	{ "退出",cmd_exit ,always_available}
};

int main(void)
{
	SetConsoleOutputCP(65001);
	SystemState state = { .running = 1,.count = 0 ,.stats = (DataStats){0} };
	state.head = (Node*)calloc(1, sizeof(Node));
	if (state.head == NULL) {
		printf("离谱，头指针生成失败\n");
		exit(1);
	}

	int len = sizeof(cmd) / sizeof(cmd[0]);
	int choice;
	print_menu();
	while (state.running) {
			Menu menu = { cmd,len };
			print_Command(&menu, &state);
			get_valid_int(&choice);
			while (choice <= 0 || choice > len||!(menu.cmd[choice-1].is_available(&state))) {
				print_Command(&menu, &state);
				get_valid_int(&choice);
			}
			cmd[choice - 1].execute(&state);
	}
	printf("程序运行结束，正常退出\n");
}
