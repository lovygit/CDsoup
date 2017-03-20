#pragma once
#include<stdio.h>
#include<stdlib.h>
#define SWAP(X,Y,T) ((T)=(X),(X)=(Y),(Y)=(T))
typedef struct {
	int key;
}element;
void adjust(element list[], int root, int n)// n is the max index
{
	element temp = list[root];
	int child = 2 * root;
	while (child <= n) {
		if (child < n&&list[child].key < list[child + 1].key)
			child++;
		if (temp.key > list[child].key)
			break;
		else {
			list[child / 2].key = list[child].key;
			child *= 2;
		}
	}
	list[child / 2].key = temp.key;
}
void heapSort(element list[], int n)
{
	element temp;
	for (int i = n / 2; i > 0; i--)
		adjust(list, i, n);//list中的所有父节点都在[1,n/2]中
	for (int i = n - 1; i > 0; i--) {
		SWAP(list[1], list[i + 1], temp);
		adjust(list, 1, i);
	}
}