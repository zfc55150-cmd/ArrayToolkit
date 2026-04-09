#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#include "ArrayToolkit.h"

#define INIT_OBJ(type) ((type*)calloc(1,sizeof(type)))

typedef struct Node {
	void* arr;
	int ndim;
	int* shape;
	struct Node* next;
}Linklist;

void error_freelist(Linklist* head)
{
	while (head != NULL) {
		Linklist* temp = head->next;
		if (head->arr != NULL) {
			if (head->ndim == 2) {
				void** mat = (void**)head->arr;
				free(mat[0]);
			}
		}

		free(head->arr);
		free(head->shape);
		free(head);
		head = temp;
	}
}

Linklist* get_arrlist(int len)
{
	Linklist* head = INIT_OBJ(Linklist);
	if (head == NULL) {
		return NULL;
	}

	Linklist* tail = head;
	for (int a = 1; a <= len; a++) {
		Linklist* new_node = INIT_OBJ(Linklist);
		if (new_node == NULL) {
			error_freelist(head);
			return NULL;
		}

		char choice;
		printf("要传入什么类型的数组：A/a一维数组；B/b二维数组\n");
		get_twochoice(&choice);

		if (choice == 'a' || choice == 'A') {
			new_node->ndim = 1;
			new_node->shape = (int*)malloc(new_node->ndim * sizeof(int));
			if (new_node->shape == NULL) {
				free(new_node);
				error_freelist(head);
				exit(1);
			}
			new_node->arr = get_array(&(new_node->shape[0]));
		}
		else {
			new_node->ndim = 2;
			new_node->shape = (int*)malloc(new_node->ndim * sizeof(int));
			if (new_node->shape == NULL) {
				free(new_node);
				error_freelist(head);
				exit(1);
			}
			get_matrix_dimensions(&(new_node->shape[0]), &(new_node->shape[1]));
			new_node->arr = get_matrix(new_node->shape[0], new_node->shape[1]);
		}
		if (new_node->arr == NULL) {
			free(new_node->shape);
			free(new_node);
			error_freelist(head);
			return NULL;
		}

		tail->next = new_node;
		tail = new_node;
	}

	return head;
}

void print_arrlist(Linklist* head)
{
	printf("以下是数组链表\n");
	Linklist* curr = head->next;
	int count = 1;
	while (curr != NULL) {
		printf("第%d个数组: \n", count++);
		if (curr->ndim == 1) {
			print_array((int*)curr->arr, curr->shape[0]);
		}
		else if (curr->ndim == 2) {
			print_matrix((int**)curr->arr, curr->shape[0], curr->shape[1]);
		}
		curr = curr->next;
	}
}

int main(void)
{
	SetConsoleOutputCP(65001);
	print_arrlist(get_arrlist(1));
}
