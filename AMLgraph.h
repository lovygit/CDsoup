#pragma once
//Adjacency Mltilist
#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 100
#define TRUE 1
#define FALSE 0
typedef char* InfoType;
typedef char VertexType;
typedef enum { unvisited, visited }VisitIf;
typedef struct EBox {
	VisitIf mark;
	int ivex, jvex;
	struct EBox *ilink, *jlink;
	InfoType* info;
}EBox;
typedef struct VexBox {
	VertexType data;
	EBox* firstedge;
}VexBox;
typedef struct {
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum, edgenum;
}AMLGraph;
int LocateVextex(AMLGraph* graph, VertexType data) {
	for (int i = 0; i < graph->vexnum; i++)
		if (graph->adjmulist[i].data == data)
			return i;
	return -1;
}
void createAMLGraph(AMLGraph* graph) {
	FILE* ptr;
	fopen_s(&ptr, "f:/AMLdata.txt", "r");
	char ch;
	while ((ch = fgetc(ptr)) != -1)
		printf("%c", ch);
	fclose(ptr);

	fopen_s(&ptr, "f:/AMLdata.txt", "r");
	//printf("Input graph's vexnum and edgenum-- ");
	fscanf_s(ptr, "%d%d", &(graph->vexnum), &(graph->edgenum));
	while (fgetc(ptr) != '\n');
	for (int i = 0; i < graph->vexnum; i++) {
		//printf("Input the vextex's data  ");
		fscanf_s(ptr, "%c", &(graph->adjmulist[i].data), 1);
		while (fgetc(ptr) != '\n');
		graph->adjmulist[i].firstedge = NULL;
	}
	int m, n;
	VertexType v1, v2;
	for (int i = 0; i < graph->edgenum; i++) {
		///printf("Input the relation about two Vextex  ");
		fscanf_s(ptr, "%c%c", &v1, 1, &v2, 1);
		while (fgetc(ptr) != '\n');
		EBox* p = (EBox*)malloc(sizeof(EBox));
		m = LocateVextex(graph, v1);
		n = LocateVextex(graph, v2);
		p->mark = 0;
		p->ivex = m;
		p->jvex = n;
		p->ilink = graph->adjmulist[m].firstedge;
		p->jlink = graph->adjmulist[n].firstedge;
		p->info = NULL;
		graph->adjmulist[m].firstedge = graph->adjmulist[n].firstedge = p;
	}
	fclose(ptr);
}
void printAMLGraph(AMLGraph* graph) {
	for (int i = 0; i < graph->vexnum; i++) {
		printf("Vectex %c", graph->adjmulist[i].data);
		EBox* move = graph->adjmulist[i].firstedge;
		while (move) {
			printf("[ %d,%d ]", move->ivex, move->jvex);
			if (move->ivex == i)
				move = move->ilink;
			else if (move->jvex == i)
				move = move->jlink;
			else
				break;
		}
		printf("\n");
	}
}

typedef struct CSNode {
	VertexType data;
	struct CSNode *lchild, *nextsibling;
}CSNode,*CSTree;
int Visited[MAX_VERTEX_NUM];
int FirstAdjVex(AMLGraph* graph, int index) {
	EBox* move = graph->adjmulist[index].firstedge;
	if (move) {
		return move->ivex == index ? move->jvex : move->ivex;
	}
	return -1;
}
int NextAdjVex(AMLGraph* graph, int v, int w) {
	EBox* move = graph->adjmulist[v].firstedge;
	while (move) {
		if (move->ivex == w || move->jvex == w)
			break;
		if (move->ivex == v)
			move = move->ilink;
		else
			move = move->jlink;
	}
	if (move) {
		if (move->ivex == v)
			move = move->ilink;
		else
			move = move->jlink;
		if (move) {
			return move->ivex == v ? move->jvex : move->ivex;
		}
	}
	return -1;
}
VertexType GetVex(AMLGraph* graph, int w) {
	return graph->adjmulist[w].data;
}
void DFSTree(AMLGraph * graph, int v, CSTree* T) {
	Visited[v] = TRUE;
	int first = TRUE;
	int w;
	CSTree p, q = NULL;
	for (w = FirstAdjVex(graph, v); w >= 0; w = NextAdjVex(graph, v, w)) {
		if (!Visited[w]) {
			p = (CSTree)malloc(sizeof(CSNode));
			p->data = GetVex(graph, w);
			p->lchild = p->nextsibling = NULL;
			if (first) {
				first = FALSE;
				(*T)->lchild = p;
			}
			else {
				q->nextsibling = p;
			}
			q = p;
			DFSTree(graph, w, &p);//此时q和p可以互换,因为（*T)->lchild=p语句只改变指针所指向的内容，不改变指针本身
		}
	}
}
void DFSTree_(AMLGraph* graph, CSTree* root) {
	*root =(CSTree) malloc(sizeof(CSNode));
	(*root)->data = graph->adjmulist[0].data;
	(*root)->lchild = (*root)->nextsibling = NULL;
	DFSTree(graph, 0, root);
}
void DFSForest(AMLGraph* graph, CSTree* T) {
	*T = NULL;
	int v;
	CSTree q=NULL;//q起到了“滑动”的作用
	for (v = 0; v < graph->vexnum; v++) {
		Visited[v] = FALSE;
	}
	for (v = 0; v < graph->vexnum; v++) {//第v顶点为新的生成树的根节点
		if (!Visited[v]) {
			CSTree p =(CSTree) malloc(sizeof(CSNode));//分配根节点
			p->data = GetVex(graph, v);//赋值
			p->lchild = p->nextsibling = NULL;
			if (!*T)//第一颗生成树的根（T的根）
				(*T) = p;
			else
				q->nextsibling = p;//此时p是其他生成树的根，并且通过q让新生成的树的根为前面树的nextsibing数据域
			q = p;
			DFSTree(graph, v, &p);//p为新的数的根--》p与q不能互换
		}
	}
}
void printTree(CSTree root,int depth) {
	if (root) {
		for (int i = 0; i < depth; i++)
			printf("  ");
		printf("%2c\n", root->data);
		if (root->lchild)
			printTree(root->lchild, depth + 1);
		else if (root->nextsibling) {
			for (int i = 0; i < depth + 1; i++)
				printf("  ");
			printf("--\n");
		}
		if (root->nextsibling)
			printTree(root->nextsibling, depth + 1);
		else if (root->lchild) {
			for (int i = 0; i < depth + 1; i++)
				printf("  ");
			printf("--\n");
		}
	}
}
void test() {
	AMLGraph graph;
	createAMLGraph(&graph);
	printAMLGraph(&graph);
	CSTree root=NULL;
	DFSTree_(&graph, &root);
	printTree(root,0);
	DFSForest(&graph, &root);
	printTree(root, 0);
}
/*AMLdata.txt
5 6
a
b
c
d
e
ab
ad
bc
be
cd
ce
*/
