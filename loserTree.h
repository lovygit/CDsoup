#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define K 10
int leaves[K + 1];/* 从下标1开始存储叶子节点值，下标0处存储一个最小值节点 */
int loserTree[K]; /* 存储中间节点值，下标0处存储冠军节点 */
void adjust(int i)//leaves[i]
{
	int parent = (i + K - 1) / 2;//for the first step.--init
	while (parent >0) {
		if (leaves[i] > leaves[loserTree[parent]]) {
			int temp = loserTree[parent];
			loserTree[parent] = i;
			i = temp;//point to the successor
		}
		parent /= 2;
	}
	loserTree[0] = i;//modify the successor.
}
int valueExist(int i, int value)
{
	for (int j = 1; j < i; j++)
		if (leaves[j] == value)
			return 1;
	return -1;
}
void initTree()
{
	srand(time(NULL));
	int temp,i;
	printf("Please input %d data.\n", K);
	for (i = 1; i < K + 1; i++) {
		//scanf_s("%d", leaves + i);
		temp = rand()%1000;
		while (valueExist(i, temp)==1) {
			temp = rand();
		}
		leaves[i] = temp;
	}
	leaves[0] = INT_MIN;
	for (i = 0; i < K; i++)
		loserTree[i] = 0;
	for (i =K; i >0; i--)//自下而上
		adjust(i);
}
/*
#define K 10
int leaves[K + 1];
int successTree[K];
int loserTree[K];
void adjust(int i) {
int m, n;
if (i * 2 < K)
m = successTree[i * 2];
else
m = i * 2 - K + 1;
if (i * 2 + 1 < K)
n = successTree[i * 2 + 1];
else
n = i * 2 - K + 2;
successTree[i] = leaves[m] > leaves[n] ? n : m;
}

void initLeaves() {
for (int i = 1; i < K + 1; i++) {
leaves[i] = rand() % 1000;
}
leaves[0] = -10000;
}
void initSuccessTree() {
for (int i = K; i > 0; i--)
adjust(i);
}
void adjustTreeRoot(int i) {
int parent = (i + K - 1) / 2;
while (parent > 0) {
adjust(parent);
parent /= 2;
}
}
void adjust_(int i) {
int parent = (i + K - 1) / 2;
while (parent > 0) {
if (leaves[i] > leaves[loserTree[parent]]) {
int temp = i;
i = loserTree[parent];
loserTree[parent] = temp;
}
parent /= 2;
}
loserTree[0] = i;
}
void initLoserTree() {
for (int i = 1; i < K; i++)
loserTree[i] = 0;
for (int i = K; i > 0; i--)
adjust_(i);
}
void testLoserAndSuccess() {
int leavesCopy[K + 1];
initLeaves();
for (int i = 1; i < K + 1; i++) {
printf("%5d", leaves[i]);
leavesCopy[i] = leaves[i];
}
printf("\n-------------------------\n");
initSuccessTree();
for (int i = 1; i < K; i++) {
printf("%5d", leaves[successTree[1]]);
leaves[successTree[1]] = 10000;
adjustTreeRoot(successTree[1]);
}
putchar('\n');
for (int i = 1; i < K + 1; i++) {
leaves[i] = leavesCopy[i];
printf("%5d", leaves[i]);
}
printf("\n-------------------------\n");
initLoserTree();
for (int i = 0; i < K; i++)
printf("%5d", loserTree[i]);
putchar('\n');
for (int i = 1; i < K; i++) {
printf("%5d", leaves[loserTree[0]]);
leaves[loserTree[0]] = 10000;
adjust_(loserTree[0]);
}
}
*/