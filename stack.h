#include<stdio.h>
#include<stdlib.h>
#ifndef STACK
#define CAPACITY 50
int size = 0;
int stack_invert[CAPACITY];
typedef struct{
	char string[20];
}element;
element stack_cal[CAPACITY];
int top =-1;
int isFull_stack()
{
	return ((size == CAPACITY) ? 1 : 0);
}
int isEmpty_stack()
{
	return ((size == 0) ? 1 : 0);
}

void push_invert(int data)
{
	if (isFull_stack()) {
		fprintf(stderr, "the stack is full.\n");
		return;
	}
	stack_invert[++top] = data;
	size++;
}
int pop_invert()
{
	if (isEmpty_stack()) {
		fprintf(stderr, "the stack is empty!\n");
		exit(1);
	}
	size--;
	return stack_invert[top--];
}

void push_cal(char* str)
{
	if (isFull_stack()) {
		fprintf(stderr, "the stack is full.\n");
		return;
	}
	strcpy_s(stack_cal[++top].string, 20, str);
	size++;
}
char* pop_cal()
{
	if (isEmpty_stack()) {
		fprintf(stderr, "the stack is empty!\n");
		exit(1);
	}
	size--;
	return stack_cal[top--].string;
}
#endif
