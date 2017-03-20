#pragma once
//十字链表是有向图的另外一种存储方式
//Orthogonal List
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 100
typedef char VertextType;
typedef char* InfoType;
typedef struct ArcBox {
	int tailvex, headvex;
	struct ArcBox *hlink, *tlink;
	InfoType *info;
}ArcBox;
typedef struct VexNode {
	VertextType data;
	ArcBox *firstin, *firstout;
}VexNode;
typedef struct {
	VexNode xlist[MAX_VERTEX_NUM];
	int vexnum, arcnum;
}OLGraph;//orthogonal List --十字链表
int Visited[MAX_VERTEX_NUM];
int LocateVex(OLGraph* graph, VertextType info) {
	for (int i = 0; i< graph->vexnum; i++)
		if (graph->xlist[i].data == info)
			return i;
	return -1;
}
void createDG(OLGraph* graph) {
	FILE* ptr;
	fopen_s(&ptr, "f:/OGdata.txt", "r");
	char ch;
	while ((ch = fgetc(ptr)) != -1)
		printf("%c", ch);
	fclose(ptr);
	fopen_s(&ptr, "f:/OGdata.txt", "r");
	//printf("Please input the vertexnum and the arcnum-- ");
	fscanf_s(ptr, "%d%d", &(graph->vexnum), &(graph->arcnum));//can get the IncInfo
	while (fgetc(ptr) != '\n');
	for (int i = 0; i < graph->vexnum; i++) {
		//printf("Input the information about this vertex  ");
		fscanf_s(ptr, "%c", &(graph->xlist[i].data), 1);
		while (fgetc(ptr) != '\n');
		graph->xlist[i].firstin = graph->xlist[i].firstout = NULL;
	}
	int m, n;
	for (int i = 0; i < graph->arcnum; i++) {
		//printf("Input the relation between two vertex  ");
		VertextType v1, v2;
		fscanf_s(ptr, "%c%c", &v1, 1, &v2, 1);
		m = LocateVex(graph, v1);
		n = LocateVex(graph, v2);
		ArcBox* p = (ArcBox*)malloc(sizeof(ArcBox));
		p->headvex = n;
		p->tailvex = m;
		p->hlink = graph->xlist[n].firstin;
		p->tlink = graph->xlist[m].firstout;
		p->info = NULL;
		graph->xlist[n].firstin = graph->xlist[m].firstout = p;//完成在入弧和出弧链头的插入
															   //if(IncInfo) Input(p->info);
		while ((fgetc(ptr) != '\n'));
	}
	fclose(ptr);
}
void printGraph_L_L(OLGraph* graph) {
	printf("--------------------\n");
	for (int i = 0; i < graph->vexnum; i++) {
		printf("Vertex: %c- ", graph->xlist[i].data);
		ArcBox* move = graph->xlist[i].firstout;
		while (move) {
			printf(" [ %d,%d ] ", move->tailvex, move->headvex);
			move = move->tlink;
		}
		printf("\n");
	}
	printf("--------------------\n");
}
void printGraph_R_L_L(OLGraph* graph) {
	printf("--------------------\n");
	for (int i = 0; i < graph->vexnum; i++) {
		printf("Vertex: %c- ", graph->xlist[i].data);
		ArcBox* move = graph->xlist[i].firstin;//弧头
		while (move) {
			printf(" [ %d,%d ] ", move->tailvex, move->headvex);
			move = move->hlink;
		}
		printf("\n");
	}
	printf("--------------------\n");
}
void printID(OLGraph* graph) {
	int count;
	for (int i = 0; i < graph->vexnum; i++) {
		count = 0;
		printf("Vertex: %c- ", graph->xlist[i].data);
		ArcBox* move = graph->xlist[i].firstin;//弧头
		while (move) {
			//printf(" [ %d,%d ] ", move->headvex, move->tailvex);
			count++;
			move = move->hlink;
		}
		printf(" DL: %d\n", count);
	}
}
void printOD(OLGraph* graph) {
	int count;
	for (int i = 0; i < graph->vexnum; i++) {
		count = 0;
		printf("Vertex: %c- ", graph->xlist[i].data);
		ArcBox* move = graph->xlist[i].firstout;//弧尾
		while (move) {
			//printf(" [ %d,%d ] ", move->headvex, move->tailvex);
			count++;
			move = move->tlink;
		}
		printf(" OL: %d\n", count);
	}
}
int FirstOLVex(OLGraph* graph, int v) {
	ArcBox* move = graph->xlist[v].firstout;
	if (move)
		return move->headvex;
	else
		return -1;
}
int NextOLVex(OLGraph* graph, int v,int w) {
	ArcBox* move = graph->xlist[v].firstout;
	while (move) {
		if (move->headvex == w)
			break;
		move = move->tlink;
	}
	if (move) {
		move = move->tlink;
		if (move)
			return move->headvex;
	}
	return -1;
}
void DFS(OLGraph* graph,int v) {
	if (!Visited[v])
		Visited[v] = TRUE;
	printf("%3c", graph->xlist[v].data);
	ArcBox* move = graph->xlist[v].firstout;
	int w;
	for (w = FirstOLVex(graph, v); w >= 0; w = NextOLVex(graph, v, w)) {
		if (!Visited[w])
			DFS(graph, w);
	}
}
void DFSTraverse(OLGraph* graph) {
	for (int v = 0; v < graph->vexnum; v++)
		Visited[v] = FALSE;
	for (int v = 0; v < graph->vexnum; v++)
		if (!Visited[v])
			DFS(graph, v);
}
void test() {
	OLGraph graph;
	createDG(&graph);
	printGraph_L_L(&graph);
	printGraph_R_L_L(&graph);
	printID(&graph);
	printOD(&graph);
	DFSTraverse(&graph);
}
/*OLdata.txt
4 7
a
b
c
d
ab
ac
ca
cd
da
db
dc
*/
