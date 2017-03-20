#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_STRING_SIZE 100
#define MAX_PATTERN_SIZE 100
int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE] = { "mao mao mao le kun" };
char pattern[MAX_PATTERN_SIZE] = { "mao le kun" };
void fail(char* pat)
{
	int n = strlen(pat);
	int i, j;
	failure[0] = -1;
	for (j = 1; j < n; j++) {
		i = failure[j - 1];
		while (pat[j] != pat[i + 1] && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;//meaning the index
		else
			failure[j] = -1;
	}
}
int patch(char* string, char *pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens&&j < lenp) {
		if (string[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0)i++;
		else
			j = failure[j - 1] + 1;
	}
	return ((j == lenp) ? i - lenp : -1);
}