#pragma once
#include<stdio.h>
#include<math.h>
#include<time.h>
#include"sortUnit.h"
//#define MAX_SIZE 10
int table[MAX_SIZE];
#define SWAP(A,B,C) (C=A,A=B,B=C)
//typedef struct {
//	int key;
//	int link;
//	int linkb;
//}element;
void list_sort1(element list[], int n, int start)//n is the amount of the list
{
	/*start is a pointer to the list of n sorted elements,
	linked together by the field link. linkb is assumed to be
	present in each element.The elements are rearranged so that
	the resulting elements list[0],..., list[n-1] are consecutive and sorted.*/
	int last, current;
	element temp;
	last = -1;
	for (current = start; current != -1; current = list[current].link) {
		/*establish the back links for the list */
		/* 初始时，link[index].link=-1 */
		list[current].linkb = last;
		last = current;
	}
	for (int i = 0; i < n - 1; i++) {
		/* move list[start] to position i while maintaining the list */
		if (start != i) {
			if (list[i].link + 1)
				list[list[i].link].linkb = start;
			list[list[i].linkb].link = start;// only list[start].linkb == -1,but start!=i
			SWAP(list[i], list[start], temp);
		}
		start = list[i].link;
	}
}
void list_sort2(element list[], int n, int start)//n is the max index of the list
{
	/*list sort with only one link field */
	int i, next;
	element temp;
	for (i = 0; i < n - 1; i++) {
		for (int j = 0; j < 10; j++)
			printf("< %d,%d > ", list[j].key, list[j].link);
		putchar('\n');
		while (start < i)
			start = list[start].link;
		next = list[start].link;
		if (start != i) {
			SWAP(list[i], list[start], temp);
			list[i].link = start;//提示已经被移动
		}
		start = next;
	}//此方法运行后link域失去了原来的含义，即不在是有意义的指针
}
void tableInit()
{
	for (int i = 0; i < MAX_SIZE; i++)
		table[i] = i;
}
void createTableByquickSort(element list[], int left, int right)
{
	if (left<right) {
		int low, high;
		element pivot = list[table[left]];
		int temp2;
		low =left;
		high = right+1;
		while (low < high) {
			do
				high--;
			while (high > low&&list[table[high]].key>=pivot.key);
			do
				low++;
			while (low < high&&list[table[low]].key <= pivot.key);

			if (low<high) {
				SWAP(table[low], table[high], temp2);
			}
		}
		SWAP(table[left], table[high], temp2);
		createTableByquickSort(list,left, high - 1);
		createTableByquickSort(list, high + 1,right);
	}
}
void createTableByInsertionSort(element list[], int n)
{
	tableInit();
	element next;
	int temp;
	for (int i = 1; i < n; i++) {
		next = list[table[i]];
		int j = i - 1;
		while (j >= 0 && list[table[j]].key>next.key) {
			//table[j + 1] = table[j];
			SWAP(table[j + 1], table[j],temp);
			j--;
			/*printf("j is %d\n", j);
			for (int i = 0; i < 9; i++)
				printf("%5d", table[i]);
			putchar('\n');*/
		}
		//table[j + 1] = table[i];
		//SWAP(table[j + 1], table[i], temp);
	}
}
void createTableBySelectionSort(element list[], int n)
{
	tableInit();
	int temp;
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++)
			if (list[table[i]].key>list[table[j]].key)
				SWAP(table[i], table[j], temp);
	}
}

void createTableByMergeSort_merge(element list[], int start, int end, int n)//n is the max index
{
	int i = start, j = end + 1;
	int k=start;
	int tableCopy[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
		tableCopy[i] = table[i];
	while (i <= end&&j <= n) {
		if (list[table[i]].key <= list[table[j]].key)
			tableCopy[k++] = table[i++];
		else
			tableCopy[k++] = table[j++];
	}
	while (i <= end)
		tableCopy[k++] = table[i++];
	while (j <= n)
		tableCopy[k++] = table[j++];

	for (i = 0; i < MAX_SIZE; i++)
		table[i] = tableCopy[i];
}
void createTableByMergeSort_merge_pass(element list[], int length, int n)//n is the amount
{
	int i = 0;
	for (; i <=n - 2 * length; i += 2 * length)//i+2*length-1<n
		createTableByMergeSort_merge(list,i, i + length - 1, i + 2 * length - 1);
	if (i + length < n-1)
		createTableByMergeSort_merge(list,i, i + length - 1, n - 1);
}
void createTableByMergeSort_merge_sort(element list[], int n)//n is the amount of the list
{
	int length = 1;
	while (length < n) {
		createTableByMergeSort_merge_pass(list, length, n);
		length *= 2;
	}
}

void createTableByHeapSort_adjust(element list[],int root, int n)//n is the max index
{
	int child = root * 2;
	int rootKey = list[table[root]].key;
	int temp=table[root];
	while (child <= n) {
		if (child < n&&list[table[child]].key < list[table[child + 1]].key)
			child++;
		if (list[table[child]].key <= rootKey)
			//return;
			break;
		else {
			//table[child / 2] = table[child];
			//SWAP(table[child / 2], table[child], temp);
			table[child / 2] = table[child];
			child *= 2;
		}
	}
	table[child / 2] = temp;
	//table[child / 2] = table[root];
	//SWAP(table[child / 2], table[root], temp);
}
void createTableByHeapSort_heapSort(element list[], int n)//n is the max index
{
	int temp;
	for (int i = n/2;i>=0; i--)
		createTableByHeapSort_adjust(list, i, n);
	for (int i = n - 1; i > 0; i--) {
		SWAP(table[1], table[i + 1], temp);
		createTableByHeapSort_adjust(list, 1, i);
	}
}

void table_sort(element list[], int n, int table[])//table 是交换表
{
	int i, next, current;
	element temp;
	for (i = 0; i < n - 1; i++) {
		if (table[i]!= i) {//物理顺序需要重排
			current = i;
			temp = list[i];
			do {
				next = table[current];
				list[current] = list[next];
				table[current]= current;
				current = next;
			} while (table[current] != i);
			list[current] = temp;
			table[current] = current;
		}
	}
}
void test()
{
	element list[10];
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		list[i].key = rand() % 100;
		list[i].link = -1;
	}
	for (int i = 0; i < 10; i++)
		printf("[ %d ]", list[i].key);
	putchar('\n');
	//int start=rmerge(list, 0, 8, 9);
	//list_sort1(list, 9, start);
	//list_sort2(list, 9, start);
	tableInit();
	//createTableByquickSort(list, 0, 9);
	//createTableByInsertionSort(list,10);
	//createTableBySelectionSort(list, 10);
	//createTableByMergeSort_merge_sort(list, 10);
	createTableByHeapSort_heapSort(list, 9);
	for (int i = 1; i < 10; i++)
		printf("%6d", table[i]);
	putchar('\n');
	table_sort(list, 10, table);
	for (int i = 1; i < 10; i++)
		printf("key is %5d,link is %5d\n", list[i].key,list[i].link);

}
