#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int parent[MAX];
int find(int i)
{
	for (int root = i; parent[i] >= 0; i = parent[i]);
	return i;
}
int find2(int i)
{
	int root,lead,trail;
	for (root = i; parent[root] >= 0; root = parent[root]);
	for (trail = i; trail != root; trail = lead) {
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}
void unionClass(int i, int j)
{
	//printf("i is %d and j is %d\n", i, j);
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}
void init()
{
	for (int i = 0; i < MAX; i++)
		parent[i] = -1;
}
void equalClass()
{
	init();
	int n, i=1, j=1;
	int iParent, jParent;
	printf("Please enter the size(<=%d).-->",MAX);
	scanf_s("%d", &n);
	while (n--> 0&&i>0&&j>0) {
		printf("Please input a pair of number(-1 -1 to quit)-->");
		scanf_s("%d%d", &i, &j);
		while (i >= MAX || j >= MAX||i==j) {
			printf("Illegal data,input again.--->");
			scanf_s("%d%d", &i, &j);
		}
		iParent = find(i);
		jParent = find(j);
		if(!((jParent>=0)&&(iParent>=0)&&jParent==iParent))
			unionClass(iParent, jParent);
	}
	for (int i = 0; i < MAX; i++) 
		if (parent[i] < 0&&parent[i]!=-1) {
			printf("\nNewClass: %5d", i);
			for (int j = 0; j < MAX; j++) {
				if (parent[j] >= 0) {
					jParent = find(j);
					if (jParent == i)
						printf("%5d", j);
				}
			}
		}
	putchar('\n');
}
