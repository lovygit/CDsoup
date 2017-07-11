#pragma once
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define K 100
#define MAX 65535
int leaves[K + 1];
int successTree[K];//successTree[0]未存储数据
/* 对于单个内部节点进行调整 */
void adjust(int i)//i is the index in successTree
{
	int m, n;
	if (2 * i <K)               /* 获取它的左孩子结点 */
		m = successTree[2 * i];
	else
		m = 2 * i - K + 1;//is leaf node---> 9 (9,10),8 (7,8)
	if (2 * i + 1<K)                 /* 获取它的右孩子节点 */
		n = successTree[2 * i + 1];
	else
		n = 2 * i + 1 - K + 1;
	successTree[i] = leaves[m] > leaves[n] ? n : m; /* 进行胜负判定 */
}
 /* 初始化叶子节点并对内部节点进行类似于堆的调整 */
int valueExist(int i, int value)
{
	for (int j = 1; j < i; j++)
		if (leaves[j] == value)
			return 1;
	return -1;
}
void initTree()
{
	int temp;
	srand(time(0));
	printf("Please input %d leaves' value.\n", K);
	for (int i = 1; i < K + 1; i++) {
		//scanf_s("%d", &leaves[i]);
		temp = rand();
		while (valueExist(i, temp) == 1) {
			temp = rand()%10000;
		}
		leaves[i] = temp;
	}
	for (int i = K ; i>0; i--)//------    i>0
		adjust(i);
}
/* 自下而上对胜者树进行调整 */
void adjustToRoot(int i)//modify leaves[i]
{
	int parent = (i + K - 1) / 2; /* 对从当前节点到根节点路径上的所有节点进行调整 --逆向运算*/
	while (parent>0){
		adjust(parent);
		parent = parent / 2;
	}
}
//-------------------------------------------
//#define MAX 10
//int leaves[MAX + 1];
//int successTree[MAX];
//void fillNode(int i) {
//	int m, n;
//	if (2 * i < MAX)
//		m = successTree[2 * i];
//	else
//		m = 2 * i - MAX + 1;
//	if (2 * i + 1 < MAX)
//		n = successTree[2 * i + 1];
//	else
//		n = 2 * i - MAX + 2;
//	successTree[i] = leaves[m] <= leaves[n] ? m : n;
//}
//void createTree() {
//	srand(time(0));
//	for (int i = 1; i <= MAX; i++)
//		leaves[i] = rand() % 1000;
//	for (int i = MAX - 1; i > 0; i--)
//		fillNode(i);
//}
//void adjust(int i) {
//	int parent = (i + MAX - 1) / 2;		--由于successTree的索引从1&&leaves的索引从1开始才有这样的索引关系
//	while (parent) {				--由于successTree的索引从1开始才有如此简洁的判断条件
//		fillNode(parent);
//		parent /= 2;
//	}
//}