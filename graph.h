#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
typedef struct matrixNode {
	int x;
	int y;
	int value;
};
struct {
	struct matrixNode matrix[MAX];
	int item;
}matrix;
struct graphNode {
	int tag;
	int parent[MAX];
	int children[MAX];
	int parentAmount;
	int childrenAmount;
};
struct graphNode graph[MAX];
int indexArray[MAX];
typedef struct node *link;
struct node {
	int key;
	link next;
};
struct {
	struct node nodes[MAX];
	int amount;
}links;
struct {
	struct node nodes[MAX];
	int amount;
}reverseLinks;
link new_node()
{
	link temp = (link)malloc(sizeof(struct node));
	if (!temp) {
		printf("The memory is full.\n");
		exit(1);
	}
	temp->next = NULL;
	return temp;
}
void initlinks()
{
	links.amount = 0;
	for (int i = 0; i < MAX; i++)
		links.nodes[i].next = NULL;
}
void initReverseLinks()
{
	reverseLinks.amount = 0;
	for (int i = 0; i < MAX; i++)
		reverseLinks.nodes[i].next = NULL;
}
void initGraph()
{
	for (int i = 0; i < MAX; i++) {
		graph[i].childrenAmount = 0;
		graph[i].parentAmount = 0;
		graph[i].tag = FALSE;
	}
}
void unionGraph(int i, int j)//i is parent and j is child
{
	graph[i].children[graph[i].childrenAmount++] = j;
	graph[j].parent[graph[j].parentAmount++] = i;
	if (graph[i].tag == FALSE)
		graph[i].tag = TRUE;
	if (graph[j].tag == FALSE)
		graph[j].tag = TRUE;
}
void createGraph()
{
	initGraph();
	int i = 1, j = 1;
	while (i >= 0 && j >= 0) {
		printf("Input a pair of number( -1 -1 to quit)--->");
		scanf_s("%d%d", &i, &j);
		while ((i == j&&i >= 0 && j >= 0)||i>=MAX||j>=MAX) {
			printf("Illegal datas,input again.--->");
			scanf_s("%d%d", &i, &j);
		}
		unionGraph(i, j);
	}
}

int maxNode()
{
	for (int i = MAX - 1; i >= 0; i--)
		if (graph[i].tag == TRUE)
			return i;
	return -1;
}
int nodeAmount()
{
	int result = 0;
	int maxNo = maxNode();
	for (int i = 0; i <= maxNo; i++)
		if (graph[i].tag == TRUE)
			result++;
	return result;
}
void printGraph()
{
	printf("There are %d node.\n",nodeAmount());
	for (int i = 0; i < MAX; i++)
		if (graph[i].tag == TRUE) {
			printf("---------------------------\n");
			printf("---(  %d  )\n", i);
			printf("Parent: ");
			for (int j = 0; j < graph[i].parentAmount; j++)
				printf("%4d", graph[i].parent[j]);
			putchar('\n');
			printf("Child: ");
			for (int k = 0; k < graph[i].childrenAmount; k++)
				printf("%4d", graph[i].children[k]);
			putchar('\n');
			printf("---------------------------\n");
		}
	putchar('\n');
}
void initMatrix()
{
	for (int i = 0; i < MAX; i++)
		matrix.matrix[i].value = FALSE;
	matrix.item = 0;
}
int childIhasParentJ(int childI, int parentJ)
{
	for (int i = 0; i < graph[childI].parentAmount; i++)
		if (graph[childI].parent[i] == parentJ)
			return 1;
	return 0;
}
void printGraphMatrix()
{
	int n = 0;
	printf("-------------------------------\n");
	for (int i = 0; i <= maxNode(); i++) {
		for (int j = 0; j <= maxNode(); j++)
			if (childIhasParentJ(i, j))
				printf("  1");
			else
				printf("  0");
		putchar('\n');
	}
	printf("-------------------------------\n");
}
void createLink()
{
	initlinks();
	link temp=NULL,trail=NULL;
	for (int i = 0; i <= maxNode(); i++) {
		if (graph[i].tag == TRUE) {
			links.nodes[links.amount].key = i;
			trail = &links.nodes[links.amount++];
			for (int j = 0; j < graph[i].parentAmount; j++) {
				temp = new_node();
				temp->key = graph[i].parent[j];
				trail->next = temp;
				trail = trail->next;
			}
		}
	}
}
void printLink()
{
	printf("--------------------------\n");
	for (int i = 0; i <links.amount; i++) {
		printf("%5d-->Parents:  ", links.nodes[i].key);
		for (link temp = links.nodes[i].next; temp; temp = temp->next)
			if(temp)
				printf("%5d", temp->key);
		putchar('\n');
	}
	printf("--------------------------\n");
}
void createReverseLink()
{
	initReverseLinks();
	link temp = NULL, trail = NULL;
	int maxNo = maxNode();
	for (int i = 0; i <= maxNo; i++) {
		if (graph[i].tag == TRUE) {
			reverseLinks.nodes[reverseLinks.amount].key = i;
			trail = &reverseLinks.nodes[reverseLinks.amount++];
			for (int j = 0; j < graph[i].childrenAmount; j++) {
				temp = new_node();
				temp->key = graph[i].children[j];
				trail->next = temp;
				trail = trail->next;
			}
		}
	}
}
void printReverseLink()
{
	printf("--------------------------\n");
	for (int i = 0; i <reverseLinks.amount; i++) {
		printf("%5d-->Children:  ", reverseLinks.nodes[i].key);
		for (link temp = reverseLinks.nodes[i].next; temp; temp = temp->next)
			if (temp)
				printf("%5d", temp->key);
		putchar('\n');
	}
	printf("--------------------------\n");
}
void createIndexArray()
{
	int num = nodeAmount();
	int maxNo = maxNode();
	int indexNL = 0,indexNR=num+1;
	link move=NULL;
	for (int i = 0; i <= maxNo; i++) {
		if (graph[i].tag == TRUE) {
			indexArray[i] = indexNR;
			for (int j = 0; j < graph[i].parentAmount; j++) {
				indexArray[indexNR++] = graph[i].parent[j];
			}
		}
	}
	indexArray[num] = indexNR + graph[maxNo].parentAmount;
	for (int i = 0; i < indexArray[num]; i++) {
		printf("[%2d]¡¾%2d¡¿ ",i, indexArray[i]);
		if ((i + 1) % 5 == 0)
			putchar('\n');
	}
}
/*
#define MAX 100
typedef struct node* node_pointer;
struct node {
int vertex;
node_pointer link;
};
node_pointer new_node() {
node_pointer temp = (node_pointer)malloc(sizeof(struct node));
if (temp) {
temp->link = NULL;
return temp;
}
return NULL;
}
node_pointer graph[MAX];
void initGraph(node_pointer graph[]) {
for (int i = 0; i < MAX; i++)
graph[i] = NULL;
}
void collectData(node_pointer graph[]) {
initGraph(graph);
int i=0, j=0;
while (1) {
printf("Input a pair of data  -|");
scanf_s("%d%d", &i, &j);
if (i < 0 || j < 0)
break;
if (graph[i] == NULL) {
graph[i] = new_node();
graph[i]->vertex = j;
}
else{
node_pointer* move = &graph[i];
for (; (*move)->link; *move = (*move)->link);
(*move)->link = new_node();
(*move)->link->vertex = j;
}
if (graph[j] == NULL) {
graph[j] = new_node();
graph[j]->vertex = i;
}
else {
node_pointer* move = &graph[j];
for (; (*move)->link; *move = (*move)->link);
(*move)->link = new_node();
(*move)->link->vertex = i;
}
}
}
void printGraph(node_pointer graph[]) {
for (int i = 0; i < MAX; i++) {
if (graph[i] != NULL) {
node_pointer move = graph[i];
printf("%5d - -", i);
while (move) {
printf("%5d", move->vertex);
move = move->link;
}
putchar('\n');
}
}
}
//if the number is 5 to create the table
int lineSum(node_pointer graph[]) {
int result = 0;
for (int i = 0; i < MAX;i++)
if (graph[i]) {
node_pointer move = graph[i];
while (move) {
result++;
move = move->link;
}
}
return result;
}
*/