#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct ParentsNode* p_pointer;
typedef struct ParentsNode {
	char data;
	int parent;
}ParentNode;
typedef struct LinkChildNode *node_pointer;
typedef struct LinkChildNode {
	int child;
	int data;
	node_pointer next;
}LinkChildNode;
node_pointer new_childNode() {
	node_pointer pointer = (node_pointer)malloc(sizeof(LinkChildNode));
	if (!pointer) {
		fprintf(stderr, "The memory is full\n");
		return NULL;
	}
	pointer->child = -1;
	pointer->next = NULL;
	return pointer;
}
node_pointer linkChildNodes[MAX];
ParentNode parentsNodes[MAX];
int fillParentsNodes() {
	char parent, child;
	int index = 0;
	FILE* file;
	fopen_s(&file, "f:/data.txt", "r");
	fscanf_s(file, "%c%c", &parent, 1, &child, 1);
	while (!(parent<'a' || parent>'z' || child<'a' || child>'z')) {
		int i = 0;
		for (i = 0; i < index; i++) {
			if (parentsNodes[i].data == parent)
				break;
		}
		if (i == index) {
			parentsNodes[index].data = parent;
			parentsNodes[index].parent = -1;
			index++;
		}
		parentsNodes[index].data = child;
		parentsNodes[index].parent = i;
		index++;
		while (fgetc(file) != '\n');
		fscanf_s(file, "%c%c", &parent, 1, &child, 1);
	}
	fclose(file);
	return index;
}
void printParentsNodes(int size) {
	for (int i = 0; i < size; i++)
		printf("%5c- %d\n", parentsNodes[i].data, parentsNodes[i].parent);
}
void fillLinkChildNodes(int size) {
	for (int i = 0; i < size; i++) {
		linkChildNodes[i] = new_childNode();
		linkChildNodes[i]->data = parentsNodes[i].data;
		for (int j = i + 1; j < size; j++) {
			if (parentsNodes[j].parent == i) {
				node_pointer child = new_childNode();
				child->child = 1;
				child->data = j;
				node_pointer temp = linkChildNodes[i];
				while (temp->next)
					temp = temp->next;
				temp->next = child;
			}
		}
	}
}
void printChildNodes(int size) {
	for (int i = 0; i < size; i++) {
		printf("%5c", linkChildNodes[i]->data);
		node_pointer temp = linkChildNodes[i]->next;
		while (temp) {
			printf("%5d", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

typedef struct childBrotherNode* cb_pointer;
typedef struct childBrotherNode {
	int data;
	cb_pointer left_child;
	cb_pointer right_child;
}childBrotherNode;
cb_pointer new_childBrotherNode() {
	cb_pointer pointer = (cb_pointer)malloc(sizeof(childBrotherNode));
	if (!pointer) {
		fprintf(stderr, "The memory is full\n");
		return NULL;
	}
	pointer->left_child = pointer->right_child = NULL;
	return pointer;
}
int mark[MAX];
int findBrother(int index, node_pointer linkChildNodes[]) {
	int parent = parentsNodes[index].parent;
	if (parent == -1)
		return -1;
	node_pointer pointer = linkChildNodes[parent]->next;
	while (pointer) {
		int index = pointer->data;
		if (!mark[index]) {
			mark[index] = 1;
			break;
		}
		pointer = pointer->next;
	}
	if (pointer)
		return pointer->data;
	else
		return -1;
}
int findLeftChild(int index, node_pointer linkChildNodes[]) {
	if (linkChildNodes[index]->next) {
		mark[linkChildNodes[index]->next->data] = 1;
		return linkChildNodes[index]->next->data;
	}
	else
		return -1;
}
void createBinaryTree_(cb_pointer parent, int index, node_pointer linkChildNodes[]) {
	int childIndex = findLeftChild(index, linkChildNodes);
	int brotherIndex = findBrother(index, linkChildNodes);
	if (childIndex != -1) {
		cb_pointer left_child = new_childBrotherNode();
		left_child->data = parentsNodes[childIndex].data;
		parent->left_child = left_child;
		createBinaryTree_(left_child, childIndex, linkChildNodes);
	}
	if (brotherIndex != -1) {
		cb_pointer right_child = new_childBrotherNode();
		right_child->data = parentsNodes[brotherIndex].data;
		parent->right_child = right_child;
		createBinaryTree_(right_child, brotherIndex, linkChildNodes);
	}
}
cb_pointer createBinaryTree(cb_pointer* root, node_pointer linkChildNodes[]) {
	*root = new_childBrotherNode();
	(*root)->data = linkChildNodes[0]->data;
	createBinaryTree_(*root, 0, linkChildNodes);
	return *root;
}
void printBinaryTree(cb_pointer root, int depth) {
	if (root) {

		for (int i = 0; i < depth; i++)
			printf("%2s", " ");
		printf("%2c\n", root->data);
		if (root->left_child)
			printBinaryTree(root->left_child, depth + 1);
		else if (root->right_child) {
			for (int i = 0; i < depth + 1; i++)
				printf("%2s", " ");
			printf("%2s\n", "__");
		}
		if (root->right_child)
			printBinaryTree(root->right_child, depth + 1);
		else if (root->right_child) {
			for (int i = 0; i < depth + 1; i++)
				printf("%2s", " ");
			printf("%2s\n", "__");
		}
	}
}
void test() {
	int size = fillParentsNodes();
	printParentsNodes(size);
	fillLinkChildNodes(size);
	printChildNodes(size);
	cb_pointer root;
	createBinaryTree(&root, linkChildNodes);
	printBinaryTree(root, 0);
}
