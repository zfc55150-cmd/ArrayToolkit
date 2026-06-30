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

void print_Command(Menu* menu, SystemState* state)
{
	printf("现在拥有%d个不同数据(%d个一维数组，%d个二维数组和%d个矩阵),你可以进行以下操作：\n",
		state->count,
		state->stats.array1D_count,
		state->stats.array2D_count,
		state->stats.matrix_count);
	printf("==============================================\n");
	for (int a = 0; a < menu->count; a++) {
		bool check = true;
		if (menu->cmd[a].is_available != NULL) {
			check = menu->cmd[a].is_available(state);
		}

		printf("%d.%s", a + 1, menu->cmd[a].description);
		if (!check) {
			printf("（当前状态不可用）");
		}
		printf("\n");
	}
}

void cmd_exit(SystemState* state)
{
	state->running = false;
}

bool always_available(const SystemState* head)
{
	return true;
}

bool has_array1D(const SystemState* state)
{
	if (state->stats.array1D_count > 0)
		return true;
	return false;
}

bool has_array2D(const SystemState* state)
{
	if (state->stats.array2D_count > 0)
		return true;
	return false;
}

bool has_matrix(const SystemState* state)
{
	if (state->stats.matrix_count > 0)
		return true;
	return false;
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
	if (new_node == NULL) {
		printf("节点内存分配失败\n");
		return;
	}

	new_node->type = Array_1D;
	new_node->data.array1D.arr = get_array(&(new_node->data.array1D.len));
	if (new_node->data.array1D.arr == NULL) {
		free(new_node);
		return;
	}

	state->stats.array1D_count++;
	state_tail_insert(state, new_node);
}

void cmd_get_array2D(SystemState* state)
{
	Node* new_node = INIT_OBJ(Node);
	if (new_node == NULL) {
		printf("节点内存分配失败\n");
		return;
	}

	new_node->type = Array_2D;
	get_array2D_dimensions(&(new_node->data.array2D.row), &(new_node->data.array2D.col));
	new_node->data.array2D.arr = get_array2D(new_node->data.array2D.row, new_node->data.array2D.col);
	if (new_node->data.array2D.arr == NULL) {
		free(new_node);
		return;
	}

	state->stats.array2D_count++;
	state_tail_insert(state, new_node);
}

static Node* find_nth_array1D(Node* head, int n)
{
	if (head == NULL || n < 1) return NULL;

	Node* cur = head->next;
	while (cur != NULL) {
		if (cur->type == Array_1D) {
			n--;
			if (n == 0) return cur;
		}

		cur = cur->next;
	}

	return NULL;
}

static Node* find_nth_array2D(Node* head, int n)
{
	if (head == NULL || n < 1) return NULL;

	Node* cur = head->next;
	while (cur != NULL) {
		if (cur->type == Array_2D) {
			n--;
			if (n == 0) return cur;
		}

		cur = cur->next;
	}

	return NULL;
}

static Node* find_nth_matrix(Node* head, int n)
{
	if (head == NULL || n < 1) return NULL;

	Node* cur = head->next;
	while (cur != NULL) {
		if (cur->type == matrix) {
			n--;
			if (n == 0) return cur;
		}

		cur = cur->next;
	}

	return NULL;
}

void cmd_print_array(SystemState* state)
{
	if (state->stats.array1D_count == 0)
	{
		printf("还没有一维数组，请先创建一个吧\n");
		return;
	}

	Node* cur;
	int index;
	if (state->stats.array1D_count == 1) {
		cur = find_nth_array1D(state->head, 1);
		if (cur == NULL) {
			printf("数据出问题了，退出吧\n");
			return;
		}

		printf("唯一的一个一维数组：");
		print_array(cur->data.array1D.arr, cur->data.array1D.len);
		printf("\n");
		return;
	}

	printf("总共有%d个一维数组，要打印第几个:\n", state->stats.array1D_count);
	get_valid_int(&index);
	while (index<1 || index>state->stats.array1D_count) {
		printf("输入范围不对，请重新选择：\n");
		get_valid_int(&index);
	}

	cur = find_nth_array1D(state->head, index);
	if (cur == NULL) {
		printf("数据出问题了，重开吧\n");
		return;
	}

	printf("第%d个一维数组：", index);
	print_array(cur->data.array1D.arr, cur->data.array1D.len);
	printf("\n");
}

void cmd_get_matrix(SystemState* state)
{
	Node* new_node = INIT_OBJ(Node);
	if (new_node == NULL) {
		printf("节点内存分配失败\n");
		return;
	}

	new_node->type = matrix;
	get_array2D_dimensions(&(new_node->data.matrix.row), &(new_node->data.matrix.col));
	new_node->data.matrix.mat = get_matrix(new_node->data.matrix.row, new_node->data.matrix.col);
	if (new_node->data.matrix.mat == NULL) {
		free(new_node);
		return;
	}

	state->stats.matrix_count++;
	state_tail_insert(state, new_node);
}

void cmd_print_array2D(SystemState* state)
{
	if (state->stats.array2D_count < 1) {
		printf("还没有二维数组，先创建一个吧\n");
		return;
	}

	Node* cur;
	int index;
	if (state->stats.array2D_count == 1) {
		cur = find_nth_array2D(state->head, 1);
		printf("唯一的一个二维数组：\n");
		print_array2D(cur->data.array2D.arr, cur->data.array2D.row, cur->data.array2D.col);
		printf("\n");
		return;
	}

	printf("现在有%d个二维数组，要打印哪一个:\n", state->stats.array2D_count);
	get_valid_int(&index);
	while (index<1 || index>state->stats.array2D_count) {
		printf("范围不对，请重新选择:\n");
		get_valid_int(&index);
	}

	cur = find_nth_array2D(state->head, index);
	printf("第%d个二维数组：\n", index);
	print_array2D(cur->data.array2D.arr, cur->data.array2D.row, cur->data.array2D.col);
	printf("\n");
	return;
}

void cmd_calculate_det(SystemState* state)
{
	if (state->stats.matrix_count == 0) {
		printf("还没有矩阵呢，先创建一个吧\n");
		return;
	}

	Node* temp = state->head->next;
	int* idx = (int*)calloc(state->stats.matrix_count, sizeof(int));
	if (idx == NULL) {
		printf("方阵的位置数组生成失败，退出吧\n");
		return;
	}

	int matrix_index = 0;
	int square_count = 0;
	while (temp != NULL) {
		if (temp->type == matrix) {
			matrix_index++;
			if (temp->data.matrix.row == temp->data.matrix.col) {
				idx[square_count++] = matrix_index;
			}
		}
		temp = temp->next;
	}

	if (square_count == 0) {
		printf("没有矩阵可以取行列式\n");
		free(idx);
		return;
	}

	int target_index;
	printf("可以求行列式的矩阵有：");
	for (int a = 0; a < square_count; a++) {
		printf("%d ", idx[a]);
	}
	printf("\n");

	printf("选择一个吧：\n");

	bool flag = true;
	while (flag) {
		get_valid_int(&target_index);
		for (int a = 0; a < square_count; a++) {
			if (target_index == idx[a]) {
				flag = false;
				break;
			}
		}

		if (flag) {
			printf("别搞，输入有问题,重输：\n");
		}
	}

	double result;
	Node* cur = find_nth_matrix(state->head, target_index);
	bool status = calculate_det(cur->data.matrix.mat, cur->data.matrix.row, &result);
	if (status) {
		printf("第%d个矩阵取行列式的值为：%lf\n", target_index, result);
		free(idx);
		return;
	}

	printf("计算函数报错，计算失败\n");
	free(idx);
	return;

	printf("数据出问题了（没找到第%d个矩阵），别搞了\n", target_index);
	free(idx);
}

void cmd_matrix_transpose(SystemState* state)
{
	assert(state != NULL);

	if (state->stats.matrix_count < 1) {
		printf("还没有矩阵呢，先创建一个吧\n");
		return;
	}

	Node* cur;
	if (state->stats.matrix_count == 1) {
		cur = find_nth_matrix(state->head, 1);
		if (cur == NULL) {
			printf("数据出问题了，退出吧\n");
			return;
		}

		double** temp = transpose_matrix(cur->data.matrix.mat, &(cur->data.matrix.row), &(cur->data.matrix.col));
		if (temp != NULL) {
			freeContiguousArray2D(cur->data.matrix.mat);
			cur->data.matrix.mat = temp;
			printf("矩阵转置成功!\n");
		}
		else {
			printf("矩阵转置失败，转置函数返回值为NULL\n");
		}
		return;
	}

	int target_mat;
	printf("有%d个矩阵可以转置，选一个吧(第几个）\n", state->stats.matrix_count);
	get_valid_int(&target_mat);
	while (target_mat > state->stats.matrix_count || target_mat < 1) {
		printf("别搞，第几个?\n");
		get_valid_int(&target_mat);
	}

	cur = find_nth_matrix(state->head, target_mat);
	if (cur != NULL) {
		double** temp = transpose_matrix(cur->data.matrix.mat, &(cur->data.matrix.row), &(cur->data.matrix.col));
		if (temp != NULL) {
			freeContiguousArray2D(cur->data.matrix.mat);
			cur->data.matrix.mat = temp;
			printf("矩阵转置成功\n");
			return;
		}
		else {
			printf("数组转置失败，转置函数返回值为NULL\n");
			return;
		}
	}

	printf("数据出问题了，退出吧\n");
	return;
}

void cmd_print_matrix(SystemState* state)
{
	if (state->stats.matrix_count < 1) {
		printf("还没有二维数组，先创建一个吧\n");
		return;
	}

	Node* cur;
	int index;
	if (state->stats.matrix_count == 1) {
		cur = find_nth_matrix(state->head, 1);
		printf("唯一的一个矩阵：\n");
		print_matrix(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		printf("\n");
		return;
	}

	printf("现在有%d个矩阵，要打印哪一个:\n", state->stats.matrix_count);
	get_valid_int(&index);
	while (index<1 || index>state->stats.matrix_count) {
		printf("范围不对，请重新选择:\n");
		get_valid_int(&index);
	}

	cur = find_nth_matrix(state->head, index);
	printf("第%d个二维数组：\n", index);
	print_matrix(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
	printf("\n");
	return;
}

void cmd_array_sort(SystemState* state)
{
	assert(state != NULL);

	if (state->stats.array1D_count < 1) {
		printf("还没有一维数组，先创建一个吧\n");
		return;
	}

	Node* cur;
	char* if_ascending;
	if (state->stats.array1D_count == 1) {
		cur = find_nth_array1D(state->head, 1);
		if (cur == NULL) {
			printf("数据有问题，退出吧\n");
			return;
		}

		printf("if ascending?\n");
		ATKStatus string_status=get_string(&if_ascending);
		if (string_status != Funk_Op_OK) {
			print_ATK_Err(string_status);
			return;
		}

		ATKStatus sort_status = bubble_sort(cur->data.array1D.arr, cur->data.array1D.len, if_ascending);
		if (sort_status == Funk_Op_OK) printf("排序成功\n");
		else print_ATK_Err(sort_status);
		free(if_ascending);
		return;
	}

	int target;
	printf("总共有%d个数组，选择一个进行排序（第几个）：", state->stats.array1D_count);
	while (1) {
		get_valid_int(&target);
		if (target<1 || target>state->stats.array1D_count) {
			printf("输入范围有问题，重新输入（第几个）：");
			continue;
		}

		break;
	}

	cur = find_nth_array1D(state->head, target);
	if (cur == NULL) {
		printf("数据有问题，退出吧\n");
		return;
	}
	
	printf("if ascending?\n");
	ATKStatus string_status = get_string(&if_ascending);
	if (string_status != Funk_Op_OK) {
		print_ATK_Err(string_status);
		return;
	}

	ATKStatus sort_status=bubble_sort(cur->data.array1D.arr, cur->data.array1D.len,if_ascending);
	if (sort_status == Funk_Op_OK) printf("排序成功\n");
	else print_ATK_Err(sort_status);
	free(if_ascending);
	return;
}

void cmd_matrix_rank(SystemState* state)
{
	assert(state != NULL);

	if (state->stats.matrix_count < 1) {
		printf("目前还没有矩阵，先创建一个吧\n");
		return;
	}

	Node* cur;
	if (state->stats.matrix_count == 1) {
		cur = find_nth_matrix(state->head, 1);
		if (cur != NULL) {
			int rank = matrix_rank(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
			if (rank >= 0) printf("唯一一个的矩阵的秩为：%d\n", rank);

			else printf("计算秩的函数返回值错误，检查一下吧\n");
			return;
		}

		else {
			printf("数据出问题了，退出吧\n");
			return;
		}
	}

	int target;
	printf("有%d个矩阵，选择一个矩阵进行求秩(第几个):",state->stats.matrix_count);
	get_valid_int(&target);
	while (target <= 0 || target > state->stats.matrix_count) {
		printf("输入范围有问题，重新输入:");
		get_valid_int(&target);
	}

	cur = find_nth_matrix(state->head, target);
	if (cur != NULL) {
		int rank = matrix_rank(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		if (rank >= 0) printf("第%d个矩阵的秩为：%d\n",target, rank);

		else printf("计算秩的函数返回值错误，检查一下吧\n");
		return;
	}

	else {
		printf("数据出问题了，退出吧\n");
		return;
	}
}

void cmd_inverse_matrix(SystemState* state)
{
	assert(state != NULL);
	if (state->stats.matrix_count < 1) {
		printf("目前还没有矩阵，先创建一个吧\n");
		return;
	}

	Node* cur;
	if (state->stats.matrix_count == 1) {
		cur = find_nth_matrix(state->head, 1);
		if (cur != NULL) {
			if (cur->data.matrix.row == cur->data.matrix.col) {
				ATKStatus status = inverse_matrix(cur->data.matrix.mat, cur->data.matrix.row);
				if (status!=Funk_Op_OK) print_ATK_Err(status);
				return;
			}
			else printf("唯一的一个矩阵也不是方阵，没法求逆\n");
			return;
		}

		else {
			printf("数据出问题了，退出吧\n");
			return;
		}
	}
	
	int target;
	printf("有%d个矩阵，选择将第几个矩阵进行求逆\n:", state->stats.matrix_count);
	get_valid_int(&target);
	while (target <= 0 || target > state->stats.matrix_count) {
		printf("输入范围有问题，重新输入:");
		get_valid_int(&target);
	}

	cur = find_nth_matrix(state->head, target);

	if (cur != NULL) {
		if (cur->data.matrix.row == cur->data.matrix.col) {
			ATKStatus status = inverse_matrix(cur->data.matrix.mat, cur->data.matrix.row);
			if (status != Funk_Op_OK) print_ATK_Err(status);
			return;
		}
		else printf("该矩阵不是方阵，没法求逆\n");
		return;
	}

	else {
		printf("数据出问题了，退出吧\n");
		return;
	}
}

void cmd_matrix_to_rowechelon(SystemState* state)
{
	assert(state != NULL);
	if (state->stats.matrix_count < 1) {
		printf("no matrix\n");
		return;
	}

	Node* cur;
	if (state->stats.matrix_count == 1) {
		cur = find_nth_matrix(state->head, 1);
		if (cur == NULL) {
			printf("data error\n");
			return;
		}

		ATKStatus status= matrix_to_rowechelon(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		if (status != Funk_Op_OK) {
			print_ATK_Err(status);
		}

		return;
	}

	int target;
	printf("有%d个矩阵，选择将第几个矩阵化成行阶梯型:", state->stats.matrix_count);
	get_valid_int(&target);
	while (target <= 0 || target > state->stats.matrix_count) {
		printf("输入范围有问题，重新输入:");
		get_valid_int(&target);
	}

	cur = find_nth_matrix(state->head, target);
	if (cur != NULL) {
		ATKStatus status = matrix_to_rowechelon(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		if (status != Funk_Op_OK) {
			print_ATK_Err(status);
		}
		return;
	}

	printf("数据出问题了，没有%d个矩阵的数据\n", target);
	return;
}

void cmd_matrix_to_rowsimplest(SystemState* state)
{
	assert(state != NULL);
	if (state->stats.matrix_count < 1) {
		printf("no matrix\n");
		return;
	}

	Node* cur;
	if (state->stats.matrix_count == 1) {
		cur = find_nth_matrix(state->head, 1);
		if (cur == NULL) {
			printf("data error\n");
			return;
		}

		ATKStatus status = matrix_to_rowsimplest(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		if (status != Funk_Op_OK) {
			print_ATK_Err(status);
		}

		return;
	}

	int target;
	printf("有%d个矩阵，选择将第几个矩阵化成行最简型:", state->stats.matrix_count);
	get_valid_int(&target);
	while (target <= 0 || target > state->stats.matrix_count) {
		printf("输入范围有问题，重新输入:");
		get_valid_int(&target);
	}

	cur = find_nth_matrix(state->head, target);
	if (cur != NULL) {
		ATKStatus status = matrix_to_rowsimplest(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		if (status != Funk_Op_OK) {
			print_ATK_Err(status);
		}
		return;
	}

	printf("数据出问题了，没有%d个矩阵的数据\n", target);
	return;
}




