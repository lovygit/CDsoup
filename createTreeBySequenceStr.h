#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
#define TOKEN_LEN 4
char strPre[MAX][TOKEN_LEN] = { "A","B","C" };
char strMid[MAX][TOKEN_LEN] = { "B","A","C" };
char strBack[MAX][TOKEN_LEN];// = { "D","E","B","F","G","C","A" };
typedef struct node *link;
struct node{
	char key[TOKEN_LEN];
	link leftChild;
	link rightChild;
};
link head = NULL;
link new_node()
{
	link temp = (link)malloc(sizeof(struct node));
	if (!temp) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	temp->leftChild = temp->rightChild = NULL;
	return temp;
}
void init()
{
	head = new_node();
}
void createTreeBySequence_Pre_Mid(link node,char strPre[][TOKEN_LEN], char strMid[][TOKEN_LEN],int startInPre,int endInPre,int startInMid,int endInMid)
{
	char* charStart = strPre[startInPre];
	int limiter=startInMid;
	for (int i = startInMid; i <= endInMid; i++)
		/*if (strMid[i] != charStart)
			limiter++;*/
		if (strcmp(charStart, strMid[i]))
			limiter++;
		else
			break;
	/*printf("startInPre is %d || endInPre is %d || startInMid is %d ||endInMid is %d limiter is %d||\n", startInPre, endInPre,startInMid,endInMid,limiter);
	printf("(*node) is null?  %d\n", (*node)== NULL);*/
	//node->key = charStart;
	strcpy_s(node->key, TOKEN_LEN, strMid[limiter]);
	if (limiter ==startInMid) {//start-1 is the former recycle--start
		node->leftChild = NULL;
	}
	else {
		node->leftChild = new_node();
		createTreeBySequence_Pre_Mid(node->leftChild, strPre, strMid, startInPre+1, startInPre+limiter-startInMid,startInMid,limiter-1);
	}
	if (limiter == endInMid) {
		node->rightChild = NULL;
	}
	else {
		node->rightChild = new_node();
		createTreeBySequence_Pre_Mid(node->rightChild, strPre,strMid, startInPre + limiter - startInMid+1,endInPre,limiter+1,endInMid);
	}
}
void createTreeBySequence_Mid_Back(link node, char strMid[][TOKEN_LEN], char strBack[][TOKEN_LEN], int startInMid, int endInMid, int startInBack, int endInBack)
{
	char* charEnd = strBack[endInBack];
	int limiter = startInMid;
	for (int i = startInMid; i < endInMid; i++)
		/*if (strMid[i] != charEnd)
			limiter++;*/
		if (strcmp(charEnd, strMid[i]))
			limiter++;
		else
			break;
	//node->key = charEnd;
	strcpy_s(node->key,TOKEN_LEN, strMid[limiter]);
	if (limiter == startInMid) {
		(node)->leftChild = NULL;
	}
	else {
		node->leftChild = new_node();
		createTreeBySequence_Mid_Back(node->leftChild, strMid, strBack, startInMid, limiter - 1, startInBack, limiter-startInMid+startInBack-1);
	}
	if (limiter == endInMid) {
		node->rightChild = NULL;
	}
	else {
		node->rightChild = new_node();
		createTreeBySequence_Mid_Back(node->rightChild, strMid, strBack, limiter + 1, endInMid, limiter - startInMid + startInBack - 1+1,endInBack - 1);
	}
}
int strlenStrArray(char strArray[][TOKEN_LEN])
{
	int result = 0;
	while (strcmp(strArray[result], "") != 0)
		result++;
	return result;
}
void createTree_Pre_Mid()
{
	init();
	createTreeBySequence_Pre_Mid(head, strPre, strMid, 0, strlenStrArray(strPre) - 1, 0, strlenStrArray(strMid) - 1);
}
void createTree_Mid_Back()
{
	init();
	createTreeBySequence_Mid_Back(head, strMid, strBack, 0, strlenStrArray(strMid) - 1, 0, strlenStrArray(strBack) - 1);
}
void printTree_(link node, int depth)
{
	if (node) {
		for (int i = 0; i < depth; i++)
			printf("   ");
		printf("%3s\n", node->key);
		if (node->leftChild)
			printTree_(node->leftChild, depth + 1);
		else if (node->rightChild) {
			for (int i = 0; i < depth + 1;i++)
				printf("   ");
			printf(" --\n");
		}
		if (node->rightChild)
			printTree_(node->rightChild, depth + 1);
		else if (node->leftChild) {
			for (int i = 0; i < depth + 1; i++)
				printf("   ");
			printf(" --\n");
		}
	}
}
void printTree()
{
	printf("The tree is:\n");
	printf("--------------------------\n");
	printTree_(head, 0);
	printf("--------------------------\n");
}
//void UI()
//{
//	printf("Please enter the preStr and the MidStr.\n");
//	printf("The strPre is--->");
//	scanf_s("%s", strPre, MAX);
//	printf("The strMid is--->");
//	scanf_s("%s", strMid, MAX);
//	createTree();
//	printTree();
//}