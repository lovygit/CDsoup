#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_SIZE 100
#define SWAP(X,Y,Z) ((Z)=(X),(X)=(Y),(Y)=(Z))
typedef struct {
	int key;
}element;
typedef struct leftist *leftist_tree;
struct leftist {
	leftist_tree left_child;
	element data;
	leftist_tree right_child;
	leftist_tree parent;
	int shortest;
};
leftist_tree queue[MAX_SIZE];
int size = 0;
int top = -1;
void addQueue(leftist_tree node)
{
	if (size == MAX_SIZE) {
		fprintf(stderr, "The queue is full\n");
		return;
	}
	queue[size++] = node;
}
leftist_tree delQueue()
{
	if (top >= size - 1) {
		return NULL;
	}
	return queue[++top];
}
int queueEmpty()
{
	return top >= size - 1;
}
leftist_tree new_node()
{
	leftist_tree temp = (leftist_tree)malloc(sizeof(struct leftist));
	if (!temp) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->left_child = temp->right_child =temp->parent= NULL;
	temp->shortest = 1;
	return temp;
}
void min_union(leftist_tree *a, leftist_tree *b)
{
	
	/* recursively combine two nonempty min leftist trees */
	leftist_tree temp;
	/* set a to be the tree with smaller root */
	if ((*a)->data.key > (*b)->data.key) {
		SWAP(*a, *b, temp);
		SWAP((*a)->parent, (*b)->parent, temp);
	}
	/* create binary tree such that the smallest key in each subtree is in the root */
	if (!(*a)->right_child) {
		(*a)->right_child = *b;
		(*b)->parent = (*a);
	}
	else
		min_union(&(*a)->right_child, b);
	/* leftiest tree property */
	if (!(*a)->left_child) {
		(*a)->left_child = (*a)->right_child;
		(*a)->right_child = NULL;
	}
	else if ((*a)->left_child->shortest <
		(*a)->right_child->shortest) {
		SWAP((*a)->left_child, (*a)->right_child, temp);
	}
	(*a)->shortest = (!(*a)->right_child) ? 1 : (*a)->right_child->shortest + 1;
}
void min_combine(leftist_tree *a, leftist_tree *b)
{
	/* combine the two leftiest tree *a and *b . The resulting min leftist tree is returned in *a,
	and *b is to NULL */
	if (!(*a))
		*a = *b;
	else if (*b)
		min_union(a, b);
	*b = NULL;
}

void max_union(leftist_tree *a, leftist_tree *b)
{
	leftist_tree temp;
	if ((*a)->data.key < (*b)->data.key) {
		SWAP(*a, *b, temp);
	}
	if (!(*a)->right_child) {
		(*a)->right_child = *b;
		(*b)->parent = *a;
	}
	else
		max_union(&(*a)->right_child, b);
	if (!(*a)->left_child) {
		(*a)->left_child = (*a)->right_child;
		(*a)->right_child = NULL;
	}
	else if ((*a)->left_child->shortest<(*a)->right_child->shortest) {
		SWAP((*a)->left_child, (*a)->right_child, temp);
	}
	(*a)->shortest = (*a)->right_child == NULL ? 1 : (*a)->right_child->shortest + 1;

}
void max_combine(leftist_tree *a, leftist_tree *b)
{
	if (!*a)
		*a = *b;
	else if (*b)
		max_union(a, b);
	*b = NULL;
}
void printTree_(leftist_tree a,int depth)
{
	if (!a)
		return;

	for (int i = 0; i < depth; i++)
		printf("%3s"," ");
	printf("%3d\n", a->data.key);
	if (a->left_child)
		printTree_(a->left_child, depth + 1);
	else if (a->right_child) {
		for (int i = 0; i < depth + 1; i++)
			printf("%3s", " ");
		printf(" --\n");
	}
	if (a->right_child)
		printTree_(a->right_child, depth + 1);
	else if (a->left_child) {
		for (int i = 0; i < depth + 1; i++)
			printf("%3s", " ");
		printf(" --\n");
	}
}
void printTree(leftist_tree a)
{
	printf("---------------------------\n");
	printTree_(a, 0);
	printf("---------------------------\n");
}
leftist_tree getNodeBySequence(leftist_tree root,int seq)
{
	size = 0;
	top = -1;
	addQueue(root);
	leftist_tree temp=root;
	while (seq-->0) {
		temp=delQueue();
		if (!temp)
			break;
		if (temp->left_child)
			addQueue(temp->left_child);
		if (temp->right_child)
			addQueue(temp->right_child);
	}
	return temp;
}
leftist_tree delNodeNumber(leftist_tree *root, int seq)
{
	leftist_tree temp = getNodeBySequence(*root, seq);
	min_combine(&temp->left_child, &temp->right_child);
	if (temp->parent)
		temp->parent->left_child = temp->left_child;
	else
		*root = temp->left_child;
	temp->left_child->parent = temp->parent;
	return temp;
}
void test()
{
	srand(time(0));
	leftist_tree a= new_node();
	leftist_tree b = new_node();
	a->data.key = rand() % 40 + 1;
	for (int i = 0; i < 10; i++) {
		b->data.key = rand() % 100 + 1;
		min_combine(&a, &b);
		//printTree(a);
		b = new_node();
	}
	printTree(a);
}
