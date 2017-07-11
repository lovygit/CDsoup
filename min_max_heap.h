#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
#include<time.h>
//min_max_heap
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0
#define SWAP(x,y,z) ((z)=(x),(x)=(y),(y)=(z))
typedef struct {
	int key;
}element;
element heap[MAX_SIZE];//the min index is 1
int n = 0;
int level(int pos)
{
	int n = pos + 1;
	int number = 1;
	int result = 0;
	while (number < n) {
		number *= 2;
		result++;
	}
	return (result%2==0)?TRUE:FALSE;//return min or max level,resume that level one is the min level
}
int levelNumber(int pos)
{
	int n = pos + 1;
	int number = 1;
	int result = 0;
	while (number < n) {
		number *= 2;
		result++;
	}
	return result;
}
void verify_max(element heap[], int i, element item)
{
	int grandParent = i / 4;
	while (grandParent) {
		if (heap[grandParent].key < item.key) {
			heap[i] = heap[grandParent];
			i = grandParent;
			grandParent /= 4;
		}
		else
			break;
	}
	heap[i] = item;
}
void verify_min(element heap[], int i, element item)
{
	int grandParent = i / 4;
	while (grandParent) {
		if (heap[grandParent].key > item.key) {
			heap[i] = heap[grandParent];
			i = grandParent;
			grandParent /= 4;
		}
		else
			break;
	}
	heap[i] = item;
}
void min_max_insert(element heap[], int *n, element item)
{
	int parent;
	(*n)++;
	if (*n == MAX_SIZE) {
		fprintf(stderr, "The heap is full.\n");
		return;
	}
	parent = (*n) / 2;
	if (parent == 0) {
		heap[1] = item;
		return;
	}
	switch (level(parent))
	{
	case TRUE://max level
		if (item.key > heap[parent].key) {
			//printf("//part one\n");
			heap[*n] = heap[parent];
			verify_max(heap, parent, item);
		}
		else {
			//printf("//part two\n");
			verify_min(heap, *n, item);
		}
		break;
	case FALSE:
		if (item.key < heap[parent].key) {
			//printf("//part three\n");
			heap[*n] = heap[parent];
			verify_min(heap, parent, item);
		}
		else {
			//printf("//part four\n");
			verify_max(heap, *n, item);
		}
		break;
	default:
		break;
	}
}

int getMinIndex(element heap[], int i,int* n)
{
	if (i + 1 > *n)
		return 0;
	int min = heap[i + 1].key;
	int minIndex = i + 1;
	while (++i <= *n) {
		if (heap[i].key < min) {
			min = heap[i].key;
			minIndex = i;
		}
	}
	return minIndex;
}
int getMinIndex_2(element heap[], int i,int *n)
{
	if (i + 1 > *n)
		return 0;
	int end(int);
	int iLevel = levelNumber(i);
	int jLevel = iLevel + ((((iLevel % 2 == 0)&&pow(2,iLevel+1)<=*n)||end(i))? 1 : 0 );
	int j = (jLevel == iLevel)? i + 1 : pow(2, jLevel-1);
	int min = heap[j].key;
	int minIndex = j;
	while (j <= *n) {
		if (heap[j].key < min) {
			min = heap[j].key;
			minIndex = j;
		}
		if (end(j)) {
			if (jLevel % 2 == 0) {
				jLevel++;
				j++;
			}
			else {
				if (((int)pow(2, jLevel + 2)) <= *n) {
					jLevel += 2;
					j = pow(2, jLevel);
				}
				else {
					jLevel++;
					j++;
				}
			}
		}
		else
			j++;
	}
	return minIndex;
}
element delete_min(element heap[], int *n)
{
	int i, last, k, parent;
	element temp, x;
	if (!(*n)) {
		fprintf(stderr, "The heap is empty.\n");
		heap[0].key = INT_MAX;
		return heap[0];
	}
	heap[0] = heap[1];
	x = heap[(*n)--];
	for (i = 1, last = (*n) / 2; i <= last;) {
		k = getMinIndex_2(heap, i,n);
		if (x.key <= heap[k].key)break;
		heap[i] = heap[k];
		if (k <= 2 * i + 1) {
			i = k;
			break;
		}
		parent = k / 2;
		if (x.key > heap[parent].key)
			SWAP(heap[parent],x,temp);
		i = k;
	}
	heap[i] = x;
	return heap[0];
}

int getMaxIndex(element heap[], int i, int* n)
{
	if (i + 1 > *n)
		return 0;
	int max = heap[i + 1].key;
	int maxIndex = i + 1;
	while (++i <= *n) {
		if (heap[i].key > max) {
			max = heap[i].key;
			maxIndex = i;
		}
	}
	return maxIndex;
}
int getMaxIndex_2(element heap[], int i, int* n)
{
	if (i + 1 > *n)
		return 0;
	int end(int);
	int iLevel = levelNumber(i);
	int jLevel = (((iLevel % 2 != 0 && pow(2, iLevel + 1) <= *n )|| end(i))?1:0) + iLevel;
	int j = (iLevel == jLevel) ? i + 1 : pow(2, jLevel-1);
	int max = heap[j].key;
	int maxIndex = j;
	while (j <= *n) {
		if (heap[j].key > max) {
			max = heap[j].key;
			maxIndex = j;
		}
		if (end(j)) {
			if (j % 2 == 0) {
				if (pow(2, jLevel + 2) <= *n) {
					jLevel += 2;
					j = pow(2, jLevel);
				}
				else {
					jLevel++;
					j++;
				}
			}
			else {
				jLevel++;
				j++;
			}
		}
		else
			j++;
	}
	return maxIndex;
}
element delete_max(element heap[], int *n)
{
	int i, last, k, parent;
	element temp, x;
	if (!*n) {
		fprintf(stderr, "The heap is empty.\n");
		heap[0].key = INT_MIN;
		return heap[0];
	}
	x = heap[(*n)--];
	k = getMaxIndex_2(heap, 1, n);
	heap[0] = heap[k];
	for (i = k, last = (*n) / 2; i <= last;) {
		k = getMaxIndex_2(heap, i, n);
		if (x.key >=heap[k].key)break;
		heap[i] = heap[k];
		if (k <= 2 * i + 1&&level(i)!=level(k)) {
			i = k;
			break;
		}
		parent = k / 2;
		if (heap[parent].key > x.key)
			SWAP(heap[parent], x, temp);
		i = k;
	}
	heap[i] = x;
	return heap[0];
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
	for (int i = 0; i < n; i++)
		printf("---");
	putchar('\n');
	int i = 1;
	for (; i <= n; i++) {
		printf("[ %d ]", heap[i].key);
		if (end(i))
			putchar('\n');
	}
	if (!end(i-1))putchar('\n');
	for (int i = 0; i < n; i++)
		printf("---");
	putchar('\n');
}
void test()
{
	n = 0;
	srand(time(0));
	element item;
	for (int i = 1; i < MAX_SIZE; i++){
		item.key = rand() % MAX_SIZE;
		min_max_insert(heap, &n, item);
	}
	printHeap();
	
	
}
