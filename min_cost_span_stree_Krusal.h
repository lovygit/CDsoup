#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICE 100
#define TRUE 1
#define FALSE 0
struct	edge{
	int start;
	int end;
	int weight;
};
typedef struct node *node_pointer;
struct node {
	int key;
	node_pointer link;
};
node_pointer graph[MAX_VERTICE];
node_pointer new_node()
{
	node_pointer temp = (node_pointer)malloc(sizeof(struct node));
	if (!temp) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	temp->link = NULL;
	return temp;
}
struct graphEdge{
	struct edge graphEdge[MAX_VERTICE];
	int amount;
};
struct graphEdge graphEdgeData;
struct graphEdge selectEdge_Kruskal;

int graphParent[MAX_VERTICE];
void createEdge()
{
	graphEdgeData.amount = 0;
	int start=1, end=1, weight=0;
	printf("Please input the start point,end point,and the weight.--->");
	scanf_s("%d%d%d", &start, &end, &weight);
	while (start >= 0 && end >= 0 && weight >= 0) {
		graphEdgeData.graphEdge[graphEdgeData.amount].start = start;
		graphEdgeData.graphEdge[graphEdgeData.amount].end = end;
		graphEdgeData.graphEdge[graphEdgeData.amount++].weight = weight;
		printf("Please input the start point,end point,and the weight.--->");
		scanf_s("%d%d%d", &start, &end, &weight);
	}
}
void printGraphEdgeData()
{
	for (int i = 0; i < graphEdgeData.amount; i++) {
		printf("(%d)------------------\n", i + 1);
		printf("start point:%5d\n", graphEdgeData.graphEdge[i].start);
		printf("end point:%5d\n", graphEdgeData.graphEdge[i].end);
		printf("weight:%5d\n", graphEdgeData.graphEdge[i].weight);
		printf("----------------------\n");
	}
}
void linkNode(int key, int child)
{
	node_pointer temp=graph[key];
	while (temp)
		temp = temp->link;
	temp = new_node();
	temp->key = child;
	if (graph[key] == NULL)
		graph[key] = temp;
}
void initGraphVectexData()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		graph[i] = NULL;
}

void initGraphParent()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		graphParent[i] = -1;
}
int getParent(int n)
{
	int temp = n;
	while (graphParent[temp]>= 0) {
		temp = graphParent[temp];
	}
	return temp;
}
void unionGraph(int u, int v)
{
	int uParent = getParent(u);
	int vParent = getParent(v);
	int temp = graphParent[uParent] + graphParent[vParent];
	if (graphParent[uParent] > graphParent[vParent]) {
		graphParent[uParent] = vParent;
		graphParent[vParent] = temp;
	}
	else {
		graphParent[uParent] = temp;
		graphParent[vParent] = uParent;
	}
}
void createGraphParentByGraphEdgeData()
{
	initGraphParent();
	for (int i = 0; i < graphEdgeData.amount; i++) {
		unionGraph(graphEdgeData.graphEdge[i].start, graphEdgeData.graphEdge[i].end);
	}
}
void createGraphParentByselectEdge_Kruskal()
{
	//printf("//createGraphParentByselectEdge_Kruskal()\n");
	initGraphParent();
	for (int i = 0; i < selectEdge_Kruskal.amount; i++) {
		unionGraph(selectEdge_Kruskal.graphEdge[i].start, selectEdge_Kruskal.graphEdge[i].end);
	}
}
void printGraphParent()
{
	printf("--------------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		if (graphParent[i] < -1) {
			printf("%d--children:", i);
			for (int j = 0; j < MAX_VERTICE; j++)
				if (graphParent[j] == i)
					printf("%5d||", j);
			putchar('\n');
		}
	}
	putchar('\n');
}

void createLinkByEdgeCollection()
{
	initGraphVectexData();
	for (int i = 0; i < graphEdgeData.amount; i++) {
		linkNode(graphEdgeData.graphEdge[i].start, graphEdgeData.graphEdge[i].end);
	}
}
void printLink()
{
	node_pointer temp=NULL;
	for (int i = 0; i < MAX_VERTICE;i++)
		if (graph[i]) {
			temp = graph[i];
			printf("%d--Children:",i);
			while (temp) {
				printf("%5d||",temp->key);
				temp = temp->link;
			}
			putchar('\n');
		}
	putchar('\n');
}

void selectEdge_KruskalFromData()
{
	selectEdge_Kruskal.amount = 0;
	int min = -1;
	int absValue;
	while (TRUE) {
		int i,imin=0;
		absValue = 10000;
		for (i = 0; i < graphEdgeData.amount; i++) {
			if (graphEdgeData.graphEdge[i].weight>min&&
				graphEdgeData.graphEdge[i].weight - min <= absValue) {
				imin = i;
				absValue=graphEdgeData.graphEdge[i].weight - min;
			}
		}
		min = graphEdgeData.graphEdge[imin].weight;
		createGraphParentByselectEdge_Kruskal();
		if(getParent(graphEdgeData.graphEdge[imin].start)!=
			getParent(graphEdgeData.graphEdge[imin].end)||selectEdge_Kruskal.amount==0)
		selectEdge_Kruskal.graphEdge[selectEdge_Kruskal.amount++] = graphEdgeData.graphEdge[imin];
		for (int j = imin; j < graphEdgeData.amount-1; j++)
			graphEdgeData.graphEdge[j] = graphEdgeData.graphEdge[j + 1];
		if (--graphEdgeData.amount==0)break;
	}
}
void printselectEdge_Kruskal()
{
	//printf("//printselectEdge_Kruskal()\n");
	for (int i = 0; i < selectEdge_Kruskal.amount; i++) {
		printf("(%d)------------------\n", i + 1);
		printf("start point:%5d\n", selectEdge_Kruskal.graphEdge[i].start);
		printf("end point:%5d\n", selectEdge_Kruskal.graphEdge[i].end);
		printf("weight:%5d\n", selectEdge_Kruskal.graphEdge[i].weight);
		printf("----------------------\n");
	}
}
int treeIsConnected_selectEdge_Kruskal()
{
	createGraphParentByselectEdge_Kruskal();
	int sameParent = getParent(selectEdge_Kruskal.graphEdge[0].start);
	for (int i = 0; i < MAX_VERTICE; i++)
		if (graphParent[i] >= 0)
			if (sameParent != getParent(i))
				return 0;
	return 1;
}
int treeWeight_selectEdge_Kruskal()
{
	int result=0;
	for (int i = 0; i < selectEdge_Kruskal.amount; i++)
		result += selectEdge_Kruskal.graphEdge[i].weight;
	return result;
}

