#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 5
#define COL 5
#define MAX_STACK_SIZE 100
typedef struct {
	int vert;
	int horiz;
} offsets;
offsets move[8] = {
	{ -1,0 },
	{ -1,1 },
	{ 0,1 },
	{ 1,1 },
	{ 1,0 },
	{ 1,-1 },
	{ 0,-1 },
	{ -1,-1 }
};
int chessbord[ROW][COL];
int step[ROW - 2][COL - 2];
void initChessbord() {
	for (int i = 0; i < ROW; i++)
		chessbord[i][0] = chessbord[i][COL - 1] = 1;
	for (int i = 0; i < COL; i++)
		chessbord[0][i] = chessbord[COL - 1][i] = 1;
}
void printChessbord() {
	printf("---------------------------\n");
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++)
			printf("%2d", chessbord[i][j]);
		printf("\n");
	}
	printf("---------------------------\n");
}
void printStep() {
	for (int i = 0; i < ROW - 2; i++) {
		for (int j = 0; j < COL - 2; j++)
			printf("%2d", step[i][j]);
		printf("\n");
	}
}
typedef struct {
	int row;
	int col;
	int dir;
}element;
element stack[MAX_STACK_SIZE];
int top = 0;
void push(element item) {
	stack[++top] = item;
}
element pop() {
	return stack[top--];
}

void findWay() {
	int seq = 0;
	int row, col, next_row, next_col, dir = 0, find = 0;
	srand(time(0));
	row = stack[0].row = rand() % (ROW - 2) + 1;
	col = stack[0].col = rand() % (COL - 2) + 1;
	printf("The start pos is [ %d,%d ]\n", row, col);
	top = 0;
	step[row - 1][col - 1] = ++seq;
	element pos;
	while (!find) {
		pos = pop();
		dir = pos.dir;
		row = pos.row;
		col = pos.col;
		seq = step[row - 1][col - 1] - 1;
		step[row - 1][col - 1] = 0;
		chessbord[row][col] = 0;
		printf("Position one\n");
		printChessbord();
		while (!find&&dir < 8) {
			next_row = row + move[dir].horiz;
			next_col = col + move[dir].vert;
			if (seq == (ROW - 2)*(COL - 2) - 2 && !chessbord[next_row][next_col]) {
				find = 1;
				break;
			}
			else if (!chessbord[next_row][next_col]) {
				pos.row = row;
				pos.col = col;
				pos.dir = dir++;
				push(pos);
				step[row - 1][col - 1] = ++seq;
				chessbord[row][col] = 1;
				printChessbord();
				row = next_row;
				col = next_col;
				dir = 0;
			}
			else
				dir++;
		}
		if (top >= 0 && !find)
			continue;
		else if (find)
			break;
		else
			printf("I can't find the correct way!\n");
	}
	step[row - 1][col - 1] = ++seq;
	step[next_row - 1][next_col - 1] = ++seq;
	printStep();
}
