#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<time.h>
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0
typedef struct {
	int key;
}element;
element heap[MAX_SIZE];//the min index is 2
int n=1;
int max_partner(int i)
{
	int j = i + (int)pow(2, (int)(log(i) / log(2)) - 1);
	if (j > n)j /= 2;
	return j;
}
int min_partner(int i)
{
	int j = i - (int)pow(2, (int)(log(i) / log(2)) - 1);
	return  j;
}
int level(int i)
{
	int n = i + 1;
	int number = 1;
	int result = 0;
	while (number < n) {
		number *= 2;
		result++;
	}
	return result;
}
int end(int pos)
{
	int n = pos + 1;
	while (n> 1) {
		if (n % 2 != 0)
			return 0;
		n /= 2;
	}
	return 1;
}
void printHeap()
{
	printf("----------------------\n");
	int i = 2;
	for (; i <= n; i++) {
		printf("[ %d ]", heap[i].key);
		if (end(i))
			putchar('\n');
	}
	if (!end(i - 1))putchar('\n');
	printf("----------------------\n");
}
int max_heap(int i)
{
	int iLevel = level(i);
	if (i >= pow(2, iLevel - 1) + pow(2, iLevel - 2) &&
		i < pow(2, iLevel))
		return TRUE;
	else
		return FALSE;
}
int min_heap(int i)
{
	int iLevel = level(i);
	if (i >= pow(2, iLevel - 1)&&
		i < pow(2, iLevel - 1) + pow(2, iLevel - 2))
		return TRUE;
	else
		return FALSE;
}
void min_insert(element heap[], int i, element item)
{
	int parent = i / 2;
	while (parent) {
		if (heap[parent].key>item.key) {
			heap[i] = heap[parent];
			i = parent;
			parent /= 2;
		}
		else
			break;
	}
	heap[i] = item;
}
void max_insert(element heap[], int i, element item)
{
	int parent = i / 2;
	while (parent>1) {
		if (heap[parent].key < item.key) {
			heap[i] = heap[parent];
			i = parent;
			parent /= 2;
		}
		else
			break;
	}
	heap[i] = item;
}
void heap_insert(element heap[], int *n, element x)
{
	int i;
	(*n)++;
	if (*n == MAX_SIZE) {
		fprintf(stderr, "The heap is full\n");
		exit(1);
	}
	if (*n == 2)//the heap is empty
		heap[2] = x;
	else switch (max_heap(*n)) {
	case FALSE:
		i = max_partner(*n);
		//printf("//part one and i is %d\n",i);
		if (x.key > heap[i].key) {
			heap[*n] = heap[i];
			max_insert(heap, i, x);
		}
		else
			min_insert(heap, *n, x);
		break;
	case TRUE:
		i = min_partner(*n);
		//printf("//part two and i is %d\n", i);
		if (x.key < heap[i].key) {
			heap[*n] = heap[i];
			min_insert(heap, i, x);
		}
		else
			max_insert(heap, *n, x);
		break;
	}
}

void modified_heap_insert_min(element heap[], int i, element item)
{
	int partner = max_partner(i);
	if (heap[partner].key < item.key) {
		heap[i] = heap[partner];
		max_insert(heap, partner, item);
	}
	else
		min_insert(heap, i, item);
}
element delete_min(element heap[], int* n)
{
	if (*n < 2) {
		fprintf(stderr, "The heap is empty.\n");
		heap[0].key = INT_MAX;
		return heap[0];
	}
	heap[0] = heap[2];//save the min
	heap[1] = heap[(*n)--];
	int i, j;
	for (i = 2; 2 * i <= *n; heap[i] = heap[j], i = j) {
		j = 2 * i;
		if (heap[j].key>heap[j + 1].key)
			j++;
	}
	modified_heap_insert_min(heap, i, heap[1]);
	return heap[0];
}

void modified_heap_insert_max(element heap[], int i, element item)
{
	int partner = min_partner(i);
	int maxKey = heap[partner].key;
	int maxIndex = partner;
	if(partner*2<=n)
		if (maxKey<heap[partner * 2].key) {
			maxKey = heap[partner * 2].key;
			maxIndex = partner * 2;
		}
	if(partner*2+1<=n)
		if (maxKey<heap[partner * 2].key) {
			maxKey = heap[partner * 2 + 1].key;
			maxIndex = 2 * partner + 1;
		}

	if(maxKey<=item.key)
		max_insert(heap, i, item);
	else {
		heap[i] = heap[maxIndex];
		min_insert(heap, maxIndex, item);
	}
}
element delete_max(element heap[], int* n)
{
	int i, j;
	if (*n < 2) {
		fprintf(stderr, "The heap is empty.\n");
		heap[0].key = INT_MIN;
		return heap[0];
	}
	if (*n == 2)
		heap[0] = heap[(*n)--];
	else {
		heap[0] = heap[3];
		heap[1] = heap[(*n)--];
		for (i = 3; i * 2 <= *n; heap[i] = heap[j], i = j) {
			j = 2 * i;
			if (heap[j].key < heap[j + 1].key)
				j++;
		}
		modified_heap_insert_max(heap, i, heap[1]);
	}
	return heap[0];
}
void test()
{
	n = 1;
	srand(time(0));
	element item;
	for (int i = 2; i < MAX_SIZE; i++) {
		item.key = rand() %(2* MAX_SIZE);
		printf("[ %d ]", item.key);
		heap_insert(heap, &n, item);
	}
	putchar('\n');
	printHeap();
	for (int i = 2; i < MAX_SIZE; i++) {
		item = delete_max(heap, &n);
		printf("[ %d ]",item.key);
	}
	putchar('\n');
	printHeap();
}