#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<windows.h>
#include"ArrayToolkit.h"

#define INIT_OBJ(type) ((type*)calloc(1,sizeof(type)))

typedef struct Node {
	void* arr;
	int dim;
	struct Node* next;
}Linklist;

void error_freelist(Linklist* head)
{
	while (head != NULL) {
		Linklist* temp = head->next;
		free(head->arr);
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

		new_node->arr = get_array(&(new_node->dim));
		if (new_node->arr == NULL) {
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
		printf("第%d个数组: ", count++);
		print_array(curr->arr, curr->dim);
		curr = curr->next;
	}
}

int main(void)
{
	SetConsoleOutputCP(65001);
	print_arrlist(get_arrlist(3));
}
