#include <stdbool.h>
#include <stdio.h>

#include "Command.h"
#include "ArrayToolkit.h"

#define INIT_OBJ(type) ((type*)calloc(1,sizeof(type)))

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

void cmd_get_array(SystemState* state)
{
	Node* new_node = INIT_OBJ(Node);
	new_node->type = Array_1D;
	new_node->data.array.arr = get_array(&(new_node->data.array.len));
	if (new_node->data.array.arr == NULL) {
		free(new_node);
		return;
	}

	Node* cur = state->head;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	
	cur->next = new_node;
	state->count++;
}

