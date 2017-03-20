#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 50
#define MAX_QUEUE_SIZE 50
#define MAX_TREE_SIZE 50
#define TRUE 1
#define FALSE 0
#define IS_FULL(P) (!(P))
typedef struct node *tree_pointer;
struct node {
	int data;
	tree_pointer left_child, right_child;
};
typedef struct thread_tree *thread_pointer;
struct thread_tree {
	int left_thread , right_thread;
	thread_pointer left_child;
	thread_pointer right_child;
	int data;
};
void lvr_order(tree_pointer ptr)
{
	if (ptr) {
		lvr_order(ptr->left_child);
		printf("%5d", ptr->data);
		lvr_order(ptr->right_child);
	}
}
void vlr_order(tree_pointer ptr)
{
	if (ptr) {
		printf("%5d", ptr->data);
		vlr_order(ptr->left_child);
		vlr_order(ptr->right_child);
	}
}
void lrv_order(tree_pointer ptr)
{
	if (ptr) {
		lrv_order(ptr->left_child);
		lrv_order(ptr->right_child);
		printf("%5d", ptr->data);
	}
}
void add(int* top, tree_pointer node,tree_pointer stack[])
{
	if (node != NULL)
		stack[++(*top)] = node;
}
tree_pointer del(int* top,tree_pointer stack[])
{
	if (*top > -1) {
		return stack[(*top)--];
	}
	else
		return NULL;
}
void iter_inorder(tree_pointer node)//中序
{
	int top = -1;
	tree_pointer stack[MAX_STACK_SIZE];
	while (TRUE) {
		for (; node; node = node->left_child)
			if (node)
				add(&top, node, stack);
			else
				break;
		node = del(&top, stack);
		if (!node)break;
		printf("%5d", node->data);
		node = node->right_child;
	}
}
void iter_preorder(tree_pointer node)
{
	int top = -1;
	tree_pointer stack[MAX_STACK_SIZE];
	while (TRUE) {
		for (; node; node = node->left_child) {
			if (!node)break;
			printf("%5d", node->data);
			add(&top, node, stack);
		}
		node = del(&top, stack);
		if (!node)break;
		node = node->right_child;
	}
}
//后序遍历的迭代伪实现
void save_stack(int* top,tree_pointer node, tree_pointer* stack)
{
	if (node) {
		add(top, node, stack);
		save_stack(top, node->right_child, stack);
		save_stack(top, node->left_child, stack);
	}
}
void iter_rearorder(tree_pointer node)
{
	int top = -1;
	tree_pointer stack[MAX_STACK_SIZE];
	save_stack(&top, node, stack);
	while (TRUE) {
		node = del(&top, stack);
		if (!node)break;
		printf("%5d",node->data);
	}
}

void addq(int front, int* rear, tree_pointer ptr,tree_pointer queue[])
{
	*rear = (*rear + 1) % MAX_QUEUE_SIZE;
	if (front == *rear) {
		fprintf(stderr, "The queue is full.\n");
		exit(1);
	}
	queue[*rear] = ptr;
}
tree_pointer deleteq(int* front, int rear, tree_pointer queue[])
{
	if (*front == rear) {
		fprintf(stderr, "\nThe queue is empty.\n");
		return NULL;
	}
	*front = (*front + 1) % MAX_QUEUE_SIZE;
	return queue[*front];
}
void level_order(tree_pointer ptr)
{
	int front = 0;
	int rear = 0;
	tree_pointer queue[MAX_QUEUE_SIZE];
	if (!ptr)return;
	addq(front, &rear, ptr, queue);
	while (TRUE) {
		ptr = deleteq(&front, rear, queue);
		if (ptr) {
			printf("%5d", ptr->data);
			if (ptr->left_child)
				addq(front, &rear, ptr->left_child, queue);
			if (ptr->right_child)
				addq(front, &rear, ptr->right_child, queue);
		}
		else
			break;
	}
}
tree_pointer copy(tree_pointer ptr)
{
	if (ptr) {
		tree_pointer temp = (tree_pointer)malloc(sizeof(struct node));
		if (IS_FULL(temp)) {
			fprintf(stderr, "The memory is full.\n");
			exit(1);
		}
		temp->left_child = copy(ptr->left_child);
		temp->right_child = copy(ptr->right_child);
		temp->data = ptr->data;
		return temp;
	}
	return NULL;
}
int equal(tree_pointer a, tree_pointer b)
{
	return ((!a&&!b) ||(
		(a&&b && (a->data == b->data)) &&
		(equal(a->left_child,b->left_child)) &&
		(equal(a->right_child,b->right_child))));
}
int node_count(tree_pointer node)
{
	if (node) {
		return 1 + node_count(node->left_child) + node_count(node->right_child);
	}
	else
		return 0;
}
void reverse_left_right(tree_pointer node)
{
	if (node) {
		tree_pointer temp = node->left_child;
		node->left_child = node->right_child;
		node->right_child = temp;
		reverse_left_right(node->left_child);
		reverse_left_right(node->right_child);
	}
}
tree_pointer create_node()
{
	tree_pointer temp = (tree_pointer)malloc(sizeof(struct node));
	if (IS_FULL(temp)) {
		fprintf(stderr, "The memory is full.\n");
	}
	return temp;
}
//node 参数无明显意义
tree_pointer create_tree(tree_pointer node,int data[],int size)
{
	if (size < 1)return NULL;
	tree_pointer tree[MAX_TREE_SIZE];
	for (int i =size-1; i >=0; i--) {
		tree[i] = create_node();
		if (2 * i + 1 < size) {
			tree[i]->left_child = tree[2 * i + 1];
		}
		else {
			tree[i]->left_child = NULL;
		}
		if (2 * i + 2 < size) {
			tree[i]->right_child = tree[2 * i + 2];
		}
		else {
			tree[i]->right_child = NULL;
		}
		tree[i]->data = data[i];
	}
	node = tree[0];
	return node;
}



thread_pointer insucc_later(thread_pointer tree)
{
	/*find the inorder sucessor of tree in a threaded binary
	tree*/
	thread_pointer temp = tree->right_child;
	if (!tree->right_thread)
		while (!temp->left_thread)
			temp = temp->left_child;
	return temp;
}
thread_pointer insucc_former(thread_pointer tree)
{
	thread_pointer temp = tree->left_child;
	if (!tree->left_thread)
		while (!temp->right_thread)
			temp = temp->right_child;
	return temp;
}
void tinorder(thread_pointer tree)
{
	thread_pointer temp = tree;
	if(tree)
		printf("%5d", temp->data);
	while (!(temp->right_thread==FALSE&&temp->right_child==NULL)) {//没有后驱也没有右孩子
		temp = insucc_later(temp);
		if (temp == tree)break;
		printf("%5d", temp->data);
	}
}
thread_pointer getMostLeftThreadNode(thread_pointer tree)
{
	thread_pointer temp = NULL;
	while(tree->left_thread==FALSE) {
		temp = tree;
		tree = tree->left_child;
	}
	temp = tree;
	return temp;
}
thread_pointer getMostRightThreadNode(thread_pointer tree)
{
	thread_pointer temp = NULL;
	while (tree) {
		temp = tree;
		tree = tree->right_child;
	}
	return temp;
}
void insert_right(thread_pointer parent, thread_pointer child)
{
	thread_pointer temp;
	child->right_thread = parent->right_thread;
	child->right_child = parent->right_child;
	child->left_thread = TRUE;//have been modified
	child->left_child = parent;
	parent->right_child = child;
	parent->right_thread = FALSE;
	if (!child->right_thread) {
		temp = insucc_later(child);
		temp->left_child = child;
	}
}
void insert_left(thread_pointer parent, thread_pointer child)
{
	thread_pointer temp;
	child->left_thread = parent->left_thread;
	child->left_child = parent->left_child;
	child->right_thread = TRUE;//have been modified
	child->right_child = parent;
	parent->left_thread = FALSE;
	parent->left_child = child;
	if (!child->left_thread) {
		temp = insucc_former(child);
		temp->right_child = child;
	}
}
void create_clue(thread_pointer tree)
{
	thread_pointer pre = tree;
	void create_clue_(thread_pointer, thread_pointer* pre);
	create_clue_(tree, &pre);
	if (!tree->right_child) {
		tree->right_thread = TRUE;
		tree->right_child = tree;
	}
	//thread_pointer rightMost = getMostRightThreadNode(tree);
	//rightMost->right_thread = TRUE;
	//rightMost->right_child = tree;
}
void create_clue_(thread_pointer tree, thread_pointer* pre)//have been modified
{
	if (tree) {
		create_clue_(tree->left_child,pre);
		if (!tree->left_child) {
			tree->left_thread = TRUE;
			tree->left_child = *pre;
		}
		if (!(*pre)->right_child) {
			(*pre)->right_thread = TRUE;
			(*pre)->right_child = tree;
		}
		*pre = tree;
		create_clue_(tree->right_child,pre);
	}
}
thread_pointer create_clue_tree(thread_pointer* root,int data[],int size)
{
	thread_pointer tree[MAX_TREE_SIZE];
	for (int i = size - 1; i >= 0; i--) {
		tree[i] = (thread_pointer)malloc(sizeof(struct thread_tree));
		tree[i]->data = data[i];
		if (2 * i + 1 < size)
			tree[i]->left_child = tree[i * 2 + 1];
		else
			tree[i]->left_child = NULL;
		if (2 * i + 2 < size)
			tree[i]->right_child = tree[2 * i + 2];
		else
			tree[i]->right_child = NULL;
		tree[i]->left_thread = tree[i]->right_thread = FALSE;
	}
	create_clue(tree[0]);
	for (int i = 0; i < size; i++) {
		printf("%d: left_thread is %s ||",i, (tree[i]->left_thread == 0) ? "F" : "T");
		printf("right thread is %s\n", (tree[i]->right_thread == 0) ? "F" : "T");
	}
	*root = tree[0];
	return *root;
}
void lvrPrintClueTree(thread_pointer tree)
{
	thread_pointer temp = getMostLeftThreadNode(tree);
	tinorder(temp);
}