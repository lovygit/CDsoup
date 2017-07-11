#pragma once
#include<stdio.h>
#include<limits.h>
#define MAX_VERTICE 3
#define TRUE 1
#define FALSE 0
//int cost[][MAX_VERTICE] = {
//	{0,50,10,1000,45,1000},
//	{1000,0,15,1000,10,1000},
//	{20,1000,0,15,1000,1000},
//	{1000,20,1000,0,35,1000},
//	{1000,1000,30,1000,0,1000},
//	{1000,1000,1000,3,1000,0}
//};
int cost[][MAX_VERTICE] = {
	{0,4,11},
	{6,0,2},
	{3,1000,0}
};
int distance[MAX_VERTICE];
int found[MAX_VERTICE];
int choose(int distance[], int n, int found[])
{
	/*find the smallest distance not yet checked.*/
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n;i++)
		if (!found[i]&& distance[i] < min){
				min = distance[i];
				minpos = i;
		}
	return minpos;
}
//˼�룺�ӵ�v��������ľ���ɷǵݼ��������
void shortestpath(int v, int cost[][MAX_VERTICE], int distance[], int n, int found[])
{
	/*distance[i] represents the shortest path from vertex v
	to i ,found[i] holds a 0 if the shortest path from vertex i
	has not been found and a 1 if it has,cost is the adjacency matrix */
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = FALSE;
		distance[i] = cost[v][i];
	}
	found[v] = TRUE;
	distance[v] = 0;
	for (int i = 0; i < n - 2; i++) {//n-2����һ������Ϊ�ų��Լ�������һ�������ֻ��һ��δ��飬û�б�Ҫ�ٴ�ѭ��
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
			if (!found[w])
				if (distance[u] + cost[u][w] < distance[w])//v��u�ľ������u��w�ľ���С��v��w�ľ���
					distance[w] = distance[u] + cost[u][w];
	}
	for (int i = 0; i < n; i++)
		printf("%5d", distance[i]);
	putchar('\n');
}
