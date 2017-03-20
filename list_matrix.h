#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 50
typedef struct matrix_node *matrix_pointer;
typedef enum{head,entry} tagfield; 
struct entry_node {
	int row;
	int col;
	int value;
};
struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;//for the heads  not head to the heads
		struct entry_node entry;//for the entry node
	}u;
};
matrix_pointer hdnode[MAX_SIZE];
matrix_pointer new_node()
{
	matrix_pointer temp = (matrix_pointer)malloc(sizeof(struct matrix_node));
	if (!temp) {
		fprintf(stderr, "The memory is full.\n");
		exit(1);
	}
	return temp;
}
matrix_pointer mread()
{
	int num_rows, num_cols, num_terms, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last, node;
	printf("Enter the number of rows, columns, and number of nonzero terms: ");
	scanf_s("%d%d%d", &num_rows, &num_cols, &num_terms);
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node = new_node();
	node->tag = head;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;
	if (!num_heads)node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;//for the first polish --67
		}
		current_row = 0;
		last = hdnode[0];//last node in current row
		for (i = 0; i < num_terms; i++) {
			printf("Enter row,column and value: ");
			scanf_s("%d%d%d", &row, &col, &value);
			if (row > current_row) {//close current row
				last->right = hdnode[current_row];//circle to the head node
				current_row = row;
				last = hdnode[row];
			}
			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;//link into row list
			last = temp;
			hdnode[col]->u.next->down = temp;//link into col list
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[current_row];//close last row,circle
		for (i = 0; i < num_cols; i++) {
			hdnode[i]->u.next->down = hdnode[i];//close all column lists
		}
		for (i = 0; i < num_heads - 1; i++)//link all head nodes together
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[i]->u.next = node;

		node->down=node->right = hdnode[0];
	}
	return node;
}
void mwrite(matrix_pointer node)
{
	int i;
	matrix_pointer temp, head = node->right;
	printf("\n num_rows=%d num_cols=%d", node->u.entry.row, node->u.entry.col);
	printf("The matrix by row,column ,and value:\n\n");
	for (i = 0; i < node->u.entry.row; i++) {
		for (temp = head->right; temp != head; temp = temp->right)
			printf("%5d%5d%5d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	}
}
void merase(matrix_pointer* node)//to change node
{
	matrix_pointer x, y, head =(*node)->right;
	int i;
	for (i = 0; i <(*node)->u.entry.row; i++) {
		y = head->right;
		while (y!=head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x);
	}
	y = head;
	while(y != (*node)) {
		x = y; y = y->u.next; free(x);
	}//the node have not been used but been linked
	free(*node); *node = NULL;
}
matrix_pointer madd(matrix_pointer a, matrix_pointer b)
{
	static matrix_pointer head_nodes[MAX_SIZE];
	matrix_pointer temp;
	matrix_pointer temp_a_row,temp_b_row,temp_a_col,temp_b_col,node;
	int row_a = a->u.entry.row ,row_b=b->u.entry.row,num_heads,i,j;
	int col_a = a->u.entry.col, col_b = b->u.entry.col;
	if (row_a != row_b || col_a != col_b) {
		fprintf(stderr, "The matrixs are not compatible.\n");
		exit(1);
	}
	num_heads = (row_a > col_a) ? row_a : col_a;
	node = new_node();
	node->tag = head;
	node->u.entry.row = row_a;
	node->u.entry.col = col_a;
	if (!num_heads)node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			head_nodes[i] = temp; head_nodes[i]->tag = head;
			head_nodes[i]->right = temp; head_nodes[i]->u.next = temp;
		}
		for (i = 0; i < row_a; i++) {
			for (j = 0; j < col_a; j++) {
				int k;
				//for(k=0,temp_a_row=hdnode[i],)
			}
		}
	}
}