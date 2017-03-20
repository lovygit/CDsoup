#pragma once
#include <stdio.h>
#include<string.h>
#include<math.h>
#define LEN 20
char* format(int a, char* s)
{
	if (a == 2)
		strcpy_s(s, LEN, "Binary");
	else if (a == 8)
		strcpy_s(s, LEN, "Octonary");
	else if (a == 16)
		strcpy_s(s, LEN, "Hexadecimal");
	else if (a == 10)
		strcpy_s(s, LEN, "Decimal");
	else {
		char ch[LEN] = { '\0' };
		while (a > 0) {
			sprintf_s(ch, "%c%s", a % 10 + '0', s, LEN);
			strcpy_s(s, LEN, ch);
		}
	}
	return s;
}
void  numberformat_part1(long a, int format_1)
{
	int number;
	char ch;
	if (a >= format_1)
		numberformat_part1(a / format_1, format_1);
	number = a%format_1;
	if (format_1 == 16) {
		switch (number) {
		case 0:case 1:case 2: case 3: case 4:
		case 5: case 6: case 7:case 8:case 9:
			ch = '0' + number;
			break;
		case 10:
			ch = 'A';
			break;
		case 11:
			ch = 'B';
			break;
		case 12:
			ch = 'C';
			break;
		case 13:
			ch = 'D';
			break;
		case 14:
			ch = 'E';
			break;
		case 15:
			ch = 'F';
			break;
		}
	}
	else {
		ch = number + '0';
	}
	putchar(ch);
}
void numberformat_part2(double number, int format_2)
{
	int a = 0;
	//printf("number is %lf %lf\n", number,(number - (long)number / 1));
	while ((number - (long)number / 1) > pow(10.0, -5)) {
		number *= format_2;
		a = (long)number / 1;
		numberformat_part1(a, format_2);
		number -= a;
	}
}
void numberFormat(char* str, int format_1, int format_2)
{
	char name[LEN] = { "" };
	char* strCopy = str;
	long result_part1 = 0;
	double result_part2 = 0;
	while (*str&&*str != '.') {
		result_part1 = result_part1*format_1 + *str - '0';
		str++;
	}
	if (*str == '.') {
		char* p = str;
		while (*p)
			p++;
		p--;
		for (; p > str; p--) {
			result_part2 = result_part2 / format_1 + *p - '0';
		}
		result_part2 /= format_1;
	}
	/*printf("the result_part2 is %lf\n", result_part2);
	while ((result_part2 -(long)result_part2 / 1 )!=0) {
	result_part2 *= format_1;
	}
	printf("the result_part2 is %lf\n", result_part2);*/
	printf("----------------------------------\n");
	printf("Number: %s\n", strCopy);
	printf("Format_old: %s\n", format(format_1, name));
	printf("Format_new: %s\n", format(format_2, name));
	printf("Result: ");
	numberformat_part1(result_part1, format_2);
	if (result_part2 != 0) {
		putchar('.');
		numberformat_part2(result_part2, format_2);
	}
	printf("\n----------------------------------\n");
}
int getline(char* str, int size)
{
	int i = 0;
	char ch;
	while (i < size - 1 && (ch = getchar()) && ch != '\n') {
		if (ch != ' ') {
			str[i] = ch;
			i++;
		}
	}
	str[i] = '\0';
	return i;
}
void UI()
{
	char str[100] = { '\0' };
	int format1, format2;
	printf("Please input the expression.(F F E)\n");
	scanf_s("%d%d", &format1, &format2);
	while (getline(str, 100) != 0) {
		numberFormat(str, format1, format2);
		printf("Please input the expression.\n");
		scanf_s("%d%d", &format1, &format2);
	}
	printf("Bye!\n");
}