#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX	 100000
#define MAX_VERTICE 100
#define TRUE 1
#define FALSE 0
struct node{
	int x;
	int y;
	int weight;
};
struct {
	struct node nodes[MAX_VERTICE];
	int amount;
}graph;
int PrimArray[MAX_VERTICE];
int visited[MAX_VERTICE];
void initVisitArray()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		visited[i] = -1;
}
int  visitedAll()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		if (visited[i] == FALSE)
			return 0;
	return 1;
}
void initGraph()
{
	graph.amount = 0;
}
void initPrimArray()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		PrimArray[i] = -1;
}
void createGraph()
{
	initVisitArray();
	initGraph();
	int x, y, weight;
	printf("x,y,weight--->");
	scanf_s("%d%d%d", &x, &y, &weight);
	while (x >= 0 && y >= 0 && weight >= 0) {
		graph.nodes[graph.amount].x = x;
		graph.nodes[graph.amount].y = y;
		graph.nodes[graph.amount++].weight = weight;
		visited[x] = FALSE;
		visited[y] = FALSE;
		printf("x,y,weight--->");
		scanf_s("%d%d%d", &x, &y, &weight);
	}
}
int findTheMin(int start)//find the min index
{
	int imin = -1;
	int result = MAX;
	for (int i = 0; i < graph.amount;i++)
		if (graph.nodes[i].x == start || graph.nodes[i].y == start) {
			for (int j = 0; j < MAX_VERTICE; j++) 
				if (visited[j] == FALSE) 
					if (graph.nodes[i].x == j || graph.nodes[i].y == j)
						if (graph.nodes[i].weight < result) {
							result = graph.nodes[i].weight;
							imin = i;
						}
		}
	return imin;
}
void printTree()
{
	printf("-------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++)
		if (PrimArray[i] != -1)
			printf("%5d__%d||", i, PrimArray[i]);
	printf("\n-------------------------\n");
}
void createTreeByPrimFunction()
{
	initPrimArray();
	int minIndex = findTheMin(graph.nodes[0].x);
	PrimArray[graph.nodes[0].x] = 0;
	visited[graph.nodes[0].x] = TRUE;
	while (TRUE) {
		//printf("//part one\n");
		int minWeight = MAX;
		int temp;
		int imin = -1;
		for (int i = 0; i < MAX_VERTICE; i++) {
			if (visited[i] == TRUE) {
				//printf("i is %d\n", i);
				temp = findTheMin(i);
				if (temp != -1) {
					if (minWeight > graph.nodes[temp].weight) {
						minWeight = graph.nodes[temp].weight;
						imin =temp;
					}
				}
			}
		}
		//printf("imin is %d\n", imin);
		//printf("graph.nodes[imin].x is %d\n", graph.nodes[imin].x);
		//printf("graph.nodes[imin].y is %d\n", graph.nodes[imin].y);
		//printf("graph.nodes[imin].weight is %d\n", graph.nodes[imin].weight);
		if (visited[graph.nodes[imin].x] == TRUE ) {
			PrimArray[graph.nodes[imin].y] = graph.nodes[imin].weight;
			visited[graph.nodes[imin].y] = TRUE ;
		}
		else {
			PrimArray[graph.nodes[imin].x] = graph.nodes[imin].weight;
			visited[graph.nodes[imin].x] = TRUE ;
		}
		if (visitedAll())break;
	}
}
