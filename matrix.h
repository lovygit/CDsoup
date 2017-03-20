#include<stdio.h>
#include<stdlib.h>
#ifndef MATRIX
#define MAX_TERMS 101
#define MAX_COL 50
typedef struct {
	int col;
	int row;
	int value;
}term;
term a[MAX_TERMS];
term b[MAX_TERMS];
term c[MAX_TERMS];
void init() {
	a[0].col = a[0].row = 6;	a[0].value = 8;
	a[1].row = a[2].row = a[3].row = 0;
	a[4].row = a[5].row = 1;	a[6].row = 2;
	a[7].row = 4;	a[8].row = 5;

	a[1].col = 0;	a[2].col = 3;
	a[3].col = 5;	a[4].col = 1;
	a[5].col = 2;	a[6].col = 3;
	a[7].col = 0;	a[8].col = 2;

	a[1].value = 15;	a[2].value = 22;
	a[3].value = -15;	a[4].value = 11;
	a[5].value = 3;		a[6].value = -6;
	a[7].value = 91;	a[8].value = 28;
}
void printTerm(term argu[])
{
	int i, j;
	int row = argu[0].row;
	//int col = argu[0].col;
	int n = argu[0].value;
	if (n > 0) {
		puts("---------------------------");
		printf("row:%d col:%d value: %d\n", argu[0].row, argu[0].col, argu[0].value);
		for (i = 0; i < row; i++)
			for (j = 1; j <= n; j++)
				if (argu[j].row == i) {
					printf("row:%d col:%d value: %d\n", argu[j].row, argu[j].col, argu[j].value);
				}
		puts("---------------------------");
	}

}
void transport(term a[], term b[])
{
	int n, i, j, currentb;
	n = a[0].value;
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].value = n;
	if (n > 0) {
		currentb = 1;//the first element except the totol-->a[0]
		for (i = 0; i < a[0].col; i++)
			for (j = 1; j <= n; j++)
				if (a[j].col == i) {
					b[currentb].col = a[j].row;
					b[currentb].row = a[j].col;
					b[currentb].value = a[j].value;
					currentb++;
				}
	}
}
void fast_transport(term a[], term b[])
{
	int row_terms[MAX_COL], starting_pos[MAX_COL];
	int i, j, num_cols = a[0].col, num_rows = a[0].row, num_terms = a[0].value;
	b[0].value = num_terms;
	b[0].col = num_rows;
	b[0].row = num_cols;
	if (num_terms > 0) {
		for (i = 0; i < num_cols; i++)
			row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++)
			row_terms[a[i].col]++;
		starting_pos[0] = 1;
		for (i = 1; i < num_cols; i++)
			starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
		for (i = 1; i <= num_terms; i++) {
			j = starting_pos[a[i].col]++;//in the same group to the next position
			b[j].col = a[i].row;
			b[j].row = a[i].col;
			b[j].value = a[i].value;
		}
	}
}
void add(term a[], term b[], term c[])
{
	int same[MAX_COL];
	int numberCount_b = b[0].value, numberCount_a = a[0].value;
	int row_a = a[0].row, col_a = a[0].col, row_b = b[0].row, col_b = b[0].col;
	if (row_a != row_b || col_a != col_b) {
		fprintf(stderr, "imcompatible matrices\n");
		exit(1);
	}
	int i, j, index_a = 1, index_b = 1, index_c = 1, exist = 0;
	for (i = 0; i < MAX_COL; i++)
		for (j = 0; j < MAX_COL; j++)
			same[i] = 0;
	for (i = 1; i <= numberCount_a; i++) {
		for (j = 1; j <= numberCount_b; j++) {
			if (b[j].row == a[i].row&&b[j].col == a[i].col)
				same[i] = 1;
		}
	}
	for (i = 0; i < row_a; i++) {
		j = index_a;
		if (a[index_a].row == i)
			for (; a[index_a].row == i; index_a++) {
				//printf("a[%d] is --->%d\n", index_a, a[index_a]);
				if (same[index_a] == 1)continue;
				else {
					c[index_c].row = a[index_a].row;
					c[index_c].col = a[index_a].col;
					c[index_c++].value = a[index_a].value;
				}
			}
		//printf("index_a is --->%d and i is %d\n", index_a,i);
		if (b[index_b].row == i)
			for (; b[index_b].row == i; index_b++) {
				//printf("b[%d] is --->%d\n", index_b, b[index_b]);
				while (a[j].row == i) {
					if (a[j].col == b[index_b].col) {
						c[index_c].row = b[index_b].row;
						c[index_c].col = b[index_b].col;
						c[index_c++].value = a[j].value + b[index_b].value;
						exist = 1;
						break;
					}
					j++;
				}
				if (exist) {
					exist = 0;
					continue;
				}
				else {
					c[index_c].row = b[index_b].row;
					c[index_c].col = b[index_b].col;
					c[index_c++].value = b[index_b].value;
				}
			}
	}
	c[0].row = a[0].row;
	c[0].col = a[0].col;
	c[0].value = index_c - 1;
}
#endif
