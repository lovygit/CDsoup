#pragma once
#include<stdio.h>
#include<stdlib.h>
#define QUEUE_CAPACITY 100
#define TRUE 1
#define FALSE 0
typedef  struct node  *nodePointer;
struct node {
	int key;
	nodePointer leftChild;
	nodePointer rightChild;
};
nodePointer head=NULL;
nodePointer queue[QUEUE_CAPACITY];
int top = -1;
int size = 0;
void initQueue()
{
	top = -1;
	size = 0;
}
nodePointer delQueue()
{
	if (top>=size)
		return NULL;
	return queue[++top];
}
void addQueue(nodePointer node)
{
	if (size >= QUEUE_CAPACITY)
		return;
	queue[size++] = node;
}
nodePointer new_node()
{
	nodePointer pointer = (nodePointer)malloc(sizeof(struct node));
	if (!pointer) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	pointer->leftChild = pointer->rightChild = NULL;
	return pointer;
}
nodePointer searchKey(nodePointer root,int key)
{
	if (root->key == key)
		return root;
	else if (root->key < key)
		return searchKey(root->rightChild, key);
	else if (root->key > key)
		return searchKey(root->leftChild, key);
	else {
		printf("The key struction is wrong.\n");
		return NULL;
	}
}
nodePointer searchKey_2(int key)
{
	nodePointer temp= head;
	while (temp) {
		if (temp->key == key)
			return temp;
		if (temp->key < key)
			temp = temp->rightChild;
		else
			temp = temp->leftChild;
	}
	return NULL;
}
nodePointer modifiedSearch(int key)
{
	nodePointer temp = head;
	nodePointer pre = head;
	while (temp) {
		pre = temp;
		if (temp->key == key)
			return NULL;
		if (temp->key > key)
			temp = temp->leftChild;
		else
			temp = temp->rightChild;
	}
	return pre;
}
void insertNode(nodePointer item)
{
	nodePointer temp = modifiedSearch(item->key);
	if (temp == NULL&&head!=NULL) {
		printf("The key has been saved.\n");
		return;
	}
	else if (head == NULL) {
		nodePointer newNode = new_node();
		newNode->key = item->key;
		head = newNode;
		return;
	}
	else {
		nodePointer newNode = new_node();
		newNode->key = item->key;
		if (temp->key > item->key)
			temp->leftChild = newNode;
		else
			temp->rightChild = newNode;
	}
}
nodePointer keyExist(int key)
{
	nodePointer temp = head;
	nodePointer tempCopy = NULL;
	while (TRUE) {
		if (temp == tempCopy)break;
		tempCopy = temp;
		if (temp->key == key)
			return temp;
		if (temp->key > key&&temp->leftChild)
			temp = temp->leftChild;
		else if(temp->key<key&&temp->rightChild)
			temp = temp->rightChild;
	}
	return NULL;
}
nodePointer parentOfKeyExist(int key)
{
	nodePointer temp = head;
	nodePointer tempPre = NULL;
	if (head&&head->key == key || !head)
		return NULL;
	while (TRUE) {
		if (tempPre == temp)break;
		tempPre = temp;
		if (temp->leftChild) {
			if (temp->leftChild->key == key)
				return temp;
		}

		if (temp->rightChild) {
			if (temp->rightChild->key == key)
				return temp;
		}

		if (temp->key > key&&temp->leftChild)
			temp = temp->leftChild;
		else if(temp->key<key&&temp->rightChild)
			temp = temp->rightChild;
		//printf("//temp->key is %5d.\n", temp->key);
	}
	return NULL;
}
void delOneElement(int key) {//´íÎó
	nodePointer temp = keyExist(key);
	nodePointer tempCopy = temp;
	nodePointer parent = NULL;
	if (temp == NULL) {
		printf("There is no this key.\n");
		return;
	}
	if (temp->leftChild) {
		//printf("//part one.\n");
		temp = temp->leftChild;
		while (temp->rightChild)
			temp = temp->rightChild;
		if (temp == tempCopy->leftChild) {
			//printf("//part two.\n");
			tempCopy->leftChild = temp->leftChild;
			tempCopy->key = temp->key;
			free(temp);
		}
		else {
			//printf("//part three.\n");
			parent = parentOfKeyExist(temp->key);
			if (parent) {
				//printf("//parent's key is %5d\n", parent->key);
				parent->rightChild = temp->leftChild;
			}
			tempCopy->key = temp->key;
			free(temp);
		}
	}
	else if (temp->rightChild) {
		//printf("//part four.\n");
		temp = temp->rightChild;
		while (temp->leftChild)
			temp = temp->leftChild;
		if (temp == tempCopy->rightChild) {
			//printf("//part five.\n");
			tempCopy->rightChild = temp->rightChild;
			tempCopy->key = temp->key;
			free(temp);
		}
		else {
			//printf("//part six.\n");
			parent = parentOfKeyExist(temp->key);
			if (parent) {
				//printf("//parent's key is %5d\n", parent->key);
				parent->leftChild = NULL;
			}
			tempCopy->key = temp->key;
			free(temp);
		}
	}
	else {
		//printf("//part seven.\n");
		parent = parentOfKeyExist(key);
		if (parent) {
			if (parent->leftChild == temp) {
				//printf("//part eight.\n");
				parent->leftChild = NULL;
				free(temp);
			}
			else {
				//printf("//part nine.\n");
				parent->rightChild = NULL;
				free(temp);
			}
		}
		else {
			//printf("//part ten.\n");
			free(head);
			head = NULL;
		}
	}
}
int printLineBreak(int n)
{
	n += 2;
	while (n >= 2) {
		if (n % 2 != 0)
			return 0;
		n /= 2;
	}
	return 1;
}
void printNode()
{
	nodePointer temp = head;
	addQueue(temp);
	int n = 0;
	while (temp) {
		temp = delQueue();
		if (!temp)break;
		printf("%5d", temp->key);
		if (printLineBreak(n++))
			putchar('\n');
		if (temp->leftChild)
			addQueue(temp->leftChild);
		if (temp->rightChild)
			addQueue(temp->rightChild);
	}
	printf("\n-------------------\n");
}
void printNodeWithLevel_(nodePointer pointer,int depth)
{
	if (pointer == NULL)
		return;
	int i;
	for (i = 1; i <= depth; i++)
		printf("    ");
	printf("%3d\n", pointer->key);
	if (pointer->leftChild)
		printNodeWithLevel_(pointer->leftChild, depth + 1);
	else if (pointer->rightChild) {
		for (i = 1; i <= depth+1; i++)
			printf("    ");
		printf(" --\n");
	}
	if (pointer->rightChild)
		printNodeWithLevel_(pointer->rightChild, depth + 1);
	else if (pointer->leftChild) {
		for (i = 1; i <= depth+1; i++)
			printf("    ");
		printf(" --\n");
	}
}
void printNodeWithLevel(nodePointer node)
{
	printNodeWithLevel_(node, 0);
	printf("-------------------------------\n");
}