#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#include "ArrayToolkit.h"
#include "Command.h"


Command no_arr_cmd[] = {
	{"获取一个一维数组\n",get_array},
	{"获取一个二维数组\n",get_matrix},
	{"退出\n",cmd_exit}
};

Command has_arr_cmd[] = {
	{"数组操作一\n",print_array},
	{"数组操作二\n",reverse_array}
};
int main(void)
{
	SetConsoleOutputCP(65001);
	SystemState state = { .running = 1,.count=0 };
	int len1 = sizeof(no_arr_cmd) / sizeof(no_arr_cmd[0]);
	int len2 = sizeof(has_arr_cmd) / sizeof(has_arr_cmd[0]);
	int choice;
	while (state.running) {
		print_menu(&state);
		if (state.count <= 0) {
			Menu menu = { no_arr_cmd,len1 };
			print_Command(&menu);
			get_valid_int(&choice);
			while (choice <= 0 || choice > len1) {
				print_Command(&menu);
				get_valid_int(&choice);
			}
			no_arr_cmd[choice - 1].execute(&state);
		}
		else {
			Menu menu = { has_arr_cmd,len2 };
			print_Command(&menu);
			get_valid_int(&choice);
			while (choice <= 0 || choice > len2) {
				print_Command(&menu);
				get_valid_int(&choice);
			}
			has_arr_cmd[choice - 1].execute(&state);
		}
	}
}
