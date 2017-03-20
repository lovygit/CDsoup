#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10
int stack[MAX_SIZE];
int top = -1;
void push(int* stack, int item) {
	if (top >= MAX_SIZE - 1) {
		printf("The stack is full.\n");
		return;
	}
	stack[++top] = item;
}
int pop(int* stack)
{
	if (top < 0) {
		printf("The stack is empty.\n");
		exit(1);
	}
	return stack[top--];
}
int output[MAX_SIZE];
int size = 0;
void treeNum(int* stack, int seq, int depth, int size) {
	static int time = 1;
	if (seq < depth) {
		push(stack, seq + 1);

		if (seq == depth - 1) {
			while (top>= 0)
				output[size++] = pop(stack);
			printf("[ %2d ]  ¡¾ ",time++);
			for (int i = 0; i < depth; i++) {
				printf("%c", output[i]+'A'-1);
				if (i != depth - 1)
					putchar(',');
			}
			printf(" ¡¿\n");
			return;
		}

		int temp[MAX_SIZE];
		int length = top + 1;
		int sizeCopy = size;
		for (int i = 0; i <= top; i++)
			temp[i] = stack[i];
		for (int i = 0; i <= length; i++) {
			for (int j = 0; j < length; j++)
				stack[j] = temp[j];
			top = length - 1;
			size = sizeCopy;
			for (int k = 0; k < i; k++)
				output[size++] = pop(stack);
			if (size < depth)
				treeNum(stack, seq + 1, depth, size);
		}
	}
}
void test() {
	treeNum(stack, 0, 3,0);
}
/*
void push(int item, int* stack,int *top) {
stack[++(*top)] = item;
}
int pop(int* stack, int* top) {
return stack[(*top)--];
}
void printWithFormat(int length, int number) {
int i = 0;
while (number >= pow(10, i++));
int distance = length - i+1;
if (distance > 0)
while (distance-- > 0)
printf("0");
printf("%d", number);
}
void treeNum(int seq, int depth,int* stack,int* top,int* output,int size) {
static int time = 1;
if (seq < depth) {
push(seq, stack, top);
if (seq == depth - 1) {
while (*top>=0)
output[size++] = pop(stack, top);

printf("[");
printWithFormat(4, time++);
printf("] ");
for (int i = 0; i <size; i++)
printf("%5c", output[i] + 'A');
putchar('\n');
}
int topCopy = *top;
int sizeCopy = size;
int stackCopy[MAX];
for (int i = 0; i <= topCopy; i++)
stackCopy[i] = stack[i];
for (int i = 0; i <= topCopy + 1; i++) {
for (int j = 0; j <= topCopy; j++)
stack[j] = stackCopy[j];
*top = topCopy;
size = sizeCopy;
for (int k = 0; k < i; k++)
output[size++] = pop(stack,top);
if (size < depth)
treeNum(seq + 1, depth, stack, top, output, size);
}
}
}
*/