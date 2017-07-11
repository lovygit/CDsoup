#pragma once
#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICE 100
#define MAX_QUEUE	100
#define MAX_STACK   100
#define MIN2(x,y) ((x)<(y)?x:y)
int visited[MAX_VERTICE];
int dfn[MAX_VERTICE];
int low[MAX_VERTICE];
int num = 0;
void initVisitArray()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		visited[i] = FALSE;
}
typedef struct node *node_pointer;
struct node {
	int vertex;
	node_pointer link;
};
struct edge {
	int u, v;
};
int queue[MAX_QUEUE];
int size = 0;
int top_queue = -1;
void initQueue()
{
	size = 0;
	top_queue = -1;
}
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
node_pointer graph[MAX_VERTICE];
node_pointer dfsTree[MAX_VERTICE];
node_pointer bfsTree[MAX_VERTICE];
void addQueue(int v)
{
	if (size >= MAX_QUEUE) {
		printf("The queue is full.\n");
		return;
	}
	queue[size++] = v;
}
int delQueue()
{
	if (top_queue >= size)
		return -100;
	return queue[++top_queue];
}
int queueEmpty()
{
	return top_queue >= size;
}
struct edge stack[MAX_STACK];
int top_stack = -1;
void addStack(int u, int v)//v is the parent of u
{
	if (top_stack >= MAX_STACK - 1)
		return;
	else {
		stack[++top_stack].u = u;
		stack[top_stack].v = v;
	}
}
void delStack(int* u, int* v)
{
	if (top_stack < 0) {
		printf("The stack is empty.\n");
		return;
	}
	*u = stack[top_stack].u;
	*v = stack[top_stack--].v;
}
void unionGraph(int i, int j)//i is child ,j is parent
{
	if (graph[i] == NULL) {
		graph[i] = new_node();
		graph[i]->vertex = j;
		return;
	}
	node_pointer temp = graph[i];
	while (temp->link)
		temp = temp->link;
	temp->link = new_node();
	temp->link->vertex = j;
}
void dfs(int v)//深度优先搜索
{
	node_pointer w;
	if (!visited[v]) {
		printf("%5d", v);
		visited[v] = TRUE;
	}
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}
void createGraphLink()
{
	int i = 1, j = 1;
	FILE* ptr;
	fopen_s(&ptr, "f:/documents/data2.txt", "r");
	while (i >= 0 && j >= 0) {
		//printf("Please input a pair number.--->");
		//scanf_s("%d%d", &i, &j);
		fscanf_s(ptr, "%d%d", &i, &j);
		/*while ((i >= 0 && j >= 0 && i == j)||i>=MAX_VERTICE||j>=MAX_VERTICE) {
			printf("The datas are illegal. Try again.--->");
			scanf_s("%d%d", &i, &j);
		}*/
		unionGraph(i, j);
		unionGraph(j, i);
	}
	fclose(ptr);
}
void printGraph()
{
	node_pointer temp = NULL;
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		if (graph[i]) {
			printf("%d   Parents/Children: ",i);
			for (temp = graph[i]; temp; temp = temp->link)
				printf("%5d", temp->vertex);
			putchar('\n');
		}
	}
	printf("--------------------------\n");
}
void printGraph_dfs()
{
	initVisitArray();
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE;i++)
		if (graph[i]) {
			dfs(i);
			putchar('\n');
		}
	printf("--------------------------\n");
}
void bfs(int v)//广度优先搜索
{
	initQueue();
	node_pointer w;
	if (!visited[v]) {
		printf("%5d", v);
		visited[v] = TRUE;
	}
	addQueue(v);
	while (!queueEmpty()) {
		v= delQueue();
		for (w = graph[v]; w;w=w->link)
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex);
				addQueue(w->vertex);
				visited[w->vertex]=TRUE;
			}
	}
}
void printGraph_bfs()
{
	initVisitArray();
	printf("--------------------------\n");
	for (int i = 0; i < MAX_VERTICE;i++)
		if (graph[i]) {
			bfs(i);
			putchar('\n');
		}
	printf("--------------------------\n");
}
void initDnfAndLow()
{
	initVisitArray();
	for (int i = 0; i < MAX_VERTICE; i++) {
		dfn[i] = -1;
		low[i] = -1;
	}
	num = 0;
}
void printDfnArray()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		if(dfn[i]!=-1)
			printf("[ %d,%d ]",i, dfn[i]);
	putchar('\n');
}
void printLowArray()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		if (low[i] != -1)
			printf("[ %d,%d ]", i, low[i]);
	putchar('\n');
}
void dfnLow_(int u, int v)
{
	/*compute dfn and low while persorming a dfs search
	begin at vertex u,v is the parent of u(if any)*/
	node_pointer ptr;
	int w;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (dfn[w]<0) {
			dfnLow_(w,u);
			low[u] = MIN2(low[w], low[u]);//if u's children can recycle to a node,whose low value is less,low[u] is the same
			printDfnArray();
			printLowArray();
			printf("-------------------\n");
		}
		else if (w != v) {/*如果顶点u不是一个根节点，那么当且仅当u至少有一个儿子结点w，
						  并且w不能通过自己的后代节点到达u的祖先节点，那么定点u才是一个关节点，
						  */
			//u 的邻接表中有一个是父节点，不看做子节点。low[u]只与子节点的low值有关
			//w!=v 在w与v构成一个环的时候出现，因为w并不是v“深度优先遍历”的直接祖先
			low[u] = MIN2(low[u], dfn[w]);
			printDfnArray();
			printLowArray();
			printf("-------------------\n");
		}
	}
}
int dfnLow(int u)
{
	initDnfAndLow();
	dfnLow_(u, -1);
}
void bicon_(int u, int v)
{
	/*compute dfn and low,and output the edge of G by their biconnected components,
	v is the parent(if any) of the u (if any) in the resulting spanning tree.It is 
	assumed that all entries of dfn[] have been initialed to -1,num has been initialized to 0,
	and the stack has been set to empty
	*/
	node_pointer ptr;
	int x, y,w;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (w != v&&dfn[w] < dfn[u]) 
			addStack(w, u);
		//there has two condition 1.w has been visited before u,2.w has not been visited.
		//condition one
		if (dfn[w] < 0){//have not visited w
			bicon_(w, u);
			low[u] = MIN2(low[u], low[w]);
			if (low[w] >= dfn[u]) {//low(w)>=dfn(u)的含义就是u中至少有一个节点不与在u之前遍历的节点相连，
				//导致的结果就是如果去掉u那么会产生至少两个子连通图
				printf("New biconnected component: ");
				do {
					delStack(&x, &y);
					printf(" < %d,%d > ", x, y);
				} while (!((x == w)&&(y == u)));//y is the parent of x
				printf("\n");
			}
		}
		//condition two
		else if (w != v) {
			low[u] = MIN2(low[u], dfn[w]);
		}
	}
}
void bicon(int u)
{
	top_stack = -1;
	initDnfAndLow();
	bicon_(u, -1);
}
void printDfnAndLow()
{
	printf("dfn is :\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		if (dfn[i] != -1) {
			printf("%5d", dfn[i]);
		}
	}
	printf("\nlow is :\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		if (low[i] != -1) {
			printf("%5d", low[i]);
		}
	}
	putchar('\n');
}
void initDfsTree()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		dfsTree[i] = NULL;
}
void initBfsTree()
{
	for (int i = 0; i < MAX_VERTICE; i++)
		bfsTree[i] = NULL;
}
void createDfsTree_(int v)
{
	visited[v] = TRUE;
	node_pointer ptr=NULL,ptr2=NULL;
	int w;
	for (ptr = graph[v]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (!visited[w]) {
			for (ptr2 = dfsTree[v]; ptr2&&ptr2->link; ptr2 = ptr2->link);
			if (!dfsTree[v]) {
				dfsTree[v] = new_node();
				dfsTree[v]->vertex = w;
			}
			else
			{
				ptr2->link = new_node();
				ptr2->link->vertex = w;
			}
			createDfsTree_(w);
		}
	}
}
void printDfsTree(int root)
{
	node_pointer ptr=NULL;
	int w;
	printf("%5d", root);
	visited[root] = TRUE;
	for (ptr = dfsTree[root]; ptr; ptr = ptr->link)
		if (!visited[ptr->vertex])
			printDfsTree(ptr->vertex);
}
void createPrintDfsTree(int v)
{
	initDfsTree();
	initVisitArray();
	createDfsTree_(v);
	initVisitArray();
	printDfsTree(v);
	putchar('\n');
}