#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node* next;
	int data;
} typedef node;

node *head = NULL;

int start(int data) {
	node *tmp = head;
	head = malloc(sizeof(node));
	head->data = data;
	head->next = tmp;
	return 1;
}

int add(int data) {
	node *tmp = head;
	if (tmp == NULL)
		start(data);
	else {
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(node));
		tmp = tmp->next;
		tmp->data = data;
		tmp->next = NULL;
	}
	return 1;
}

int insert(int index, int item) {
	if (index < 0)
		return 0;
	if (index == 0) {
		start(item);
		return 1;
	}
	node *tmp = head;
	while (index > 1) {
		if (tmp == NULL)
			return 0;
		tmp = tmp->next;
		index--;
	}
	if (tmp == NULL)
		return 0;
	node *tmp2;
	tmp2 = malloc(sizeof(node));
	tmp2->data = item;
	tmp2->next = tmp->next;
	tmp->next = tmp2;
	return 1;
}

int size() {
	int len = 0;
	node *tmp = head;
	while (tmp != NULL) {
		len++;
		tmp = tmp->next;
	}
	return len;
}

int rremove(int index) {
	if (index < 0)
		return 0;
	if (index == 0) {
		if (head == NULL)
			return 0;
		node *tmp = head->next;
		free(head);
		head = tmp;
		return 1;
	}
	node *tmp = head;
	while (index > 1) {
		if (tmp == NULL)
			return 0;
		tmp = tmp->next;
		index--;
	}
	if (tmp == NULL || tmp->next == NULL)
		return 0;
	node *tmp2 = tmp->next->next;
	free(tmp->next);
	tmp->next = tmp2;
	return 1;
}

int set(int index, int item) {
	if (index < 0)
		return 0;
	node *tmp = head;
	while (index != 0) {
		if (tmp == NULL)
			return 0;
		tmp = tmp->next;
		index--;
	}
	if (tmp == NULL)
		return 0;
	tmp->data = item;
	return 1;
}

int get(int index) {
	if (index < 0)
		return 0;
	node *tmp = head;
	while (index != 0) {
		if (tmp == NULL)
			return 0;
		tmp = tmp->next;
		index--;
	}
	if (tmp == NULL)
		return 0;
	return tmp->data;
}

void printList() {
	node *tmp = head;
	while (tmp != NULL) {
		printf("%d>>", tmp->data);
		tmp = tmp->next;
	}
	printf("\b\b  \n");
}

int main() {
	printf("cur size: %d\n", size());
	printList();
	insert(1, 2);
	insert(2, 0);
	rremove(2);
	rremove(1);
	rremove(0);
	set(0, 0);
	set(1, 1);
	set(2, 2);
	get(0);
	get(1);
	get(2);
	add(3);
	printf("cur size: %d\n", size());
	printList();
	add(4);
	insert(0, 1);
	add(5);
	insert(4, 6);
	insert(1, 2);
	printf("cur size: %d\n", size());
	printList();
	rremove(0);
	rremove(2);
	printf("cur size: %d\n", size());
	printList();
	set(0, 1);
	set(3, 7);
	printf("cur size: %d\n", size());
	printList();
	printf("2EL=%d\t0EL=%d\n", get(2), get(0));
	insert(4, 9);
	insert(6, 13);
	rremove(7);
	rremove(6);
	rremove(5);
	rremove(4);
	set(4, 9);
	set(5, 11);
	set(3, 7);
	get(4);
	get(3);
	get(5);
	return 0;
}
