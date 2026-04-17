#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Command.h"
#include "ArrayToolkit.h"

#define INIT_OBJ(type) ((type*)calloc(1,sizeof(type)))

void print_menu()
{
	printf("这是一个数组工具交互系统\n");

}

int count_array(SystemState* state)
{
	int count = 0;
	Node* cur = state->head->next;

	while (cur != NULL) {
		if (cur->type == Array_1D) count++;
		cur = cur->next;
	}

	return count;
}                                        //

void print_Command(Menu* menu, SystemState* state)
{
	int count = count_array(state);
	printf("现在拥有%d个数组(%d个一维数组，%d个二维数组）,你可以进行以下操作：\n", state->count, count, state->count - count);
	printf("==============================================\n");
	for (int a = 0; a < menu->count; a++) {
		printf("%d.%s", a + 1, menu->cmd[a].description);
	}
}

void cmd_exit(SystemState* state)
{
	state->running = false;
}

void state_tail_insert(SystemState* state, Node* new_node)
{
	Node* cur = state->head;
	while (cur->next != NULL) {
		cur = cur->next;
	}

	cur->next = new_node;
	state->count++;
}

void cmd_get_array(SystemState* state)
{
	Node* new_node = INIT_OBJ(Node);
	assert(new_node != NULL);

	new_node->type = Array_1D;
	new_node->data.array.arr = get_array(&(new_node->data.array.len));
	if (new_node->data.array.arr == NULL) {
		free(new_node);
		return;
	}

	state_tail_insert(state, new_node);
}

void cmd_get_matrix(SystemState* state)
{
	Node* new_node = INIT_OBJ(Node);
	assert(new_node != NULL);

	new_node->type = Array_2D;
	get_matrix_dimensions(&(new_node->data.matrix.row), &(new_node->data.matrix.col));
	new_node->data.matrix.mat = get_matrix(new_node->data.matrix.row, new_node->data.matrix.col);
	if (new_node->data.matrix.mat == NULL) {
		free(new_node);
		return;
	}

	state_tail_insert(state, new_node);
}

void cmd_print_array(SystemState* state)
{
	Node* cur = state->head->next;
	int a = 1;
	while (cur != NULL) {
		printf("第%d个一维数组：",a++);
		print_array(cur->data.array.arr, cur->data.array.len);
		printf("\n");
		cur = cur->next;
	}
}




