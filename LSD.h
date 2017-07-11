#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define MAX_DIGIT 3//Î»Êý
#define  RADIX_SIZE 10
typedef struct node *node_pointer;
struct node {
	int key[MAX_DIGIT];
	node_pointer link;
};

node_pointer radix_sort(node_pointer ptr)
{
	int digit;
	node_pointer front[RADIX_SIZE], rear[RADIX_SIZE];
	for (int i = MAX_DIGIT - 1; i >= 0; i-- ) {
		for (int j = 0; j < RADIX_SIZE; j++)
			front[j] = rear[j] = NULL;
		while (ptr) {
			digit = ptr->key[i];
			if (!front[digit])
				front[digit] = ptr;
			else
				rear[digit]->link = ptr;
			rear[digit] = ptr;
			ptr = ptr->link;
		}
		ptr = NULL;
		for (int k = RADIX_SIZE - 1; k >= 0;k--)
			if (front[k]) {
				rear[k]->link = ptr;
				//ptr = rear[k];
				ptr = front[k];
			}
	}
	return ptr;
}

node_pointer createNodeByNumber(int digit)
{
	int length = 0;
	int digitCopy = digit;
	while (digitCopy > 0) {
		length++;
		digitCopy /=RADIX_SIZE;
	}

	if (length > MAX_DIGIT) {
		printf("The length is too long .\n");
		return NULL;
	}
	int pos = 0;
	node_pointer temp = (node_pointer)malloc(sizeof(struct node));
	temp->link = NULL;
	char str[MAX_DIGIT+1];
	_itoa_s(digit, str, MAX_DIGIT+1, RADIX_SIZE);
	while (length < MAX_DIGIT) {
		temp->key[pos] = 0;
		length++;
		pos++;
	}
	int i = 0;
	while (pos < MAX_DIGIT)
		temp->key[pos++] = str[i++]-'0';
	return temp;
}
void printNode(node_pointer ptr)
{
	printf("[ ");
	for (int i = 0; i < MAX_DIGIT; i++)
		printf("%d", ptr->key[i]);
	printf(" ]");
}
void test()
{
	srand(time(0));
	node_pointer nodes[20];
	nodes[19] = createNodeByNumber(rand() % 100);
	for (int i = 18; i >=0; i--) {
		nodes[i] = createNodeByNumber(rand() % 100);
		nodes[i]->link = nodes[i + 1];
	}
	nodes[0]=radix_sort(nodes[0]);
	while (nodes[0]) {
		printNode(nodes[0]);
		nodes[0] = nodes[0]->link;
	}
}