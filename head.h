#ifndef HEAD
#define MAX_SIZE 15
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#include<stdarg.h>
#include<time.h>
int a[5] = { 1,2,3,4,5 };
//1.2 习题
#define SWAP(X,Y,T) ((T)=(X),(X)=(Y),(Y)=(T))
#define COMPARE(X,Y) ((X)>(Y)? 1:((X)==(Y))? 0:-1)
int binsearch(int list[], int searchnum, int left, int right);
long Horner(int number, int constant[], int);
void perm(char* list, int i, int n);
void true_false(int i, bool value[], int n);
void sort_recurse(int i, int data[], int n);
double calculate(int num);
void print_same(double(*p)(int), int data[], int i, int n);
bool answer_6(int n);
void print_answer_6(int n);
double Ackerman(double m, double n);
void Hanoi(int n, char from, char to, char depend_on);
void move(int n, char from, char to);
//1.2习题结束
#endif 
//1.2 习题
void sort(int list[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		SWAP(list[i], list[min], temp);
	}

}
int binsearch(int list[], int searchnum, int left, int right)
{
	int middle = 0;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum)) {
		case 1:
			right = middle - 1;
			break;
		case 0:
			return middle;
		case -1:
			left = middle + 1;
			break;
		}
	}
	return -1;
}
void perm(char* list, int i, int n)
{
	static int count = 0;
	int j, temp;
	if (i + 1 == n) {
		printf("%d:", ++count);
		for (j = 0; j < n; j++)
			printf("%c-", list[j]);
		printf("\n");
	}
	else {
		for (j = i; j < n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
		}
	}
}
long Horner(int number, int constant[], int n)
{
	long result = constant[n - 1];
	for (int i = n - 2; i >-1; i--) {
		result = result*number + constant[i];
	}
	return result;
}
void true_false(int i, bool value[], int n)
{
	static int count = 1;
	if (i == n) {
		printf("%-3d----< ", count++);
		for (int j = 0; j < n; j++)
			printf("%-7s", value[j] ? "true " : "false ");
		printf(">\n");
	}
	else {
		true_false(i + 1, value, n);
		value[i] = !value[i];
		true_false(i + 1, value, n);
	}
}
void sort_recurse(int i, int data[], int n)
{
	int temp;
	if (i < n - 1) {
		for (int j = i + 1; j < n; j++)
			if (data[i]>data[j])
				SWAP(data[i], data[j], temp);
		sort_recurse(i + 1, data, n);
	}
}
double calculate(int num)
{
	return (num - 1)*(num - 2)*(num - 3);
}
void print_same(double(*p)(int), int data[], int i, int n)
{
	if (i < n - 1) {
		for (int j = i + 1; j < n; j++)
			if (p(data[i]) == p(data[j]) && data[i] != data[j])
				printf("input %d or %d will get the same result!\n", data[i], data[j]);
		print_same(p, data, i + 1, n);
	}
}
void Hanoi(int n, char from, char to, char depend_on)
{
	if (n == 1)
		move(1, from, to);
	else {
		Hanoi(n - 1, from, depend_on, to);
		move(n, from, to);
		Hanoi(n - 1, depend_on, to, from);
	}
}
void move(int n, char from, char to)
{
	static int i = 1;
	printf("第 %d 步:将 %d 号盘子从 %c 移动到 %c\n", i++, n, from, to);
}
bool answer_6(int n)
{
	int count = 1;
	for (int i = 2; i*i <= n; i++) {
		if (n%i == 0) {
			count += i;
			count += n / i;
		}
	}
	return (n == count) ? true : false;
}
void print_answer_6(int n)
{
	printf("1");
	for (int i = 2; i*i <= n; i++)
		if (n%i == 0) {
			printf("+%d+%d", i, n / i);
		}
}
double Ackerman(double m, double n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return Ackerman(m - 1, 1);
	else
		return Ackerman(m - 1, Ackerman(m, n - 1));
}
void magic_square()
{
	static int square[MAX_SIZE][MAX_SIZE];
	int i, j, row, column;
	int count;
	int size;
	printf("Enter the size of the square: ");
	scanf_s("%d", &size);
	if (size<1 || size>MAX_SIZE + 1) {
		fprintf(stderr,"Error!  Size is out of range\n");
		exit(1);
	}
	if (!(size % 2)) {
		fprintf(stderr, "Error! Size is even\n");
		exit(2);
	}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			square[i][j] = 0;
	square[0][(size - 1) / 2] = 1;
	i = 0;
	j = (size - 1) / 2;
	for (count = 2; count <= size*size; count++) {
		row = (i - 1 < 0) ? size - 1 : i - 1;
		column = (j - 1 < 0) ? size - 1 : j - 1;
		if (square[row][column]) {
			i = (++i) % size;
		}
		else {
			i = row;
			j = column;
		}
		square[i][j] = count;
	}
	printf("the magic square is :\n");
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			printf("%5d", square[i][j]);
		putchar('\n');
	}
}
void magic_square_2(int row, int column, int square[][MAX_SIZE], int size)
{
	static int count = 1;
	if (is_full(square, size)) {
		printf("the square has been filled !\n");
		return;
	}
	int i = (row - 1 < 0) ? size - 1 : row - 1;//the next row
	int j = (column - 1 < 0) ? size - 1 : column - 1;//the next column
	if (square[row][column] == 0) {
		square[row][column] = count++;
		magic_square_2(i, j, square, size);
	}
	else {
		i = (++row) % size;
		magic_square_2(i, j, square, size);
	}
}
int is_full(int square[][MAX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (square[i][j] == 0)
				return 0;
	return 1;
}
void magic()
{
	int size;
	int square[MAX_SIZE][MAX_SIZE];
	printf("Enter the size of the square: ");
	scanf_s("%d", &size);
	if (size<1 || size>MAX_SIZE + 1) {
		fprintf(stderr, "Error!  Size is out of range\n");
		exit(1);
	}
	if (!(size % 2)) {
		fprintf(stderr, "Error! Size is even\n");
		exit(2);
	}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			square[i][j] = 0;
	magic_square_2(0, (size - 1) / 2, square, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			printf("%5d", square[i][j]);
		putchar('\n');
	}

}
//1.2习题结束


