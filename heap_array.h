#pragma once
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define MAX_ELEMENTS 200
#define QUEUE_ELEMENTS 200

#define HEAP_FULL(n) (n==MAX_ELEMENTS)
#define HEAP_EMPTY(n) (n==0)

#define QUEUE_FULL(n) (n==MAX_ELEMENTS)
#define QUEUE_EMPTY(n) (n==0)

typedef struct {
	int key;
} element;
element heap[MAX_ELEMENTS];
int queue[QUEUE_ELEMENTS];
int queueCapacity = 0;
int heapCapacity = 0;
void addQueue(int data)
{
	if (HEAP_FULL(queueCapacity)) {
		fprintf(stderr, "The queue is full.\n");
		exit(1);
	}
	queue[queueCapacity++] = data;
}
int delQueue()
{
	if (QUEUE_EMPTY(queueCapacity)) {
		fprintf(stderr, "The queue is empty.\n");
		exit(1);
	}
	return queue[--queueCapacity];
}
void insertMaxHeap(element item, int *n)
{
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}
	int i = ++(*n);
	while ((i != 1) && (item.key > heap[i/ 2].key)) {//如果堆存储从0开始那么heapCapacity 从-1开始.
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}
int judgeTwoPower(int a)
{
	a += 1;
	int b = a;
	while (a >= 2) {
		if (a % 2 != 0)
			return 0;
		a /= 2;
	}
	if (b == a)
		return 0;
	return 1;
}
void printHeap()
{
	for (int i = 1; i <=heapCapacity; i++) {
		printf("%5d", heap[i].key);
		if (judgeTwoPower(i))
			putchar('\n');
	}
	printf("\n-----------------------\n");
}
element deleteMaxHeap(int *n)
{
	if (HEAP_EMPTY(heapCapacity)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}
	element temp = heap[1];
	heap[1] = heap[heapCapacity];
	int j = 1;
	heapCapacity--;
	while (j * 2 <= heapCapacity) {

		if (j * 2 + 1 <= heapCapacity) {
			if ((heap[j].key < heap[2 * j + 1].key&& heap[2 * j + 1].key>heap[2*j].key)) {
				int temp = heap[j].key;
				heap[j].key = heap[2 * j + 1].key;
				heap[2 * j + 1].key = temp;
			}
		}

		if (heap[j].key < heap[2 * j].key) {
			int temp = heap[j].key;
			heap[j].key = heap[2 * j].key;
			heap[2 * j].key = temp;
		}
		j++;
	}
	return temp;
}
element deleteMaxHeap_Second(int *n)
{
	if (HEAP_EMPTY(heapCapacity)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}
	element item = heap[(*n)--];
	element temp = heap[1];//save the value to return .
	int child=2, parent=1;//the child now is the left child of the parent
	while (child <= *n) {
		if ((child<*n) && (heap[child + 1].key>heap[child].key))//child<*n for there is the parent's right child.
			child++;
		if (item.key >= heap[child].key)break;//'=' may decreas one step
		heap[parent] = heap[child];
		parent = child;
		child *=2;
	}
	heap[parent] = item;
	return temp;
}
void insertMinHeap(element item, int *n)
{
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}
	int i = ++(*n);
	while ((i != 1) && (item.key < heap[i / 2].key)) {//如果堆存储从0开始那么heapCapacity 从-1开始.
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}
element deleteMinHeap(int* n)
{
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}
	int child=2, parent=1;
	element temp = heap[0];
	element item = heap[(*n)--];
	while (child <= *n) {
		if ((child<*n) && heap[child].key>heap[child + 1].key)
			child++;
		if (heap[child].key >= item.key)break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = item;
	return temp;
}
void changePriority(int position, element item)
{
	int temp;
	heap[position].key = item.key;
	while (position>1) {
		if (heap[position].key <= heap[position / 2].key) {
			if (position * 2 <= heapCapacity) {
				if (heap[2 * position].key <= heap[position].key) {
					if (position * 2 + 1 <= heapCapacity&&heap[position * 2 + 1].key <= heap[position].key)
						break;
					else if (position * 2 + 1 > heapCapacity)
						break;
					else if(heap[position * 2 + 1].key>heap[position * 2].key){
						temp = heap[position].key;
						heap[position].key = heap[2 * position + 1].key;
						heap[position * 2 + 1].key = temp;
						position = position * 2 + 1;
					}
				}
				else {
					temp = heap[position].key;
					heap[position].key = heap[2 * position].key;
					heap[position * 2].key = temp;
					position *= 2;
				}
			}
			else
				break;
		}
		else {
			temp = heap[position].key;
			heap[position].key = heap[position / 2].key;
			heap[position / 2].key = temp;
			position /= 2;
		}
	}
}
element getMostBigElement()
{
	element temp;
	temp.key = heap[1].key;
	for (int i = 2; i <= heapCapacity; i++) {
		if (temp.key < heap[i].key);
		temp.key = heap[i].key;
	}
	return temp;
}
void deleteOneElement(int position)
{
	if (position<1 || position>heapCapacity) {
		fprintf(stderr, "The position is illegal.\n");
		return;
	}
	element temp = getMostBigElement();
	temp.key += 1;
	changePriority(position, temp);
	deleteMaxHeap(&heapCapacity);
}


