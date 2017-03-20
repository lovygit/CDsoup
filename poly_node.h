#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#define IS_FULL(ptr) (!(ptr))
#define COMPARE(A,B) (((A)>(B))? 1:((A)==(B))?0:-1)
typedef struct poly_node *poly_pointer;
struct poly_node {
	double coef;
	int expon;
	poly_pointer link;
};
poly_pointer avail=NULL;
void attach(double coefficient, int exponent, poly_pointer *ptr)
{
	poly_pointer temp;
	temp= (poly_pointer)malloc(sizeof(struct poly_node));
	if (IS_FULL(temp)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}
poly_pointer add(poly_pointer a, poly_pointer b)
{
	void attach(double, int, poly_pointer*);
	double sum;
	poly_pointer front, rear, temp;
	rear = (poly_pointer)malloc(sizeof(struct poly_node));
	if (IS_FULL(rear)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	front = rear;
	while (a&&b) {
		switch (COMPARE(a->expon, b->expon)) {
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if(sum)attach(sum, a->expon , &rear);
			a = a->link;
			b = b->link;
			break;
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		}
	}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = front; front = front->link; free(temp);
	return front;
}
poly_pointer minus(poly_pointer a, poly_pointer b)
{
	poly_pointer front, rear, temp;
	rear = (poly_pointer)malloc(sizeof(struct poly_node));
	if (IS_FULL(rear)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	front = rear;
	while (a&&b) {
		switch (COMPARE(a->expon, b->expon)) {
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		case 0:
			attach(a->coef - b->coef, a->expon , &rear);
			a = a->link;
			b = b->link;
			break;
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		}
	}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(-(b->coef), b->expon, &rear);
	rear->link = NULL;
	temp = front; front = front->link; free(temp);
	return front;
}
poly_pointer multiply(poly_pointer a, poly_pointer b)
{
	poly_pointer front, rear, temp;
	poly_pointer b_head = b;
	rear = (poly_pointer)malloc(sizeof(struct poly_node));
	if (IS_FULL(rear)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	front = rear;
	while (a) {
		b_head = b;
		while (b_head) {
			attach(a->coef*b_head->coef, b_head->expon+a->expon, &rear);
			b_head = b_head->link;
			}
		a = a->link;
	}
	rear->link = NULL;
	temp = front; front = front->link; free(temp);
	return front;
}
poly_pointer simplify(poly_pointer a)
{
	poly_pointer temp1, temp2;
	temp1 = a;
	int expon;
	while (temp1) {
		expon = temp1->expon;
		temp2 = temp1;
		while (temp2&&temp2->link) {
			if (temp2->link->expon == expon) {
				temp1->coef += temp2->link->coef;
				temp2->link = temp2->link->link;
			}
			temp2 = temp2->link;
		}
		temp1 = temp1->link;
	}
	return a;
}
int nodes(poly_pointer a)
{
	int count = 0;
	while (a) {
		count++;
		a = a->link;
	}
	return count;
}
poly_pointer max_pointer(poly_pointer a)
{
	int max = a->expon;
	poly_pointer temp= a;
	while (a) {
		if (a->expon> max) {
			max = a->expon;
			temp = a;
		}
		a = a->link;
	}
	return temp;
}
poly_pointer min_pointer(poly_pointer a)
{
	int min_expon = a->expon;
	poly_pointer min_pointer = a;
	while (a) {
		if (a->expon<min_expon) {
			min_expon = a->expon;
			min_pointer = a;
		}
		a = a->link;
	}
	return min_pointer;
}
poly_pointer sort(poly_pointer a)
{
	poly_pointer rear= (poly_pointer)malloc(sizeof(struct poly_node));
	poly_pointer front = rear,temp,erase;
	int amount = nodes(a);
	int i = 0,record=min_pointer(a)->expon-1;
	int min=max_pointer(a)->expon;
	poly_pointer min_pointer = max_pointer(a);
	while (i != amount) {
		temp = a;
		min = max_pointer(a)->expon;
		min_pointer = max_pointer(a);
		while (temp) {
			if (temp->expon < min&&temp->expon>record) {
				min = temp->expon;
				min_pointer = temp;
			}
			temp = temp->link;
		}
		record = min;
		attach(min_pointer->coef, min_pointer->expon, &rear);
		i++;
	}
	rear->link = NULL;
	erase = front; front = front->link; free(erase);
	return front;
}
double value(poly_pointer head, double val)
{
	printf("let x=%lf,the result is$:", val);
	double count = 0;
	while (head) {
		count += head->coef*pow(val, head->expon);
		head = head->link;
	}
	printf("%lf\n", count);
	return count;
}
void erase(poly_pointer* ptr)
{
	poly_pointer temp;
	while (*ptr) {
		temp = *ptr;
		(*ptr) = (*ptr)->link;
		free(temp);
	}
}
void print_poly_node(poly_pointer ptr)
{
	poly_pointer temp = ptr;
	int i = 1;
	printf("------------------------------------\n");
	while (temp) {
		printf("%3d: coef is %10lf || expon is %5d \n", i++, temp->coef, temp->expon);
		temp = temp->link;
	}
	printf("------------------------------------\n");
}
void print_x(int n)
{
	printf("x");
	for (int i = 0; i < n - 1; i++)
		printf("*x");
}
void print_expression(poly_pointer ptr)
{
	printf("The expression is:\n");
	puts("------------------------");
	ptr = simplify(ptr);
	ptr = sort(ptr);
	while (ptr) {
		printf("%lf*", ptr->coef);
		print_x(ptr->expon);
		ptr = ptr->link;
		printf("+\n");
	}
	puts("------------------------");
}
//circle list
poly_pointer get_node()
{
	poly_pointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else {
		node = (poly_pointer)malloc(sizeof(struct poly_node));
		if (IS_FULL(node)) {
			fprintf(stderr, "The stack is full.\n");
			exit(1);
		}
	}
	return node;
}
void ret_node(poly_pointer ptr)
{
	ptr->link = avail;
	avail = ptr;
}
void cerase(poly_pointer* ptr)
{
	poly_pointer temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}//not a circle list
//end
double atod(char* str, int* position)
{
	double value = 0, value_2 = 0, power = 0, power_2 = 0;
	int i = 0;
	int sign = 1, number_exist = 0;
	if (str[0] == '-') {
		sign = -1;
		i++;
	}
	else if (str[0] == '+') {
		sign = 1;
		i++;
	}
	while (str[i] && isalnum(str[i]) && !isalpha(str[i])) {
		number_exist = 1;
		value = value * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.') {
		number_exist = 1;
		i++;
		while (str[i] && isalnum(str[i]) && !isalpha(str[i])) {
			value_2 = value_2 * 10 + str[i] - '0';
			i++;
		}
		while (value_2 > 1)value_2 /= 10;
	}
	value += value_2;
	value *= sign;
	sign = 1;
	if (toupper(str[i]) == 'E') {
		if (value == 0)
			value = 1;
		number_exist = 1;
		i++;
		if (str[i] == '-') {
			sign = -1;
			i++;
		}
		while (str[i] && isalnum(str[i]) && !isalpha(str[i])) {
			power = power * 10 + str[i] - '0';
			i++;
		}
		if (str[i] == '.') {
			i++;
			while (str[i] && isalnum(str[i]) && !isalpha(str[i])) {
				power_2 = power_2 * 10 + str[i] - '0';
				i++;
			}
			while (power_2 > 1)power_2 /= 10;
		}
		power += power_2;
		power *= sign;
	}
	if (number_exist)
		*position += i;
	return value*pow(10.0, power);
}
void move_space(char* str)
{
	char str_modifier[100] = { '\0' };
	int i = 0;
	for (; i < strlen(str); i++)
		if (!isspace(str[i])) {
			strncat_s(str_modifier, 100, &str[i], 1);
		}
	//printf("str_modifier is %s\n", str_modifier);
	strcpy_s(str, 100, str_modifier);
}
poly_pointer arr_list(char*str)
{
	move_space(str);
	int length = strlen(str);
	int n = 0;
	double ceof;
	int expon;
	poly_pointer rear = (poly_pointer)malloc(sizeof(struct poly_node));
	poly_pointer front = rear, temp;
	while (n < length) {
		expon = 0;
		ceof = atod(str+n, &n);
		while (n<length&&str[n] == '*'&&toupper(str[n + 1]) =='X' ) {
			n += 2;
			expon += 1;
		}
		if(ceof)attach(ceof, expon, &rear);
	}
	rear->link = NULL;
	temp = front; front = front->link; free(temp);
	return front;
}
