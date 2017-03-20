#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include<math.h>
#define MAX_ITEM 100
typedef struct poly* poly_pointer;
struct poly {
	double coef;
	int expon;
	poly_pointer link;
};
poly_pointer avail = NULL;
poly_pointer a = NULL, b = NULL;
poly_pointer get_node()
{
	poly_pointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else {
		node = (poly_pointer)malloc(sizeof(struct poly));
		node->link = NULL;
		if (!node) {
			fprintf(stderr, "The memery is full.\n");
			exit(1);
		}
	}
	return node;
}
void return_node(poly_pointer* ptr)//return a cyclic list
{
	poly_pointer temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}
int compareNodeExpon(poly_pointer a, poly_pointer b)
{
	double c = a->expon - b->expon;
	if (c == 0)
		return 0;
	else if (c > 0)
		return 1;
	else
		return -1;
}
void attach(double coef, int expon, poly_pointer* ptr)
{
	poly_pointer newNode = (poly_pointer)malloc(sizeof(struct poly));
	if (!newNode) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = NULL;
	(*ptr)->link = newNode;
	(*ptr) = newNode;
}
poly_pointer padd(poly_pointer a, poly_pointer b)
{
	poly_pointer front, rear, aStart, bStart;
	aStart = a;
	bStart = b;
	//rear = (poly_pointer)malloc(sizeof(struct poly));
	rear = get_node();
	front = rear;
	a = a->link;
	b = b->link;
	while (a != aStart&&b != bStart) {
		switch (compareNodeExpon(a, b)) {
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
		{
			double sum = a->coef + b->coef;
			if (sum)attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		}
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		}
	}
	while (a != aStart)
		attach(a->coef, a->expon, &rear);
	while (b != bStart)
		attach(b->coef, b->expon, &rear);
	rear->link = front;
	front->coef = INT_MIN;
	return front;
}
void createExpr(poly_pointer* root, int itemNum)
{
	//srand(time(0));
	poly_pointer temp, aStart;
	*root = get_node();
	aStart = *root;
	for (int i = itemNum; i >= 0; i--) {
		temp = get_node();
		temp->coef = rand() % 10;
		temp->expon = i;
		(*root)->link = temp;
		(*root) = (*root)->link;
	}
	aStart->coef = INT_MIN;
	(*root)->link = aStart;
	(*root) = aStart;
}
void printOneItem(double coef, int expon)
{
	int coef_ = (int)coef;
	//printf("//coef_ is %d\n", coef_);
	if (coef_) {
		printf("%10lf * X[ %10d ]", coef, expon);
		/*while (expon_-- > 0) {
		putchar('x');
		if (expon_ != 0)
		putchar('*');
		}*/
	}
	else
		printf("- - - - - - - - - -");
	putchar('\n');
}
void printExpr(poly_pointer root)
{
	root = root->link;
	printf("----------------------------\n");
	while (((int)root->coef) != INT_MIN) {
		//printf("coef is %d\n", coef);
		printOneItem(root->coef, root->expon);
		root = root->link;
	}
	printf("----------------------------\n");
}
poly_pointer multiExprOneItem(poly_pointer a, poly_pointer b)
{
	poly_pointer newNode = get_node();
	newNode->coef = a->coef*b->coef;
	newNode->expon = a->expon + b->expon;
	if (((int)newNode->coef))
		return newNode;
	else
		return NULL;
}
void insertItem(poly_pointer item, poly_pointer front, poly_pointer* rear)
{
	poly_pointer temp = front->link;
	if (front->link&&front->link->expon < item->expon) {
		item->link = front->link;
		front->link = item;
		return;
	}
	for (; temp; temp = temp->link) {
		if (temp->expon >= item->expon&&temp->link&&temp->link->expon<item->expon) {
			if (temp->expon == item->expon) {
				temp->coef += item->coef;
				return;
			}
			else {
				item->link = temp->link;
				temp->link = item;
				return;
			}
		}
	}
	(*rear)->link = item;
	(*rear) = (*rear)->link;
}
poly_pointer multiExpr(poly_pointer a, poly_pointer b)
{
	poly_pointer front, rear, aStart, bStart, midResult;
	aStart = a;
	bStart = b;
	rear = get_node();
	front = rear;
	a = a->link;
	b = b->link;
	while (a != aStart) {
		if (((int)a->coef) != 0) {
			while (b != bStart) {
				if (((int)b->coef) != 0) {
					midResult = multiExprOneItem(a, b);
					if (midResult)
						insertItem(midResult, front, &rear);
				}
				b = b->link;
			}
		}
		a = a->link;
		b = bStart->link;
	}
	rear->link = front;
	front->coef = INT_MIN;
	return front;
}
