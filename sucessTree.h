#pragma once
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#define K 100
#define MAX 65535
int leaves[K + 1];
int successTree[K];//successTree[0]δ�洢����
/* ���ڵ����ڲ��ڵ���е��� */
void adjust(int i)//i is the index in successTree
{
	int m, n;
	if (2 * i <K)               /* ��ȡ�������ӽ�� */
		m = successTree[2 * i];
	else
		m = 2 * i - K + 1;//is leaf node---> 9 (9,10),8 (7,8)
	if (2 * i + 1<K)                 /* ��ȡ�����Һ��ӽڵ� */
		n = successTree[2 * i + 1];
	else
		n = 2 * i + 1 - K + 1;
	successTree[i] = leaves[m] > leaves[n] ? n : m; /* ����ʤ���ж� */
}
 /* ��ʼ��Ҷ�ӽڵ㲢���ڲ��ڵ���������ڶѵĵ��� */
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
/* ���¶��϶�ʤ�������е��� */
void adjustToRoot(int i)//modify leaves[i]
{
	int parent = (i + K - 1) / 2; /* �Դӵ�ǰ�ڵ㵽���ڵ�·���ϵ����нڵ���е��� --��������*/
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
//	int parent = (i + MAX - 1) / 2;		--����successTree��������1&&leaves��������1��ʼ����������������ϵ
//	while (parent) {				--����successTree��������1��ʼ������˼����ж�����
//		fillNode(parent);
//		parent /= 2;
//	}
//}