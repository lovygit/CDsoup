#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define K 16
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 10
typedef struct {
	int key;
	int run;
}element;
typedef struct {
	element data;
	int loser;
}tree_node;
tree_node tree[K+1];
FILE* open_input(char* fileName)
{
	FILE* ptr;
	fopen_s(&ptr, fileName, "rb");
	if (!ptr) {
		fprintf(stderr, "File %s cannot be opened for input\n", fileName);
		exit(1);
	}
	return ptr;
}

void adjust(tree_node tree[],int pos)
{
	int loser;
	int winner = pos;
	int parent = (K + pos-1) / 2;
	while (parent>0) {
		loser = tree[parent].loser;
		if (tree[loser].data.run < tree[winner].data.run ||
			(tree[loser].data.run == tree[winner].data.run&&
				tree[loser].data.key < tree[winner].data.key)) {
			//exchange winner and loser.
			tree[parent].loser = winner;
			winner = loser;
		}
		parent /= 2;
	}
	tree[0].loser = winner;
}
void run_generation(char* readFileName, char* writeFileName)
{
	int amount = 1;
	int i,cnt=0,current_run=2;
	FILE *in, *out;
	in = open_input(readFileName);
	fopen_s(&out, writeFileName, "wb");

	for (i = 1; i < K+1; i++) {
		if (fread(&tree[i], sizeof(element), 1, in)) {
			tree[i].data.run = 1;
		}
		else
			break;
	}
	if (i != K+1) {
		for (int j = K; j >=i; j--) {
			tree[j].data.key = INT_MAX;
			tree[j].data.run = INT_MAX;
		}
	}
	tree[0].data.run =INT_MIN;
	for (int j = K; j > 0; j--)
		adjust(tree, j);
	while (TRUE) {

		fwrite(&tree[tree[0].loser], sizeof(element), 1, out);
		if(fread(&tree[tree[0].loser], sizeof(element), 1, in)){
			cnt++;
			if ((cnt-1)%K == 0&&cnt>1)
				current_run++;
			tree[tree[0].loser].data.run = current_run;
			adjust(tree, tree[0].loser);
		}
		else {
			while (tree[tree[0].loser].data.run !=INT_MAX) {
				tree[tree[0].loser].data.run = INT_MAX;
				adjust(tree, tree[0].loser);
				if (tree[tree[0].loser].data.run != INT_MAX)//for the last time
					fwrite(&tree[tree[0].loser], sizeof(element), 1, out);
			}
			fclose(in);
			fclose(out);
			return;
		}
	}
}
void test()
{
	srand(time(0));
	FILE* ptr;
	element temp;


	fopen_s(&ptr, "f:/documents/kmerge", "wb");
	for (int i = 0; i < MAX_SIZE; i++) {
		temp.key = rand() %(2* MAX_SIZE);
		temp.run = 0;
		fwrite(&temp, sizeof(element), 1, ptr);
	}
	fclose(ptr);

	int i = 1;
	fopen_s(&ptr, "f:/documents/kmerge", "rb");
	while (fread(&temp, sizeof(element), 1, ptr)) {
		printf("[ %d ]", temp.key);
		if (i % 16 == 0)
			putchar('\n');
		i++;
	}
	putchar('\n');
	fclose(ptr);

	run_generation("f:/documents/kmerge", "f:/documents/kmerge_out");
	i = 1;
	fopen_s(&ptr, "f:/documents/kmerge_out", "rb");
	while (fread(&temp, sizeof(element), 1, ptr)) {
		printf("[ %d ]", temp.key);
		if (i % 16 == 0)
			putchar('\n');
		i++;
	}
	putchar('\n');
	fclose(ptr);
}