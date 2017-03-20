#pragma once
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define QUEUE_CAPACITY 100
typedef struct node *node_link;
struct node{
	int priority;
	node_link leftChild;
	node_link rightChild;
	node_link parent;
};
node_link head = NULL;
int nodeAmount = 0;
node_link queue[QUEUE_CAPACITY];
int top = 0;
int size = -1;
void queueInit()
{
	top = 0;
	size = -1;
}
node_link delQueue()
{
	if (top >size) {
		return NULL;
	}
	return queue[top++];
}
void addQueue(node_link link)
{
	if (size >= QUEUE_CAPACITY) {
		fprintf(stderr, "The queue is full.\n");
		return;
	}
	queue[++size] = link;
}

node_link new_node()
{
	node_link temp = (node_link)malloc(sizeof(struct node));
	if (!temp) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	temp->rightChild = temp->leftChild =temp->parent= NULL;
	return temp;
}
int leftLeafNode(node_link node)
{
	if (node->leftChild == NULL)
		return 1;
	return 0;
}
int rightLeafNode(node_link node)
{
	if (node->rightChild == NULL)
		return 1;
	return 0;
}
int leafNode(node_link node)
{
	if (leftLeafNode(node) && rightLeafNode(node))
		return 1;
	return 0;
}
node_link getFirstLeafNode()
{
	queueInit();
	node_link temp;
	addQueue(head);
	while (TRUE) {
		temp = delQueue();
		if (!temp)
			return NULL;
		if (temp->leftChild==NULL|| temp->rightChild==NULL)
			return temp;
		addQueue(temp->leftChild);
		addQueue(temp->rightChild);
	}
}
node_link getMostLeftNode()
{
	node_link temp = head;
	while (temp)
		temp = temp->leftChild;
	return temp;
}
void insertTreeHeap(int priority)
{
	nodeAmount++;
	if (head == NULL) {
		head = new_node();
		head->priority = priority;
		return;
	}
	else {
		node_link temp = new_node();
		temp->priority = priority;
		if (getFirstLeafNode() == NULL) {
			node_link mostLeft = getMostLeftNode();
			mostLeft->leftChild = temp;
			temp->parent = mostLeft;
		}
		else {
			node_link firstLeaf = getFirstLeafNode();
			if (leftLeafNode(firstLeaf)) {
				firstLeaf->leftChild = temp;
				temp->parent = firstLeaf;
			}
			else {
				firstLeaf->rightChild = temp;
				temp->parent = firstLeaf;
			}
		}
		while (temp!=head) {
			int priority;
			if (temp->priority > temp->parent->priority) {
				priority = temp->priority;
				temp->priority = temp->parent->priority;
				temp->parent->priority = priority;
				temp = temp->parent;
			}
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
void printTreeHeap()
{
	queueInit();
	node_link temp;
	addQueue(head);
	int i = 0;
	while (TRUE) {
		temp = delQueue();
		if (!temp)
			break;
		printf("%5d", temp->priority);
		if (printLineBreak(i))
			putchar('\n');
		if (temp->leftChild)
			addQueue(temp->leftChild);
		if (temp->rightChild)
			addQueue(temp->rightChild);
		i++;
	}
	printf("\n----------------------\n");
}
node_link getTheNode(int position)
{
	queueInit();
	addQueue(head);
	node_link temp;
	if (head == NULL || position == 0)
		return head;
	int j = 0;
	while (j<position) {
		temp = delQueue();
		if (!temp) {
			printf("There is no this element.\n");
			return NULL;
		}
		if (temp->leftChild)
			addQueue(temp->leftChild);
		if (temp->rightChild)
			addQueue(temp->rightChild);
		j++;
	}
	temp = delQueue();
	if (!temp) {
		printf("There is no this element.\n");
		return NULL;
	}
	return temp;
}
int getNodeNumber_(node_link link)
{
	if (link)
		return 1 + getNodeNumber_(link->leftChild) + getNodeNumber_(link->rightChild);
	else
		return 0;
}
int getNodeNumber()
{
	return getNodeNumber_(head);
}
void setOneElementPriority(int position)
{
	if (head == NULL) {
		printf("The heap is empty.\n");
		return;
	}
	else if (position >= nodeAmount) {
		printf("There is not this node.\n");
		return;
	}
	int highestPriority = head->priority+1;
	int temp;
	node_link setNode = getTheNode(position);
	node_link setNodeCopy = NULL;
	setNode->priority = highestPriority;
	if (setNode == head)
		return;
	while (setNode!=setNodeCopy&&setNode!=head) {
		setNodeCopy = setNode;
		if (setNode->priority > setNode->parent->priority) {
			temp = setNode->priority;
			setNode->priority = setNode->parent->priority;
			setNode->parent->priority = temp;
			setNode = setNode->parent;
		}
		if (setNode->rightChild&&setNode->rightChild) {
			if (setNode->rightChild->priority > setNode->priority&&setNode->leftChild->priority > setNode->priority) {
				if (setNode->rightChild->priority >=setNode->leftChild->priority) {
					temp = setNode->priority;
					setNode->priority = setNode->rightChild->priority;
					setNode->rightChild->priority = temp;
					setNode = setNode->rightChild;
				}
				else {
					temp = setNode->priority;
					setNode->priority = setNode->leftChild->priority;
					setNode->leftChild->priority = temp;
					setNode = setNode->leftChild;
				}
			}
			else if (setNode->rightChild->priority > setNode->priority) {
				temp = setNode->priority;
				setNode->priority = setNode->rightChild->priority;
				setNode->rightChild->priority = temp;
				setNode = setNode->rightChild;
			}
			else if (setNode->leftChild->priority > setNode->priority) {
				temp = setNode->priority;
				setNode->priority = setNode->leftChild->priority;
				setNode->leftChild->priority = temp;
				setNode = setNode->leftChild;
			}
		}
		else if(setNode->leftChild){
			if (setNode->leftChild->priority > setNode->priority) {
				temp = setNode->priority;
				setNode->priority = setNode->leftChild->priority;
				setNode->leftChild->priority = temp;
				setNode = setNode->leftChild;
			}
		}
		else if (setNode->rightChild) {
			if (setNode->rightChild->priority > setNode->priority) {
				temp = setNode->priority;
				setNode->priority = setNode->rightChild->priority;
				setNode->rightChild->priority = temp;
				setNode = setNode->rightChild;
			}
		}
	}
}
void deleteFromHeap()
{
	if (nodeAmount == 0) {
		fprintf(stderr, "There is no any node.\n");
		return;
	}
	node_link temp = getTheNode(--nodeAmount);
	node_link tempCopy = NULL;
	if (temp->parent) {
		if (temp->parent->leftChild == temp)
			temp->parent->leftChild = NULL;
		else
			temp->parent->rightChild = NULL;
	}
	head->priority = temp->priority;
	free(temp);
	temp = head;
	int priority;
	while (temp!=tempCopy) {
		tempCopy = temp;
		if (temp->leftChild&&temp->rightChild) {
			if (temp->leftChild->priority > temp->priority&&temp->rightChild->priority > temp->priority) {
				if (temp->leftChild->priority >= temp->rightChild->priority) {
					priority = temp->priority;
					temp->priority = temp->leftChild->priority;
					temp->leftChild->priority = priority;
					temp = temp->leftChild;
				}
				else {
					priority = temp->priority;
					temp->priority = temp->rightChild->priority;
					temp->rightChild->priority =priority;
					temp = temp->rightChild;
				}
			}else if (temp->leftChild->priority >= temp->rightChild->priority) {
				priority = temp->priority;
				temp->priority = temp->leftChild->priority;
				temp->leftChild->priority = priority;
				temp = temp->leftChild;
			}
			else if (temp->rightChild->priority > temp->priority) {
				priority = temp->priority;
				temp->priority = temp->rightChild->priority;
				temp->rightChild->priority = priority;
				temp = temp->rightChild;
			}
		}
		else if (temp->leftChild) {
			if (temp->leftChild->priority > temp->priority) {
				priority = temp->priority;
				temp->priority = temp->leftChild->priority;
				temp->leftChild->priority =priority;
				temp = temp->leftChild;
			}
		}
		else if (temp->rightChild) {
			if (temp->rightChild->priority > temp->priority) {
				priority = temp->priority;
				temp->priority = temp->rightChild->priority;
				temp->rightChild->priority = priority;
				temp = temp->rightChild;
			}
		}
	}
}
void deleteOneElement(int position)
{
	setOneElementPriority(position);
	deleteFromHeap();
}
