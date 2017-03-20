#pragma once
#include<stdio.h>
#include<stdlib.h>
#define IS_FULL(ptr) (!(ptr))
typedef struct list_node *list_pointer;
struct list_node{
	int data;
	list_pointer link;
};
list_pointer ptr = NULL;
void insert(list_pointer* ptr, list_pointer node)//insert after the node
{
	list_pointer temp = (list_pointer)malloc(sizeof(struct list_node));
	if (IS_FULL(temp)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->data = 100;
	if (*ptr) {
		temp->link = node->link;
		node->link = temp;
	}
	else {
		temp->link = NULL;
		(*ptr)->link = temp;
	}
}
void mov_node(list_pointer* ptr, list_pointer trail)
{
	if (trail) {
		if (trail->link != NULL)
			trail->link = trail->link->link;
	}
	else {
		*ptr = (*ptr)->link;
	}
}
list_pointer search(list_pointer* ptr, int number)
{
	list_pointer temp = *ptr;
	while (temp != NULL) {
		if (temp->data == number)return temp;
		temp = temp->link;
	}
	return NULL;
}
void mov_num(list_pointer* ptr, int number)
{
	list_pointer temp = search(ptr, number);
	if (temp == NULL) {
		fprintf(stderr, "there is not the data.\n");
	}
	else {
		temp = *ptr;
		while (temp->link != NULL) {
			if (temp->link->data == number)
				temp->link = temp->link->link;
			else if (temp == *ptr&&temp->data == number)
				*ptr = (*ptr)->link;
			else
			temp=temp->link;
		}
	}
}
int nodes(list_pointer* ptr)
{
	int count = 0;
	list_pointer temp = *ptr;
	while (temp != NULL) {
		count++;
		temp = temp->link;
	}
	return count;
}
void mov_odd(list_pointer* ptr)
{
	list_pointer temp = *ptr;
	list_pointer temp_copy = temp;
	int i = 1;
	while (temp != NULL) {
		if (i == 1)
			mov_node(ptr, NULL);
		else if (i % 2 == 0) {
			if (temp->link != NULL) {
				temp = temp->link->link;
				i += 2;
				mov_node(ptr, temp_copy);
				temp_copy = temp;
				continue;
			}
			else
				break;
		}
		i++;
		temp = temp->link;
		temp_copy = temp;
	}
}
void print_node(list_pointer* ptr)
{
	list_pointer temp = *ptr;
	while (temp != NULL) {
		printf("the data is %d\n", temp->data);
		temp = temp->link;
	}
}
list_pointer unit_not_less(list_pointer* ptr1, list_pointer* ptr2)
{
	list_pointer temp1 = *ptr1;
	list_pointer temp2 = *ptr2;
	list_pointer temp3 = (list_pointer)malloc(sizeof(struct list_node));
	list_pointer temp4 = temp3;
	while (temp1!= NULL && temp2!= NULL) {
		if (temp1->data <= temp2->data) {
			temp3->link = temp1;
			temp3 = temp3->link;
			temp1 = temp1->link;
		}
		else {
			temp3->link= temp2;
			temp3 = temp3->link;
			temp2 = temp2->link;
		}
	}
	if (temp1 == NULL)
		temp3->link = temp2;
	else if (temp2 == NULL)
		temp3->link = temp1;
	list_pointer temp5 = temp4;
	temp4 = temp4->link;
	free(temp5);
	return temp4;
}
list_pointer unit_mutual(list_pointer* ptr1, list_pointer* ptr2)
{
	int m = nodes(ptr1);
	int n = nodes(ptr2);
	list_pointer temp1 = *ptr1;
	list_pointer temp2 = *ptr2;
	list_pointer temp3 = (list_pointer)malloc(sizeof(struct list_node));
	list_pointer temp4 = temp3;
	list_pointer temp5 = temp4;
	int a = 1;
	if (m <=n) {
		while (temp1 != NULL) {
			if (a % 2 == 0) {
				temp3->link = temp1;
				temp3 = temp3->link;
				temp1 = temp1->link;
			}
			else {
				temp3->link = temp2;
				temp3 = temp3->link;
				temp2 = temp2->link;
			}
			a++;
		}
		temp3->link = temp2;
	}
	else {
		while (temp2 != NULL) {
			if (a % 2 != 0) {
				temp3->link = temp1;
				temp3 = temp3->link;
				temp1 = temp1->link;
			}
			else {
				temp3->link = temp2;
				temp3 = temp3->link;
				temp2 = temp2->link;
			}
			a++;
		}
		temp3->link = temp1;
	}
	temp4 = temp4->link;
	free(temp5);
	return temp4;
}