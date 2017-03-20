#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct node *node_ptr;
struct node{
	double coef;
	int expo;
	node_ptr next;
};
node_ptr new_node() {
	node_ptr temp = (node_ptr)malloc(sizeof(struct node));
	if (!temp) {
		fprintf(stderr, "The memory is full");
		exit(1);
	}
	temp->coef = 0;
	temp->next = NULL;
	return temp;
}
void insertNewNode(node_ptr* head,node_ptr newNode) {
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	node_ptr move = *head, movePre = *head;
	while (move) {
		if (newNode->expo > move->expo) {
			if (move == *head) {
				newNode->next = *head;
				*head = newNode;
				return;
			}
			else {
				movePre->next = newNode;
				newNode->next = move;
				return;
			}
		}
		else if (newNode->expo == move->expo) {
			move->coef += newNode->coef;
			if (move->coef >= -1e-5&&move->coef <= 1e-5)
				if (move != movePre)
					movePre->next = move->next;
				else
					(*head) = (*head)->next;
			return;
		}
		movePre = move;
		move = move->next;
	}
	if (move == NULL) {
		movePre->next = newNode;
	}
}
void printExpr(node_ptr head) {
	node_ptr move = head;
	double coef;
	int expo;
	if (head == NULL) {
		printf("the expression is empty\n");
		return;
	}
	printf("-----------------------\n");
	while (move) {
		coef = move->coef;
		expo = move->expo;
		printf("%f", coef);
		int i = 0;
		for (; i < expo; i++) {
			if (i == 0)
				printf("*");
			if (i != expo - 1) {
				printf("x*");
			}
			else
				printf("x +\n");
		}
		if (i == 0)
			printf("\n");
		move = move->next;
	}
	printf("-----------------------\n");
}
int getFirstChar_NoBlank() {
	int end;
	while ((end = getchar())&& end == ' ');
	if (end == 'q' || end == 'Q')
		return 1;
	else
	{
		ungetc(end,stdin);
		return 0;
	}
}
node_ptr samp(node_ptr* head) {//数据采样
	printf("Please input the data pair coef-expo q|Q to quit \n");
	double coef;
	int expo=0;
	node_ptr dataNode;
	printf("(ceof,expo)--   ");
	if (getFirstChar_NoBlank()) {
		while (getchar() != '\n');
		return NULL;
	}
	scanf_s("%lf%d", &coef, &expo);
	while (1) {
		while (getchar() != '\n');
		dataNode = new_node();
		dataNode->coef = coef;
		dataNode->expo = expo;
		insertNewNode(head, dataNode);
		printf("(ceof,expo)--   ");
		if (getFirstChar_NoBlank())
			break;
		scanf_s("%lf%d", &coef, &expo);
	}
	while (getchar() != '\n');
	return *head;
}
node_ptr exprAdd(node_ptr* head,node_ptr head1, node_ptr head2) {
	node_ptr move1 = head1;
	node_ptr move2= head2;
	node_ptr nodeCopy;
	while (move1) {
		nodeCopy = new_node();
		nodeCopy->coef = move1->coef;
		nodeCopy->expo = move1->expo;
		insertNewNode(head,nodeCopy);
		move1 = move1->next;
	}
	while (move2) {
		nodeCopy = new_node();
		nodeCopy->coef = move2->coef;
		nodeCopy->expo = move2->expo;
		insertNewNode(head, nodeCopy);
		move2 = move2->next;
	}
	return *head;
}
node_ptr exprSub(node_ptr* head, node_ptr head1, node_ptr head2) {
	node_ptr move= head2;
	while (move) {
		move->coef = -move->coef;
		move = move->next;
	}
	exprAdd(head, head1, head2);
	node_ptr movePre = *head;
	move = *head;
	while (move) {
		if (move->coef>=-1e-5&&move->coef<=1e-5) {
			if (move == *head) {
				*head = (*head)->next;
			}
			else {
				movePre->next = move->next;
			}
		}
		movePre = move;
		move = move->next;
	}
	return *head;
}
void test() {
	node_ptr head1 = NULL, head2 = NULL, head = NULL;
	samp(&head1);//数据采样
	printExpr(head1);
	samp(&head2);
	printExpr(head2);
	//exprAdd(&head, head1, head2);
	exprSub(&head, head1, head2);//减
	printExpr(head);
	head = NULL;
	exprAdd(&head, head1, head2);//加
	printExpr(head);
	system("pause");
}