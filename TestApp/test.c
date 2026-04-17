#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#include "ArrayToolkit.h"
#include "Command.h"

Command no_arr_cmd[] = {
	{"获取一个一维数组\n",cmd_get_array},
	{"获取一个二维数组\n",cmd_get_matrix},
	{"退出\n",cmd_exit}
};

Command has_arr_cmd[] = {
	{"获取一个一维数组\n",cmd_get_array},
	{"获取一个二维数组\n",cmd_get_matrix},
	{"打印一维数组\n",cmd_print_array},
	{ "退出\n",cmd_exit }
};

int main(void)
{
	SetConsoleOutputCP(65001);
	SystemState state = { .running = 1,.count=0 };
	state.head = (Node*)calloc(1, sizeof(Node));
	if (state.head == NULL) {
		printf("离谱，头指针生成失败\n");
		exit(1);
	}
	 
	int len1 = sizeof(no_arr_cmd) / sizeof(no_arr_cmd[0]);
	int len2 = sizeof(has_arr_cmd) / sizeof(has_arr_cmd[0]);
	int choice;
	print_menu();
	while (state.running) {
		if (state.count <= 0) {
			Menu menu = { no_arr_cmd,len1 };
			print_Command(&menu,&state);
			get_valid_int(&choice);
			while (choice <= 0 || choice > len1) {
				print_Command(&menu,&state);
				get_valid_int(&choice);
			}
			no_arr_cmd[choice - 1].execute(&state);
		}
		else {
			Menu menu = { has_arr_cmd,len2 };
			print_Command(&menu,&state);
			get_valid_int(&choice);
			while (choice <= 0 || choice > len2) {
				print_Command(&menu,&state);
				get_valid_int(&choice);
			}
			has_arr_cmd[choice - 1].execute(&state);
		}
	}
	printf("程序运行结束，正常退出\n");
}
