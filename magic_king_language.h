#pragma once
#define MAX 100
int stack[MAX];
int top = -1;
void push(int item) {
	stack[++top] = item;
}
int pop() {
	return stack[top--];
}
void translate(char* str) {
	void translate_();
	while (*str) {
		push(*str);
		translate_();
		str++;
	}
	for (int i = 0; i <= top; i++)
		printf("%c", stack[i]);
	printf("\n");
}
void translate_() {
	char ch;
	ch = pop();
	if (ch == 'A') {
		push('s');
		push('a');
		push('e');
	}
	else if (ch == 'B') {
		push('t');
		push('A');
		translate_();
		push('d');
		push('A');
		translate_();
	}
	else if (ch == ')') {
		char temp[MAX];
		int pos = 0;
		while (stack[top] != '(') {
			temp[pos++] = pop();
		}
		pop();
		char firstChar = temp[pos - 1];
		for (int i = 0; i < pos - 1; i++) {
			push(firstChar);
			push(temp[i]);
			if (temp[i] == 'B' || temp[i] == 'A')
				translate_();
		}
		push(firstChar);
	}
	else {
		push(ch);
	}
}
