#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX_VERTICE 9
//AOVÍø---activity on vertex network
typedef struct node *node_pointer;
struct node {
	int duration;
	int vertex;
	node_pointer link;
};
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
typedef struct {
	int count;
	node_pointer link;
}hdnodes;
hdnodes graph[MAX_VERTICE];
hdnodes graph_reverse[MAX_VERTICE];
int earliest[MAX_VERTICE];
int latest[MAX_VERTICE];
int max=INT_MIN;
//»ñµÃÍøÂçGµÄÍØÆËÐòÁÐ
void topsort(hdnodes graph[], int n)
{
	int i, j, k, top;
	node_pointer ptr;
	top = -1;
	for (i = 0; i < n;i++)
		if (!graph[i].count) {
			graph[i].count = top;
			top = i;
		}
	for (i = 0; i < n;i++)
		if (top == -1) {
			fprintf(stderr, "\nNetwork has a cycle .Sort terminated.\n");
			exit(1);
		}
		else {
			j = top;
			top = graph[top].count;
			printf("[ v%d ]", j);
			for (ptr = graph[j].link; ptr; ptr = ptr->link) {
				k = ptr->vertex;
				graph[k].count--;
				if (!graph[k].count) {
					graph[k].count = top;
					top = k;
				}
			}
		}
}
void initGraph()
{
	for (int i = 0; i < MAX_VERTICE; i++) {
		graph[i].link = NULL;
		graph[i].count = 0;
	}
}
void initGraphReverse()
{
	for (int i = 0; i < MAX_VERTICE; i++) {
		graph_reverse[i].link = NULL;
		graph_reverse[i].count = 0;
	}
}
void createGraphNoDur()
{
	initGraph();
	int vertexA, vertexB;
	node_pointer* temp = NULL;
	printf("vertexA,vertexB:--->");
	scanf_s("%d%d", &vertexA, &vertexB);
	while (vertexA >= 0 && vertexB >= 0 ) {
		graph[vertexB].count++;
		if (graph[vertexA].link == NULL) {
			graph[vertexA].link = new_node();
			graph[vertexA].link->vertex = vertexB;
		}
		else {
			temp = &graph[vertexA].link;
			while (*temp)
				temp = &(*temp)->link;
			*temp = new_node();
			(*temp)->vertex = vertexB;
		}
		printf("vertexA,vertexB:--->");
		scanf_s("%d%d", &vertexA, &vertexB);
	}
}
void createGraphWithDur()
{
	initGraph();
	int vertexA, vertexB,duration;
	node_pointer* temp = NULL;
	FILE* ptr;
	fopen_s(&ptr, "f:/documents/temp.txt", "w");
	fprintf(ptr, "%d %d %d\n", 0, 1, 6);
	fprintf(ptr, "%d %d %d\n", 0, 2, 4);
	fprintf(ptr, "%d %d %d\n", 0, 3, 5);
	fprintf(ptr, "%d %d %d\n", 1, 4, 1);
	fprintf(ptr, "%d %d %d\n", 2, 4, 1);
	fprintf(ptr, "%d %d %d\n", 3, 5, 2);
	fprintf(ptr, "%d %d %d\n", 4, 6, 9);
	fprintf(ptr, "%d %d %d\n", 4, 7, 7);
	fprintf(ptr, "%d %d %d\n", 5, 7, 4);
	fprintf(ptr, "%d %d %d\n", 6, 8, 2);
	fprintf(ptr, "%d %d %d\n", 7, 8, 4);
	fclose(ptr);
	fopen_s(&ptr, "f:/documents/temp.txt", "r");
	//printf("vertexA,vertexB,duration:--->");
	while (fscanf_s(ptr,"%d%d%d", &vertexA, &vertexB, &duration)==3&&vertexA >= 0 && vertexB >= 0&&duration>=0) {
		graph[vertexB].count++;
		if (graph[vertexA].link == NULL) {
			graph[vertexA].link = new_node();
			graph[vertexA].link->vertex = vertexB;
			graph[vertexA].link->duration = duration;
		}
		else {
			temp = &graph[vertexA].link;
			while (*temp)
				temp = &(*temp)->link;
			*temp = new_node();
			(*temp)->vertex = vertexB;
			(*temp)->duration = duration;
		}
		//printf("vertexA,vertexB,duration:--->");
		//scanf_s("%d%d%d", &vertexA, &vertexB,&duration);
	}
	fclose(ptr);
}
void printGraphNoDur()
{
	node_pointer temp = NULL;
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		printf("%d--[ %d ]||->", i, graph[i].count);
		temp = graph[i].link;
		while (temp) {
			printf(" < %d > ", temp->vertex);
			temp = temp->link;
		}
		putchar('\n');
	}
	printf("--------------------------\n");
}
void printGraphWithDur()
{
	node_pointer temp = NULL;
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		printf("%d--[ %d ]||->", i, graph[i].count);
		temp = graph[i].link;
		while (temp) {
			printf("[ Ver:%d,Dur:%d ]", temp->vertex,temp->duration);
			temp = temp->link;
		}
		putchar('\n');
	}
	printf("--------------------------\n");
}
//AOEÍø--activity on  edge network
void initEarliestArrayMin()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		earliest[i] = 0;
}
void initLatestArrayMax()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		latest[i] = max;
}
void createEarliesArray(hdnodes graph[],int n)
{
	initEarliestArrayMin();
	int i, j, k, top, cnt = 0;
	node_pointer ptr;
	top = -1;
	for (i = 0; i < n; i++)
		if (!graph[i].count) {
			graph[i].count = top;
			top = i;
			cnt++;
		}
	for (i = 0; i < n; i++)
		if (top == -1) {
			if (cnt == n)
				return;
			fprintf(stderr, "\nNetwork has a cycle .Sort terminated.\n");
			exit(1);
		}
		else {
			j = top;
			top = graph[top].count;
			//printf("[ v%d ]", j);
			for (ptr = graph[j].link; ptr; ptr = ptr->link) {
				k = ptr->vertex;
				graph[k].count--;
				if (!graph[k].count) {
					graph[k].count = top;
					top = k;
					cnt++;
				}
				if (earliest[k] < earliest[j] + ptr->duration)
					earliest[k] = earliest[j] + ptr->duration;
			}
		}
	for (int i = 0; i < MAX_VERTICE; i++)
		if (max < earliest[i])
			max = earliest[i];
}
void printEarliestArray()
{
	printf("EarliestArray: ");
	for (int i = 0; i < MAX_VERTICE; i++)
		printf("[ %d ]", earliest[i]);
	putchar('\n');
}
void createGraphReverseByGraph()
{
	initGraphReverse();
	node_pointer temp = NULL;
	node_pointer* temp_pointer = NULL;
	for (int i = 0; i < MAX_VERTICE; i++) {
		temp = graph[i].link;
		while (temp) {
			graph_reverse[i].count++;
			temp = temp->link;
		}
		for (int j = 0; j < MAX_VERTICE; j++) {
			temp = graph[j].link;
			while (temp) {
				if (temp->vertex == i) {
					if (graph_reverse[i].link == NULL) {
						graph_reverse[i].link = new_node();
						graph_reverse[i].link->duration = temp->duration;
						graph_reverse[i].link->vertex = j;
					}
					else {
						temp_pointer = &(graph_reverse[i].link);
						while (*temp_pointer)
							temp_pointer = &(*temp_pointer)->link;
						*temp_pointer = new_node();
						(*temp_pointer)->duration = temp->duration;
						(*temp_pointer)->vertex = j;
					}
				}
				temp = temp->link;
			}
		}
	}
}
void printLatestArray()
{
	printf("LatestArray: ");
	for (int i = 0; i < MAX_VERTICE; i++)
		printf("[ %d ]", latest[i]);
	putchar('\n');
}
void createLatestArray(hdnodes graph[],int n)
{
	//createGraphReverseByGraph();
	initLatestArrayMax();
	int i, j, k, top;
	node_pointer ptr;
	top = -1;
	for (i = 0; i < n; i++)

		if (!graph_reverse[i].count) {
			graph_reverse[i].count = top;
			top = i;
		}
	for (i = 0; i < n; i++)
		if (top == -1) {
			fprintf(stderr, "\nNetwork has a cycle .Sort terminated.\n");
			printf("n is %d\n", n);
			exit(1);
		}
		else {
			j = top;
			top = graph_reverse[top].count;
			//printf("[ v%d ]", j);
			for (ptr = graph_reverse[j].link; ptr; ptr = ptr->link) {
				k = ptr->vertex;
				graph_reverse[k].count--;
				if (!graph_reverse[k].count) {
					graph_reverse[k].count = top;
					top = k;
				}
				if (latest[k] > latest[j] - ptr->duration)
					latest[k] = latest[j] - ptr->duration;
				//printLatestArray();
			}
		}
}

void printGraphReverseNoDur()
{
	node_pointer temp = NULL;
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		printf("%d--[ %d ]||->", i, graph_reverse[i].count);
		temp = graph_reverse[i].link;
		while (temp) {
			printf(" < %d > ", temp->vertex);
			temp = temp->link;
		}
		putchar('\n');
	}
	printf("--------------------------\n");
}
void printGraphReverseWithDur()
{
	node_pointer temp = NULL;
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		printf("%d--[ %d ]||->", i, graph_reverse[i].count);
		temp = graph_reverse[i].link;
		while (temp) {
			printf("[ Ver:%d,Dur:%d ]", temp->vertex,temp->duration);
			temp = temp->link;
		}
		putchar('\n');
	}
	printf("--------------------------\n");
}