#pragma once
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct node *nodePointer;
struct node {
	int key;
	int count;
	nodePointer leftChild;
	nodePointer rightChild;
};
nodePointer head = NULL;
nodePointer  new_node()
{
	nodePointer temp = (nodePointer)malloc(sizeof(struct node));
	if (!temp) {
		fprintf(stderr,"The memory is full.\n");
		exit(1);
	}
	temp->leftChild = temp->rightChild = NULL;
	temp->count = 1;
	return temp;
}
nodePointer keyExist(int key)
{
	nodePointer temp = head;
	while (temp) {
		if (temp->key == key)
			return temp;
		if (temp->key > key)
			temp = temp->leftChild;
		else
			temp = temp->rightChild;
	}
	return NULL;
}
nodePointer keyExist_recursion(nodePointer node, int key)
{
	if (node) {
		if (node->key == key)
			return node;
		if (node->key > key)
			return keyExist_recursion(node->leftChild, key);
		else
			return keyExist_recursion(node->rightChild, key);
	}
	else
		return NULL;
}
nodePointer parentOfKey(int key)
{
	nodePointer temp = head;
	while (temp) {
		if (temp->rightChild) {
			if (temp->rightChild->key == key)
				return temp;
		}
		if (temp->leftChild) {
			if (temp->leftChild->key == key)
				return temp;
		}
		if (temp->key > key)
			temp = temp->leftChild;
		else
			temp = temp->rightChild;
	}
	return NULL;
}
nodePointer parentOfKey_recursion(nodePointer node,int key)
{
	if (node) {
		if (node->leftChild)
			if (node->leftChild->key == key)
				return node;
		if (node->rightChild)
			if (node->rightChild->key == key)
				return node;
		if (node->key > key)
			return parentOfKey_recursion(node->leftChild, key);
		else
			return parentOfKey_recursion(node->rightChild, key);
	}
	else
		return NULL;
}
void insertNewNode(int key)
{
	nodePointer nodeExist = keyExist(key);
	if (nodeExist) {
		nodeExist->count++;
		return;
	}
	nodePointer temp = head,preNode=NULL;
	if (head == NULL) {
		head = new_node();
		head->key = key;
		return;
	}
	while (temp) {
		preNode = temp;
		if (temp->key > key)
			temp = temp->leftChild;
		else
			temp = temp->rightChild;
	}
	temp = new_node();
	temp->key = key;
	if (preNode->key > key)
		preNode->leftChild = temp;
	else
		preNode->rightChild = temp;
}
void insertNewNode_recursion(nodePointer node, int key)
{
	if (head == NULL) {
		head = new_node();
		head->key = key;
		return;
	}
	if (node) {
		if (node->key == key) {
			node->count++;
			return;
		}
		else if(node->key > key&&node->leftChild)
			insertNewNode_recursion(node->leftChild, key);
		else if(node->key<key&&node->rightChild)
			insertNewNode_recursion(node->rightChild, key);
		else {
			nodePointer temp = new_node();
			temp->key = key;
			if (node->key > key)
				node->leftChild = temp;
			else
				node->rightChild = temp;
		}
	}
}
void removeNode(int key)
{
	nodePointer nodeExist = keyExist(key);
	if (!nodeExist) {
		printf("Tree has no node whose key is %d\n", key);
		return;
	}
	if (nodeExist->count > 1) {
		nodeExist->count--;
		return;
	}
	nodePointer parent = NULL,nodeExistCopy=nodeExist;
	if (nodeExist->leftChild) {
		nodeExist = nodeExist->leftChild;
		while (nodeExist->rightChild)
			nodeExist = nodeExist->rightChild;
		if (nodeExist == nodeExistCopy->leftChild) {
			nodeExistCopy->leftChild = nodeExist->leftChild;
			nodeExistCopy->key = nodeExist->key;
			nodeExistCopy->count = nodeExist->count;
			free(nodeExist);
		}
		else {
			parent = parentOfKey(nodeExist->key);
			if (parent)
				parent->rightChild = NULL;
			nodeExistCopy->key = nodeExist->key;
			nodeExistCopy->count = nodeExist->count;
			free(nodeExist);
		}
	}
	else if (nodeExist->rightChild) {
		nodeExist = nodeExist->rightChild;
		while (nodeExist->leftChild)
			nodeExist = nodeExist->leftChild;
		if (nodeExist == nodeExistCopy->rightChild) {
			nodeExistCopy->rightChild = nodeExist->rightChild;
			nodeExistCopy->key = nodeExist->key;
			nodeExistCopy->count = nodeExist->count;
			free(nodeExist);
		}
		else {
			parent = parentOfKey(nodeExist->key);
			if (parent)
				parent->leftChild = NULL;
			nodeExistCopy->key = nodeExist->key;
			nodeExistCopy->count = nodeExist->count;
			free(nodeExist);
		}
	}
	else {
		parent = parentOfKey(key);
		free(nodeExist);
		if (parent) {
			if (parent->key > key)
				parent->leftChild = NULL;
			else
				parent->rightChild = NULL;
		}
		else {
			head = NULL;
		}
	}
}
void printTree_(nodePointer node, int depth)
{
	if (!node)
		return;
	int i;
	for (i = 1; i <= depth; i++)
		printf("   ");
	printf("%3d\n", node->key);
	if (node->leftChild)
		printTree_(node->leftChild, depth + 1);
	else if (node->rightChild) {
		for (i = 1; i <= depth + 1; i++)
			printf("   ");
		printf(" --\n");
	}
	if (node->rightChild) {
		printTree_(node->rightChild, depth + 1);
	}
	else if (node->leftChild) {
		for (i = 1; i <= depth+1; i++)
			printf("   ");
		printf(" --\n");
	}
}
void printTree()
{
	printf("The tree is :\n");
	printTree_(head, 0);
	printf("----------------------------\n");
}