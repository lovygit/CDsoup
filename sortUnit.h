#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0
//顺序查找
int seqsearch(int list[], int searchPos, int n)//searchPos is a end position
{
	/* [0,n) */
	list[n] = searchPos;
	int i = 0;
	while (i < n&&list[i] != searchPos)i++;
	return (i < n) ? i : -1;
}
//二分查找
int binsearch(int list[], int left, int right,int searchData)
{
	if (left <= right) {
		int min = (left + right) / 2;
		if (list[min] == searchData)
			return min;
		else if (list[min]>searchData)
			return binsearch(list, left, min - 1, searchData);
		else
			return binsearch(list, min + 1, right, searchData);
	}
	return -1;
}
//顺序查找，表验证
void verify1(int list1[], int list2[], int list1_n, int list2_n)//两个表的大小默认为<MAX_SIZE
{
	int marked[MAX_SIZE];
	int pos = -1;
	for (int i = 0; i < MAX_SIZE; i++)
		marked[i] = FALSE;
	for (int i = 0; i < list2_n; i++)
		if ((pos = binsearch(list1, 0, list1_n - 1, list2[i])) < 0)
			printf("%d is not in list1\n", list2[i]);
		else
			marked[pos] = TRUE;
	for (int i = 0; i < list1_n; i++)
		if (!marked[i])
			printf("%d is not in list2\n", list1[i]);
}
void insertion_sort(int list[], int n)
{
	int next;
	int i, j;
	if (n < 2)return;
	for (i = 2; i < n; i++) {
		next = list[i];
		for (j = i - 1; j >= 0 && list[j] > next; j--)
			list[j + 1] = list[j];
		list[j + 1] = next;
	}
}
int increase(int a, int b)
{
	return a > b;
}
int decrease(int a, int b)
{
	return a < b;
}
void insertion_sort2(int data[], int n, int(*p)(int, int))
{
	int next, j;
	if (n < 2)return;
	for (int i = 1; i < n; i++) {
		next = data[i];
		for (j = i - 1; j >= 0 && p(data[j], next); j--)
			data[j + 1] = data[j];
		data[j + 1] = next;
	}
}
void verify2(int list1[], int list2[], int list1_n, int list2_n)
{
	insertion_sort(list1, list1_n);
	insertion_sort(list2, list2_n);
	int m = list1_n;
	int n = list2_n;
	int i , j;
	i = j = 0;
	while (i < m&&j < n) {
		if (list1[i] < list2[j]) {
			printf("%d is not in list2\n", list1[i]);
			i++;
		}
		else if (list1[i]>list2[j]) {
			printf("%d is not in list1\n", list2[j]);
			j++;
		}
		else {
			i++; j++;
		}
	}
	while(i<m)
		printf("%d is not in list2\n", list1[i++]);
	while(j<n)
		printf("%d is not in list1\n", list2[j++]);
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
//快速排序
void quickSort(int list[], int left, int right)
{
	if (left<right) {
		int low, high, pivot;
		pivot = list[left];
		low = left;
		high = right+1;
		while (low < high) {
			do
				high--;
			while (high > low&&list[high]>pivot);
			do
				low++;
			while (low < high&&list[low] < pivot);

			if(low<high)//找到小于pivot的项
			swap(&list[low], &list[high]);
		}
		swap(&list[left], &list[high]);
		quickSort(list, left, high - 1);
		quickSort(list, high + 1, right);
	}
}
//归并两个已经排序的表
void merge(int list[], int sorted[], int start, int end1, int end2)
{
	int i = start;
	int j = end1 + 1;
	int k = start;
	while (i <= end1&&j <=end2) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	while (i <= end1)
		sorted[k++] = list[i++];
	while (j <= end2)
		sorted[k++] = list[j++];
}
void merge_pass(int list[], int sorted[], int n, int length)//n is the size of list
{
	int i;
	for (i = 0; i <= n - 2 * length; i += 2 * length)
		merge(list, sorted, i, i + length - 1, i + 2 * length-1);
	if (i + length < n-1)
		merge(list, sorted, i, i + length - 1, n - 1);
	else
		while (i < n) {
			sorted[i] = list[i];
			i++;
		}
}
void merge_sort(int list[], int n)
{
	int length = 1;
	int temp[MAX_SIZE];
	while (length < n) {
		merge_pass(list, temp, n, length);
		length *= 2;
		merge_pass(temp, list, n, length);
		length *= 2;
	}
}
//递归实现归并排序
typedef struct {
	int key;
	int link;//link 是整数，不是动态指针-->逻辑指针
	int linkb;
} element;
int listmerge(element list[], int first, int second,int n)//n+1 is the size of list
/*merge lists pointed by first and second.*/
{
	int start = n;//start is the cursor!!!
	while (first!= -1 && second != -1) {
		if (list[first].key <= list[second].key) {
			list[start].link = first;
			start = first;
			first = list[first].link;
		}
		else {
			list[start].link = second;
			start = second;
			second = list[second].link;
		}
	}
	if (first == -1)
		list[start].link = second;
	else
		list[start].link = first;
	return list[n].link;
}
int rmerge(element list[], int low, int high ,int n)//n is the max index of list-->link[n] is to save the start
{
	if (low >= high)
		return low;
	else {
		int middle = (low + high) / 2;
		return listmerge(list, rmerge(list, low, middle, n), rmerge(list, middle + 1, high, n), n);
	}
}
