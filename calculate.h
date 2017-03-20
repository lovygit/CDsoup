#ifndef CALCULATE
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include"stack.h"
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#define MAX_SYMBOL_SIZE 20
#define ALPHA_NUM 26
#define STR_LEN 100
#define BIT_LEN 10
#define TRUE 1
#define FALSE 0
typedef enum {
	lparen,rparen,
	plus,minus,
	times,divide,
	mod,power,
	less_than,more_than,
	no,equal,not_equal,//three
	move_left,move_right,
	and_bit,and_logic,
	not_less,not_more,
	add_auto,minus_auto,or_bit,or_logic,
	eos,operand } precedence;
char* print_token(precedence token)
{
	switch (token) {
	case lparen:return "(";
	case rparen:return ")";
	case plus:return "+";
	case minus:return "-";
	case times:return "*";
	case divide:return "/";
	case mod:return "%";
	case power:return "^";
	case less_than:return "<";
	case more_than:return ">";
	case no:return "!";
	case equal:return "==";
	case not_equal:return "!=";
	case move_left:return "<<";
	case move_right:return ">>";
	case and_bit:return "&";
	case and_logic:return "&&";
	case not_less:return ">=";
	case not_more:return "<=";
	case add_auto:return "++";
	case minus_auto:return "--";
	case or_logic:return "||";
	case or_bit:return "|";
	case eos:return "\0";
	}
}

char expr_pre[MAX_EXPR_SIZE] = {'\0'};
char expr[MAX_EXPR_SIZE] = {'\0'};
char symbols[MAX_SYMBOL_SIZE] = { '\0' };
static int isp[] = { 0,19,12,12,13,13,13,14,10,10,15,9,9,11,11,8,5,10,10,16,16,6,4,0 };//in_stack precedence
static int icp[] = { 20,19,12,12,13,13,13,14,10,10,15,9,9,11,11,8,5,10,10,16,16,6,4,0 };//incoming precedence

char* judge(char* str)
{
	if (strlen(str) == 0)return "\0";
	else {
		if (strlen(str) > 1) {
			static char temp[3] = { '\0' };
			strncpy_s(temp, 3, str, 2);
			if (strstr(temp, "<<") != NULL)return "<<";
			else if (strstr(temp, ">>") != NULL)return ">>";
			else if (strstr(temp, "&&") != NULL)return "&&";
			else if (strstr(temp, "<=") != NULL)return "<=";
			else if (strstr(temp, ">=") != NULL)return ">=";
			else if (strstr(temp, "!=") != NULL)return "!=";
			else if (strstr(temp, "--") != NULL)return "--";
			else if (strstr(temp, "++") != NULL)return "++";
			else if (strstr(temp, "==") != NULL)return "==";
			else if (strstr(temp, "||") != NULL)return "||";
		}
		if (*str == '+')return "+";
		else if (*str == '-')return "-";
		else if (*str == '*')return "*";
		else if (*str == '/')return "/";
		else if (*str == '^')return "^";
		else if (*str == '<')return "<";
		else if (*str == '>')return ">";
		else if (*str == '%')return "%";
		else if (*str == '!')return "!";
		else if (*str == '&')return "&";
		else if (*str == '(')return "(";
		else if (*str == ')')return ")";
		else if (*str == '|')return "|";
		else
			return "\0";
	}
}
double atod(char* str,int* position)
{
	double value = 0, value_2 = 0, power = 0, power_2 = 0;
	int i = 0;
	int sign = 1,number_exist=0;
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
	if(number_exist)
		*position += i;
	return value*pow(10.0, power);
}
char* dtoa(double num,char* str,int len)
{
	//printf("num is %lf\n", num);
	for (int i = 0; i < len; i++) {
		str[i] = '\0';
	}
	long value_1 = (long)num;
	double value_2 = num - value_1;
	double value_2_copy = value_2;
	int i = 0;
	while ((((long)value_2) % 10 != 0 || ((long)value_2) == 0) && i++<10) {
		value_2 *= 10;
	}
	value_2 /= 10;
	value_2 = ((value_2 > 0) ? value_2 : -value_2);
	//printf("value_1 is %lf and value_2 is %lf\n", value_1, value_2);
	char str1[10] = { '\0' }, str2[10] = { '\0' };
	if (value_1 == 0 && num < 0)
		strcat_s(str, len,"-");
	_itoa_s(value_1, str1, 10, 10);
	strcat_s(str, len, str1);
	if (value_2_copy != 0) {
		strcat_s(str, len, ".");
		_itoa_s(value_2, str2, 10, 10);
		strcat_s(str, len, str2);
	}
	return str;
}
int getline(char* str, int n)
{
	int i = 0;
	char ch;
	while (i < n - 1 && (ch = getchar()) && ch != '\n')str[i++] = ch;
	str[i] = '\0';
	return i;
}
precedence get_token(int* n, char* source)
{
	for (int i = 0; i < MAX_SYMBOL_SIZE; i++)
		symbols[i] = '\0';
	while (isspace(source[*n]))(*n)++;
	int n_temp = *n;
	//printf("n_temp is %d\n", n_temp);
	double temp = atod(source+*n, n);
	//printf("n is %d\n", *n);
	//printf("temp is %lf\n", temp);
	if (*n == n_temp) {
		char* temp=judge(source+*n);
		//printf("temp is %s\n", temp);
		*n += strlen(temp);
		if (strstr(temp, "(") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "(", 1);
			return lparen;
		}
		else if (strstr(temp, ")") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, ")", 1);
			return rparen;
		}
		else if (strlen(temp) == 0||*temp=='\n') {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "\0", 1);
			return eos;
		}
		else if (strstr(temp, "<<") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "<<", 2);
			return move_left;
		}
		else if (strstr(temp, ">>") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, ">>", 2);
			return move_right;
		}
		else if (strstr(temp, "&&") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "&&", 2);
			return and_logic;
		}
		else if (strstr(temp, "<=") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "<=", 2);
			return not_more;
		}
		else if (strstr(temp, ">=") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, ">=", 2);
			return not_less;
		}
		else if (strstr(temp, "!=") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "!=", 2);
			return not_equal;
		}
		else if (strstr(temp, "==") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "==", 2);
			return equal;
		}
		else if (strstr(temp, "--") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "--", 2);
			return minus_auto;
		}
		else if (strstr(temp, "++") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "++", 2);
			return add_auto;
		}
		else if (strstr(temp, "||") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "||", 2);
			return or_logic;
		}
		else if (strstr(temp, "+") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "+", 1);
			return plus;
		}
		else if (strstr(temp, "-") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "-", 1);
			return minus;
		}
		else if (strstr(temp, "*") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "*", 1);
			return times;
		}
		else if (strstr(temp, "/") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "/", 1);
			return divide;
		}
		else if (strstr(temp, "^") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "^", 1);
			return power;
		}
		else if (strstr(temp, "%") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "%", 1);
			return mod;
		}
		else if (strstr(temp, "<") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "<", 1);
			return less_than;
		}
		else if (strstr(temp, ">") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, ">", 1);
			return more_than;
		}
		else if (strstr(temp, "!") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "!", 1);
			return no;
		}
		else if (strstr(temp, "&") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "&", 1);
			return and_bit;
		}
		else if (strstr(temp, "|") != NULL) {
			strncpy_s(symbols, MAX_SYMBOL_SIZE, "|", 1);
			return or_bit;
		}
		else {
			fprintf(stderr, "The expression is illegal.\n");
			exit(1);
		}
	}
	else {
		dtoa(temp, symbols, MAX_SYMBOL_SIZE);
		return operand;
	}

}
void postfix(char* source)
{
	for (int i = 0; i < MAX_EXPR_SIZE; i++)
		expr[i] = '\0';
	precedence token;
	int n = 0;
	push_invert(eos);
	for (token = get_token(&n, source); token != eos; token = get_token(&n, source)) {
		//printf("the symbols is %s\n", symbols);
		//printf("the token is %d\n", token);
		if (token == operand) {
			strcat_s(expr, MAX_EXPR_SIZE, symbols);
			strcat_s(expr, MAX_EXPR_SIZE, " ");
			//printf("the expr is %s\n", expr);
		}
		else if (token == rparen) {
			while (stack_invert[top] != lparen) {
				//printf("position 1\n");
				strcat_s(expr, MAX_EXPR_SIZE, print_token(pop_invert()));
				strcat_s(expr, MAX_EXPR_SIZE, " ");
				//printf("the expr is %s\n", expr);
			}
			//printf("position 2\n");
			pop_invert();
		}
		else {
			while (isp[stack_invert[top]] >= icp[token]) {
				//printf("position 3\n");
				strcat_s(expr, MAX_EXPR_SIZE, print_token(pop_invert()));
				strcat_s(expr, MAX_EXPR_SIZE, " ");
				//printf("the expr is %s\n", expr);
			}
			//printf("position 4--\n");
			push_invert(token);
			//for (int i = 1; i <= top; i++)
				//printf("stack_invert[%d] is %d\n", i, stack_invert[i]);
		}
	}
	//printf("the size is %d.\n", size);
	while (stack_invert[top] != eos) {
		//printf("position 5\n");
		strcat_s(expr, MAX_EXPR_SIZE, print_token(pop_invert()));
		//printf("*******\n");
		strcat_s(expr, MAX_EXPR_SIZE, " ");
		//printf("the expr is %s\n", expr);
	}
	strcat_s(expr, MAX_EXPR_SIZE, "\n");
}


void move_space(char* str)
{
	char str_modifier[100] = { '\0' };
	int i = 0;
	for (; i < strlen(str); i++)
		if (!isspace(str[i])) {
			strncat_s(str_modifier, 100-strlen(str_modifier), &str[i], 1);
		}
	//printf("str_modifier is %s\n", str_modifier);
	strcpy_s(str, 100, str_modifier);
}
int include_plus_or_minus(char* str)
{

	int i = 0;
	for (; i < strlen(str) - 1; i++) {
		if (str[i] == '+' || str[i] == '-') {
			if (i > 0) {
				if ((isalnum(str[i - 1]) && !isalpha(str[i - 1]) &&
					isalnum(str[i + 1]) && !isalpha(str[i + 1])))
					return i;
				if (i > 1) {
					if (((str[i - 1] == '-'&&str[i - 2] == '-') || (str[i - 1] == '+'&&str[i - 2] == '+') &&
						isalnum(str[i + 1]) && !isalpha(str[i + 1])))
						return i;
				}
			}
		}
	}
	return -1;
}
void modifier_str(char* str)
{
	move_space(str);
	char str_new[100] = { '\0' };
	int i = 0;
	int exist = include_plus_or_minus(str);
	//printf("exist is %d\n", exist);
	while (exist != -1) {
		for (; i < strlen(str_new); i++)
			str_new[i] = '\0';
		strncat_s(str_new, 100, str, exist);
		strncat_s(str_new, 100, " ", 1);
		strncat_s(str_new, 100, &str[exist], 1);
		strncat_s(str_new, 100, " ", 1);
		strncat_s(str_new, 100, &str[exist + 1], strlen(str) - exist);
		strcpy_s(str, 100, str_new);
		//printf("str is %s\n", str);
		exist = include_plus_or_minus(str);
		//printf("exist is %d\n", exist);
	}
}
double eval()
{
	precedence token;
	double op1, op2;
	int n = 0, temp = 0;
	top = -1;
	token = get_token(&n,expr);
	//printf("the expr is %s\n", expr);
	while (token != eos) {
		if (token == operand)
			push_cal(symbols);
		else {
			op2 = atod(pop_cal(), &temp);
			switch (token) {
			case plus:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((op1 + op2), symbols, MAX_SYMBOL_SIZE));
				break;
			case minus:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((op1-op2), symbols, MAX_SYMBOL_SIZE));
				break;
			case times:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((op1 * op2), symbols, MAX_SYMBOL_SIZE));
				break;
			case divide:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((op1 /op2), symbols, MAX_SYMBOL_SIZE));
				break;
			case add_auto:
				push_cal(dtoa((op2+1), symbols, MAX_SYMBOL_SIZE));
				break;
			case power:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((pow(op1,op2)), symbols, MAX_SYMBOL_SIZE));
				break;
			case minus_auto:
				push_cal(dtoa((op2 - 1), symbols, MAX_SYMBOL_SIZE));
				break;
			case no:
				push_cal(dtoa(!op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case more_than:case not_less:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa(op1>op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case less_than:case not_more:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa(op1<op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case move_left:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((int)op1<<(int)op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case move_right:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((int)op1 >> (int)op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case equal:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa(op1==op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case not_equal:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa(op1 != op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case and_bit:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((int)op1&(int)op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case and_logic:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa(op1&&op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case or_logic:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa(op1||op2, symbols, MAX_SYMBOL_SIZE));
				break;
			case or_bit:
				op1 = atod(pop_cal(), &temp);
				push_cal(dtoa((int)op1 |(int) op2, symbols, MAX_SYMBOL_SIZE));
				break;
			}
		}
		token= get_token(&n, expr);
	}
	return atod(pop_cal(),&temp);
}
int visited[ALPHA_NUM+1];
char bits[BIT_LEN];
void initVisitedArray()
{
	for (int i = 0; i < ALPHA_NUM+1; i++)
		visited[i] = FALSE-1;
}
void initVariable(char* str,int visited[])
{
	int cnt = 0;
	while (*str) {
		if (isalpha(*str)) {
			if (visited[tolower(*str) - 'a'] == FALSE - 1) {
				visited[tolower(*str) - 'a'] = *str;
				cnt++;
			}
		}
		str++;
	}
	visited[ALPHA_NUM] = cnt;
}
void getAlphaValue(int* ch)
{
	char chValue = *ch;
	printf("Input the value(0 or 1) of [ %c ]--->", *ch);
	while (!scanf_s("%d",ch)||( *ch != 0 && *ch != 1)){
		printf("ch is %d\n", *ch);
		printf("Input the value(0 or 1) of [ %c ]--->", chValue);
	}
	printf("alpha--[ %c ],value--[ %d ]\n",chValue,*ch);
}
void getValue(int visited[])
{
	for (int i = 0; i < ALPHA_NUM;i++)
		if (visited[i] != FALSE-1) {
			getAlphaValue(visited + i);
		}
}
void createBitsArray(char* bits, int seq, int length)
{
	int pos = 0;
	for (int i = length-1; i >=0; i--) {
		if (seq >= pow(2, i)) {
			bits[pos++] = '1';
			seq -=(int)pow(2, i);
		}
		else
			bits[pos++] = '0';
	}
	for (int i = length; i < BIT_LEN; i++)
		bits[i] = '\0';
}
void setValue_auto(int visited[],int seq)
{
	//createBitsArray(bits, seq, visited[ALPHA_NUM]);
	int i = 0, j = 0;
	for (; i < ALPHA_NUM;i++)
		if (visited[ALPHA_NUM] != FALSE - 1) {
			visited[i] = bits[j++] - '0';
		}
}
void modifier_str_by_value(char* str, int visited[])
{
	while (*str) {
		if (isalpha(*str)) {
			*str = visited[tolower(*str) - 'a']+'0';
		}
		str++;
	}
}
void listTable()
{
	char str[STR_LEN] = { '\0' };
	char strCopy[STR_LEN];
	int result;
	puts("Please input the expression.([enter] to quit)");
	printf("Expr$: (a,b,c...,but [a,A] is illegal.)--->");
	while (getline(str,100)!=0) {
		strcpy_s(strCopy, STR_LEN, str);
		initVisitedArray();
		initVariable(strCopy, visited);
		//getValue(visited);
		printf("              [ VALUE TABLE ]\n");
		printf("----------------------------------------\n\n");
		for (int i = 0; i < ALPHA_NUM; i++)
			if (visited[i] != FALSE - 1)
				printf(" [ %c ] ", visited[i]);
		printf("%5s[ V ]\n"," ");

		for (int i = 0; i < pow(2, visited[ALPHA_NUM]); i++) {
			strcpy_s(str, STR_LEN, strCopy);
			createBitsArray(bits, i, visited[ALPHA_NUM]);
			for (int j = 0; j < visited[ALPHA_NUM]; j++)
				printf(" [ %c ] ", bits[j]);
			setValue_auto(visited, i);
			modifier_str_by_value(str, visited);
			modifier_str(str);
			postfix(str);
			//printf("The expr is %s\n", expr);
			result =(int) eval();
			printf("%5s[ %d ]       (%s)-[ %4d ]"," ",result,bits,i);
			if (result == 1)
				printf("   * * *\n");
			else
				putchar('\n');
		}
		/*puts("---------------------------");
		printf("Result: [ %lf ]\n", eval());
		puts("---------------------------");*/
		printf("----------------------------------------\n");
		printf("Expr$: (a,b,c...,but [a,A] is illegal.)--->");
	}
	puts("GoodBye!");
}
void calExpr()
{
	char str[STR_LEN] = { '\0' };
	puts("Please input the Expr:-->");
	int circle = '\n';
	while (getline(str, STR_LEN)&&circle=='\n') {
		modifier_str(str);
		postfix(str);
		puts("---------------------------\n");
		printf("Result: [ %lf ]\n", eval());
		puts("---------------------------\n");
		puts("Please input the Expr([ENTER] to quit):-->");
		circle = getchar();
	}
	printf("GoodBye.\n");
}
#endif
