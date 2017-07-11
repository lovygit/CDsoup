#pragma once
#include<stdio.h>
#include<stdlib.h>
void quickSort(int array[], int left, int right) {
	if (left < right) {
		int pivot = array[left];
		int i = left;
		int j = right;
		while (i<j) {
			do
				j--;
			while (j > i&&array[j]>pivot);
			do
				i++;
			while (j > i&&array[i] < pivot);
			if (i < j) {
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
		array[left] = array[j];
		array[j] = pivot;
		quickSort(array, left, j);
		quickSort(array, j + 1, right);
	}
}

int split(int array[], int left, int right) {
	int pivot = array[left];
	int i = left;
	for (int j = left + 1; j <= right; j++) {
		if (array[j] < pivot) {
			i++;
			if (i != j) {
				int tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	array[left] = array[i];
	array[i] = pivot;
	return i;
}
struct node {
	int low;
	int high;
}stack[1000];

void quickSort2(int array[], int size) {
	int left = 0, right = size - 1;
	int top = -1;
	stack[++top].low = left;
	stack[top].high = right;
	int low = left;
	int high = right;
	int position;
	while (top >= 0) {
		low = stack[top].low;
		high = stack[top--].high;
		position = split(array, low, high);
		if (position>low)
			stack[++top].low = low; stack[top].high = position - 1;
		if (high>position + 1)
			stack[++top].low = position + 1; stack[top].high = high;
	}
}

int test(void)
{
	int array[24];
	int j = 0;
	for (int i = 11; i != 0; i = (11 + i) % 24) {
		array[j++] = i;
	}
	for (int i = 0; i < 23; i++)
		printf("%5d", array[i]);
	printf("\n--------------------\n");
	/*quickSort(array, 0, 23);
	for (int i = 0; i < 23; i++)
	printf("%5d", array[i]);
	printf("\n--------------------\n");*/
	quickSort2(array, 23);
	for (int i = 0; i < 23; i++)
		printf("%5d", array[i]);
	printf("\n--------------------\n");
}
