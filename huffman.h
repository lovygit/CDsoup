#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode,*HuffmanTree;
typedef char* *HuffmanCode;

void Select(HuffmanTree* HT, int pos, int* min1, int* min2) {
	int minWeight1, minWeight2;
	for (int i = 1; i < pos; i++) {
		if ((*HT + i)->parent == 0) {
			minWeight1 = minWeight2 = (*HT + i)->weight;
			(*min1) = (*min2) = i;
			break;
		}
	}
	for (int i = 1; i < pos; i++) {
		//printf("(*HT + i)->parent == 0? %d\n", (*HT + i)->parent == 0);
		if ((*HT + i)->parent == 0&&(*HT+i)->weight < minWeight1) {
			(*min1) = i;
			minWeight1 = (*HT + i)->weight;
			//printf("I come here(1)\n");
		}
	}
	for (int i = 1; i < pos; i++) {
		if ((*HT + i)->parent == 0&&
			(*HT + i)->weight < minWeight2&&i!=(*min1)) {
			(*min2) = i;
			minWeight2 = (*HT + i)->weight;
			//printf("I come here(2)\n");
		}
	}
	if (*min1 == *min2)
		for (int i = 1; i < pos; i++)
			if ((*HT + i)->parent == 0)
				*min2 = i;
}
void HuffmanCoding(HuffmanTree* HT, HuffmanCode* HC, int* w, int n) {
	//w 存放n个字符的权值(>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
	if (n <= 1)return;
	int m = n * 2 - 1;
	*HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode));//0号单元空置
	HuffmanTree p;
	int i = 1;
	for (p = (*HT) + 1; i <= n; ++i, ++p, ++w) {
		p->weight = *w;
		p->parent = p->lchild = p->rchild = 0;
	}
	for (; i <= m; i++, p++) {
		p->weight= p->parent = p->lchild = p->rchild = 0;
	}
	for (i = n + 1; i <= m; i++) {
		int s1, s2;
		Select(HT, i, &s1, &s2);
		((*HT)+s1)->parent = i;
		((*HT)+s2)->parent = i;
		((*HT) + i)->lchild = s1;
		((*HT) + i)->rchild = s2;
		((*HT) + i)->weight = ((*HT) + s1)->weight + ((*HT) + s2)->weight;
	}
	/*for (int i = 1; i <= m; i++) {
		printf("Weight: %2d,Parent: %d,lChild: %d,rChild: %d\n", ((*HT) + i)->weight, ((*HT) + i)->parent, ((*HT) + i)->lchild, ((*HT) + i)->rchild);
	}*/
	//---从叶子到根逆向求每个字符的赫夫曼编码 ---
	*HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));//分配n个字符编码的头指针向量
	char* cd = (char*)malloc(n*sizeof(char));//分配求编码的工作空间
	cd[n - 1] = '\0';//编码结束符
	for (i = 1; i <= n; i++) {
		int start = n - 1;//编码结束符的位置
		int f;
		int c;
		for (c = i, f = ((*HT)+i)->parent; f != 0; c = f, f = ((*HT)+f)->parent)//从叶子到根逆向求编码
			if (((*HT) + f)->lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		(*HC)[i] = (char*)malloc((n - start)*sizeof(char));//给第i个字符编码分配空间
		strcpy_s((*HC)[i],n-start, cd + start);
	}
	/*for (int i = 1; i <= n; i++)
		printf("Code: %s\n", (*HC)[i]);*/
	free(cd);
}
//向量的前n个节点（不包括0）表示叶子节点，最后的[n+1,2*n-1]为"根"节点，并且HT[2*n-1]位root节点
void createHuffmanCode(HuffmanTree HT,HuffmanCode* HC,int n) {
	*HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1));
	char* cd = malloc(sizeof(char)*n);
	int m = 2 * n - 1;
	int p = m;
	int cdLen = 0;
	for (int i = 1; i <= m; i++)
		(HT)[i].weight = 0;//遍历赫夫曼树时用作节点状态标志

	while (p) {//if p==0意味着退回到了根节点
		if ((HT)[p].weight == 0) {//向左
			(HT)[p].weight = 1;
			if ((HT)[p].lchild != 0) {
				p = (HT)[p].lchild;
				cd[cdLen++] = '0';
			}
			else if (HT[p].rchild == 0) {//登记叶子节点的字符编码
				(*HC)[p] = (char*)malloc(sizeof(char)*(cdLen + 1));
				cd[cdLen] = '\0';
				strcpy_s((*HC)[p], cdLen + 1, cd);
			}
		}
		else if (HT[p].weight == 1) {//向右
			HT[p].weight = 2;
			if (HT[p].rchild != 0) {
				p = HT[p].rchild;
				cd[cdLen++] = '1';
			}
		}
		else {//回退
			HT[p].weight = 0;
			p = HT[p].parent;
			--cdLen;
		}
	}
}
void test() {
	int weight[] = { 7,5,2,4,4,3,8,9 };
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(&HT, &HC, weight, 8);
	for (int i = 1; i <= 8; i++)
		printf("Code: %s\n", HC[i]);
	createHuffmanCode(HT, &HC, 8);
	printf("----------\n");
	for (int i = 1; i <= 8; i++)
		printf("Code: %s\n", HC[i]);
}