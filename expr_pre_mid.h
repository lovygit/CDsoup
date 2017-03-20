#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_STACK 100
#define MAX_LEN 100
#define MAX_ITEM 100
int stack[MAX_STACK];
int top = -1;
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, logic_and, logic_or, logic_no, eos, operand
} precedence;
static int isp[] = { 19,0,12,12,13,13,13,5,4,15,0 };
static int icp[] = { 19,20,12,12,13,13,13,5,4,15,0 };
void addStack(int ch)
{
	if (top >= MAX_STACK - 1) {
		printf("The stack is full.\n");
		return;
	}
	stack[++top] = ch;
}
int delStack()
{
	if (top < 0) {
		printf("The stack is empty.\n");
		exit(1);
	}
	return stack[top--];
}
char str[MAX_LEN] = " A/B*C&D+E";
char str_pre[MAX_LEN];
precedence get_token(char* symbol, int* n)
{
	*symbol = str[(*n)--];
	switch (*symbol) {
	case '(':
		return lparen;
	case ')':
		return rparen;
	case '+':
		return plus;
	case '/':
		return divide;
	case '*':
		return times;
	case '%':
		return mod;
	case '-':
		return minus;
	case ' ':
		return eos;
	case '&':
		return logic_and;
	case '|':
		return logic_or;
	case '!':
		return logic_no;
	default:
		return operand;
	}
}
//void getStr()
//{
//	int i = 1;
//	int ch;
//	while (i < MAX_LEN - 1 && (ch = getchar()) && ch != ' '&& ch != '\n'&&ch != EOF) {
//		str[i++] = ch;
//	}
//	str[i] = '\0';
//	str[0] = ' ';
//}
char print_token(precedence token)
{
	switch (token) {
	case lparen:return '(';
	case rparen:return ')';
	case plus:return '+';
	case minus:return '-';
	case times:return '*';
	case divide:return '/';
	case mod:return '%';
	case logic_and:return '&';
	case logic_or:return '|';
	case logic_no:return '!';
	case eos:return ' ';
	}
}
void reverseStr(char* str)
{
	int length = strlen(str);
	int i = 0;
	char temp;
	while (i <= length / 2) {
		temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;
		i++;
	}
}

char* postfix_MidToPre()
{
	top = -1;
	int n = strlen(str) - 1;
	int index = 0;
	precedence token;
	char symbol;
	addStack(eos);
	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
		if (isalnum(symbol)) {
			str_pre[index++] = symbol;
		}
		else if (token == lparen) {
			while (stack[top] != rparen)
				str_pre[index++] = print_token(delStack());
			delStack();
		}
		else {
			while (isp[stack[top]]>icp[token])
				str_pre[index++] = print_token(delStack());
			addStack(token);
		}
	}
	while ((token = delStack()) != eos)
		str_pre[index++] = print_token(token);
	reverseStr(str_pre);
	return str_pre;
}


char stackStr[MAX_ITEM][MAX_LEN];
int top_str = -1;
void initStackStr()
{
	for (int i = 0; i < MAX_ITEM; i++)
		memset(stackStr[i], '\0', sizeof(stackStr[i]));
}
void addStackStr(char* str)
{
	if (top_str >= MAX_ITEM - 1) {
		printf("The stack_str is full.\n");
		return;
	}
	strcpy_s(stackStr[++top_str], MAX_LEN, str);
}
char* delStackStr()
{
	if (top_str < 0) {
		printf("The stack_str is empty.\n");
		exit(1);
	}
	return stackStr[top_str--];
}
char* postfix_preToMid()
{
	top_str = -1;
	initStackStr();
	char buffer1[MAX_LEN], buffer2[MAX_LEN];
	int n = strlen(str_pre) - 1;
	int a, b;
	char temp[2];
	temp[1] = '\0';
	while (n >= 0) {
		if (isalnum(str_pre[n])) {
			temp[0] = str_pre[n];
			addStackStr(temp);
		}
		else {
			strcpy_s(buffer1 + 1, MAX_LEN - 1, delStackStr());
			strcpy_s(buffer2, MAX_LEN, delStackStr());
			buffer1[0] = '(';
			a = strlen(buffer1);
			b = strlen(buffer2);
			buffer1[a] = str_pre[n];
			buffer1[a + 1] = '\0';
			buffer2[b] = ')';
			buffer2[b + 1] = '\0';
			strcat_s(buffer1, MAX_LEN - strlen(buffer1), buffer2);
			addStackStr(buffer1);
		}
		n--;
	}
	return stackStr[0];
}


void test()
{
	puts(postfix_MidToPre());
	puts(postfix_preToMid());
	puts(postfix_MidToPre());
	puts(postfix_preToMid());
}
