#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "get.h"
#include "array_alloc.h"
#include "array_core.h"
#include "list.h"

#define INIT_OBJ(type) ((type*)calloc(1,sizeof(type)))


//用来在链表出现错误时，释放链表内存
void free_list(Node* head)
{
	if (head == NULL) {
		return;
	}

	Node* cur = head->next;
	while (cur != NULL) {
		
		Node* temp = cur->next;
		if (cur->type== Array_1D) {
			if (cur->data.array.arr!=NULL) {
				free(cur->data.array.arr);
			}
		}

		else if(cur->type==Array_2D){
			if (cur->data.matrix.mat != NULL) {
				freeContiguousMatrix(cur->data.matrix.mat);
			}
		}

		free(cur);
		cur = temp;
	}
	free(head);
}

//用来获取一个数组链表
Node* get_arrlist(int len)
{
	Node* head = INIT_OBJ(Node);
	if (head == NULL) {
		return NULL;
	}

	Node* tail = head;
	for (int a = 1; a <= len; a++) {
		Node* new_node = INIT_OBJ(Node);
		if (new_node == NULL) {
			free_list(head);
			return NULL;
		}

		char choice;
		printf("要传入什么类型的数组：A/a一维数组；B/b二维数组\n");
		get_twochoice(&choice);

		if (choice == 'a' || choice == 'A') {
			new_node->type = Array_1D;
			new_node->data.array.arr = get_array(&(new_node->data.array.len));
			if (new_node->data.array.arr == NULL) {
				free(new_node);
				free_list(head);
				return NULL;
			}
		}
		else {
			new_node->type = Array_2D;
			get_matrix_dimensions(&(new_node->data.matrix.row), &(new_node->data.matrix.col));
			new_node->data.matrix.mat = get_matrix(new_node->data.matrix.row, new_node->data.matrix.col);
			if (new_node->data.matrix.mat == NULL) {
				free(new_node);
				free_list(head);
				return NULL;
			}

		}

		tail->next = new_node;
		tail = new_node;
	}

	return head;
}

void print_arrlist(Node* head)
{
	printf("以下是数组链表\n");
	Node* cur = head->next;
	int count = 1;
	while (cur != NULL) {
		printf("第%d个数组: \n", count++);
		if (cur->type == Array_1D) {
			print_array(cur->data.array.arr, cur->data.array.len);
		}
		else if (cur->type==Array_2D) {
			print_matrix(cur->data.matrix.mat, cur->data.matrix.row, cur->data.matrix.col);
		}
		cur = cur->next;
	}
}