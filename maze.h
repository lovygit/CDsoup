#include<stdio.h>
#include<stdlib.h>
#ifndef MAZE
#ifndef MAX_STACK_SIZE
#define MAX_STACK_SIZE 100
#endif
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
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];
int top = 0;
void add(int* top, element item)
{
	if (*top >= MAX_STACK_SIZE - 1) {
		fprintf(stderr, "the stack is full.\n");
		exit(1);
	}
	stack[++*top] = item;
}
element del(int* top)
{
	if (*top == -1) {
		fprintf(stderr, "the stack is empty.\n");
		exit(2);
	}
	return stack[(*top)--];
}
int maze[13][17] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1 },
	{ 1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1 },
	{ 1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1 },
	{ 1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1 },
	{ 1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1 },
	{ 1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1 },
	{ 1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1 },
	{ 1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1 },
	{ 1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1 },
	{ 1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};
int mark[13][17] = { 0 };
#define EXIT_ROW 11
#define EXIT_COL 15
void print_mark()
{
	printf("--------------------------------------------------------\n");
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			printf("%3d", mark[i][j]);
		}
		putchar('\n');
	}
	printf("--------------------------------------------------------\n");
}
void path()
{
	int  row, col, next_row, next_col, dir, found = 0;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (!found&& top>-1) {
		printf("the top is %d\n", top);
		position = del(&top);
		row = position.row;
		col = position.col;
		dir = position.dir;
		print_mark();
		while (dir < 8 && !found) {
			next_row = row + move[dir].vert;
			next_col = col + move[dir].horiz;
			if (next_row == EXIT_ROW&&next_col == EXIT_COL) {
				found = 1;
				break;
			}
			else if (!maze[next_row][next_col] && !mark[next_row][next_col]) {
				mark[next_row][next_col] = 1;
				position.row = row; position.col = col;
				position.dir = dir++;
				add(&top, position);
				row = next_row; col = next_col; dir = 0;
			}
			else {
				dir++;
			}
		}
	}
	if (found) {
		printf("The path is :\n");
		printf("row   col\n");
		for (int i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else {
		printf("The maze does not have a path\n");
	}
}
#endif 