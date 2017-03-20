#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0
typedef struct node  *node_pointer;
struct node {
	int visited;
	int vertex;
	int weight;
	node_pointer next;
};
node_pointer graph[MAX_SIZE];
int parent[MAX_SIZE];
typedef struct minNode *minNode_pointer;
struct minNode {
	int vertexA;
	int vertexB;
	int weight;
	minNode_pointer next;
};
minNode_pointer minG = NULL;
minNode_pointer newMinNode()
{
	minNode_pointer temp = (minNode_pointer)malloc(sizeof(struct minNode));
	if (!temp) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	temp->next = NULL;
	return temp;
}
void insert_(node_pointer ptr, int vertex)
{
	minNode_pointer temp = NULL, newN = NULL, tempParent = NULL;
	newN = newMinNode();
	newN->vertexA = vertex;
	newN->vertexB = ptr->vertex;
	newN->weight = ptr->weight;
	if (minG == NULL) {
		minG = newN;
		return;
	}
	else {
		for (temp = minG; temp; temp = temp->next) {
			if (ptr->weight == temp->weight) {
				if (ptr->vertex == temp->vertexA&&vertex == temp->vertexB ||
					ptr->vertex == temp->vertexB&&vertex == temp->vertexA)
					return;
				else {
					newN->next = temp->next;
					temp->next = newN;
				}
			}
			else {
				if (ptr->weight < temp->weight) {
					if (tempParent == NULL) {
						newN->next = minG;
						minG = newN;
					}
					else {
						tempParent->next = newN;
						newN->next = temp;
					}
					return;
				}
			}
			tempParent = temp;
		}
		tempParent->next = newN;
	}
}
void insert()
{
	node_pointer temp = NULL;
	for (int i = 0; i < MAX_SIZE; i++)
		if (graph[i]) {
			for (temp = graph[i]; temp; temp = temp->next)
				insert_(temp, i);
		}
}
void del(minNode_pointer ptr)
{
	minNode_pointer temp = NULL, tempParent = NULL;
	for (temp = minG; temp; temp = temp->next) {
		if (temp == ptr) {
			if (!tempParent) {
				minG = minG->next;
				return;
			}
			else {
				tempParent->next = temp->next;
				return;
			}
		}
		tempParent = temp;
	}
}
void printMinG()
{
	minNode_pointer temp;
	for (temp = minG; temp; temp = temp->next) {
		printf("[ %2d %2d %2d ]", temp->vertexA, temp->vertexB, temp->weight);
	}
	putchar('\n');
}
void initGraph()
{
	for (int i = 0; i < MAX_SIZE; i++)
		graph[i] = NULL;
}
node_pointer newNode()
{
	node_pointer temp = (node_pointer)malloc(sizeof(struct node));
	if (!temp) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	temp->visited = FALSE;
	temp->next = NULL;
	return temp;
}
void createGraph()
{
	initGraph();
	int i, j, weight;
	node_pointer temp = NULL, *move = NULL;
	//printf("Enter a pair of vertex and weight-->  ");
	FILE* filePtr = NULL;
	fopen_s(&filePtr, "f:/documents/data.txt", "r");
	while (fscanf_s(filePtr, "%d%d%d", &i, &j, &weight) && i >= 0 && j >= 0 && i != j) {
		temp = newNode();
		temp->vertex = i;
		temp->weight = weight;
		for (move = &graph[j]; *move; move = &((*move)->next));
		(*move) = temp;
		temp = newNode();
		temp->vertex = j;
		temp->weight = weight;
		for (move = &graph[i]; *move; move = &((*move)->next));
		(*move) = temp;
		//printf("Enter a pair of vertex and weight-->  ");
	}
	//printf("Bye!\n");
	fclose(filePtr);
}
void printGraph()
{
	node_pointer move = NULL;
	for (int i = 0; i < MAX_SIZE; i++)
		if (graph[i]) {
			printf("V:%2d-- ", i);
			for (move = graph[i]; move; move = move->next)
				printf("¡¾V:%2d,W:%2d¡¿", move->vertex, move->weight);
			putchar('\n');
		}
}
void initParentArray()
{
	for (int i = 0; i < MAX_SIZE; i++)
		parent[i] = -1;
}
int getParent(int i)
{
	for (; parent[i] >= 0; i = parent[i]);
	return i;
}
void unit(int i, int j)//if parent[i] ==parent[j],i is the parent of j
{
	int temp;
	int iParent, jParent;
	iParent = getParent(i);
	jParent = getParent(j);
	temp = parent[iParent] + parent[jParent];
	if (parent[iParent] <= parent[jParent]) {
		parent[i] = parent[j] = iParent;
		parent[iParent] = temp;
	}
	else {
		parent[j] = parent[i] = jParent;
		parent[jParent] = temp;
	}
}
int vertexNum()
{
	int result = 0;
	for (int i = 0; i < MAX_SIZE; i++)
		if (graph[i])
			result++;
	return result;
}
void printMostClosePath()
{
	insert();
	initParentArray();
	minNode_pointer temp = NULL;
	int vertexA, vertexB, weight;
	int aParent, bParent, verNum = vertexNum();
	for (temp = minG; minG&&verNum>1; temp = temp->next) {
		vertexA = temp->vertexA;
		vertexB = temp->vertexB;
		weight = temp->weight;
		aParent = getParent(vertexA);
		bParent = getParent(vertexB);
		if (aParent == bParent&&aParent >= 0 && bParent >= 0);
		else {
			printf("[ Va:%2d,Vb:%2d,W:%2d ]\n", vertexA, vertexB, weight);
			unit(vertexA, vertexB);
			void printParentArray();
			verNum--;
		}
		del(temp);
	}
}
void printParentArray()
{
	for (int i = 0; i < MAX_SIZE; i++)
		if (parent[i] != -1) {
			printf("[ %2d,%2d ]", i, parent[i]);
		}
	putchar('\n');
}
void KrusalTest()
{
	createGraph();
	printGraph();
	printMostClosePath();
}
node_pointer getMinDisNode(int i)
{
	node_pointer temp = graph[i], minNode = NULL;
	int weight = INT_MAX;
	for (; temp; temp = temp->next) {
		if (temp->weight < weight&&temp->visited == FALSE) {
			minNode = temp;
			weight = temp->weight;
		}
	}
	return minNode;
}
void Perm()
{
	initGraph();
	createGraph();
	printGraph();
	int start;
	for (int i = 0; i < MAX_SIZE; i++)
		if (graph[i]) {
			start = i;
			break;
		}
	int nodN = vertexNum();
	int visited[MAX_SIZE];
	for (int i = 0; i< MAX_SIZE; i++)
		visited[i] = FALSE;
	visited[start] = TRUE;
	int minDis = INT_MAX, minI;
	node_pointer temp = NULL, minNode = NULL;
	while (nodN > 1) {
		minDis = INT_MAX;
		temp = NULL;
		for (int i = 0; i < MAX_SIZE; i++) {
			if (graph[i] && visited[i]) {
				temp = getMinDisNode(i);
				if (temp&& minDis > temp->weight) {
					minDis = temp->weight;
					minNode = temp;
					minI = i;
				}
			}
		}
		for (temp = graph[minNode->vertex]; temp; temp = temp->next)
			if (temp->vertex == minI) {
				temp->visited = TRUE;
				break;
			}
		visited[minNode->vertex] = TRUE;
		minNode->visited = TRUE;
		printf("[ Va:%2d,Vb:%2d,W:%2d ]\n", minI, minNode->vertex, minNode->weight);
		nodN--;
	}
}
int sideExist(int vertexA, int vertexB)
{
	node_pointer temp;
	for (temp = graph[vertexA]; temp; temp = temp->next)
		if (vertexB == temp->vertex&&temp->visited == TRUE)
			return 1;
	for (temp = graph[vertexB]; temp; temp = temp->next)
		if (vertexA == temp->vertex&&temp->visited == TRUE)
			return 1;
	return 0;
}
void Sollin()
{
	initGraph();
	createGraph();
	initParentArray();
	node_pointer temp = NULL;
	int weight = INT_MAX;
	int visited[MAX_SIZE];
	int nodN = vertexNum();
	/*for (int i = 0; i < MAX_SIZE; i++) {
	temp = NULL;
	weight = INT_MAX;
	if (graph[i]) {
	temp = getMinDisNode(i);
	if (!sideExist(i, temp->vertex)) {
	unit(i, temp->vertex);
	nodN--;
	printf("[ Va:%2d,Vb:%d,W:%2d ]\n", i, temp->vertex, temp->weight);
	}
	temp->visited = TRUE;
	}
	}*/
	for (int i = 0; i < MAX_SIZE; i++)
		if (graph[i]) {
			parent[i] = -2;
		}
	node_pointer minNode = NULL;
	int minI;
	while (nodN > 1) {
		for (int i = 0; i < MAX_SIZE; i++) {
			temp = NULL;
			weight = INT_MAX;
			if (parent[i] <= 0 && parent[i] != -1) {
				for (int j = 0; j < MAX_SIZE; j++) {
					if (getParent(j) == i) {
						temp = getMinDisNode(j);
						if (temp&&temp->weight < weight) {
							weight = temp->weight;
							minNode = temp;
							minI = j;
						}
					}
				}
				if (!sideExist(minI, minNode->vertex)) {
					unit(minI, minNode->vertex);
					nodN--;
					printf("[ Va:%2d,Vb:%d,W:%2d ]\n", minI, minNode->vertex, minNode->weight);
				}
				minNode->visited = TRUE;
			}
		}
	}
}