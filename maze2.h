#pragma once
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define ROW 11
#define COL 11
int maze[ROW][COL];
void initMaze() {
	for (int i = 0; i < ROW; i++)
		maze[i][0] = maze[i][ROW - 1] = 1;
	for (int j = 0; j <COL; j++)
		maze[0][j] = maze[COL - 1][j] = 1;
}
void fillMaze() {
	initMaze();
	srand(time(NULL));
	for (int i = 1; i < ROW - 1; i++)
		for (int j = 1; j < COL - 1; j++)
			maze[i][j] = (rand() % 2 == 0) ? 0 : 1;
	maze[1][1] = maze[ROW - 2][COL - 2] = 0;
}
void printMaze() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++)
			if (maze[i][j] == 0)
				printf("%2c", '*');
			else
				printf("%2s", "-");
		printf("\n");
	}
}
typedef struct {
	int horiz;
	int vert;
}offset;

offset move[8] = {
	{ -1,0 },
	{ -1,1 },
	{ 0,1 },
	{ 1,1 },
	{ 1,0 },
	{ 1,-1 },
	{ 0,-1 },
	{ -1,-1 }
};
typedef struct {
	int row;
	int col;
	int dir;
}element;
element stack[MAX];
int top = -1;
void push(element pos) {
	stack[++top] = pos;
}
element pop() {
	return stack[top--];
}
int visited[ROW][COL];
int findPath() {
	element position;
	int row, col, next_row, next_col, find = 0, direction = 0;
	visited[1][1] = 1;
	stack[0].row = stack[0].col = 1;
	stack[0].dir = 0;
	top = 0;
	while (!find) {
		position = pop();
		row = position.row;
		col = position.col;
		direction = position.dir;
		while (!find&&direction < 8) {
			next_row = row + move[direction].horiz;
			next_col = col + move[direction].vert;
			if (next_row == ROW - 2 && next_row == COL - 2) {
				find = 1;
				break;
			}
			else if (!maze[next_row][next_col] && !visited[next_row][next_col]) {
				visited[next_row][next_col] = 1;
				position.row = row;
				position.col = col;
				push(position);
				row = next_row;
				col = next_col;
				direction = 0;
			}
			else {
				direction++;
			}
		}
		if (top >= 0) {
			continue;
		}
		else {
			printf("The maze has no path to go out!\n");
			return 0;
		}
	}

	printf("The path of this maze is:\n");
	//printf("-------------------------------\n");
	//printf("Row  Col\n");
	//for (int i = 0; i <= top; i++)
	//	printf("%3d%3d\n", stack[i].row, stack[i].col);
	//printf("%3d%3d\n", row, col);
	//printf("%3d%3d\n", next_row, next_col);
	//printf("-------------------------------\n");
	position.row = row;
	position.col = col;
	push(position);
	position.row = ROW - 2;
	position.col = COL - 2;
	push(position);
	printf("-------------------------------\n");
	int label = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j <= COL; j++) {
			for (int k = 0; k <= top; k++)
				if (stack[k].row == i&&stack[k].col == j) {
					printf("%2c", '*');
					label = 1;
				}
			if (!label)
				printf("%2c", ' ');
			else
				label = 0;
		}
		printf("\n");
	}
	printf("-------------------------------\n");
	return 1;
}
void test() {
	fillMaze();
	printMaze();
	if (findPath())
		printf("Do a good job!\n");
}

