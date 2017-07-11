#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ARRAY1_LEN 5
#define ARRAY2_LEN 5
#define ARRAY_LEN (ARRAY1_LEN+ARRAY2_LEN)
#define MATRIX_LEN 4
//question one
int* unionWithSeq(int* array,int* array1, int length1, int* array2, int length2) {
	int i = 0, j = 0,k=0;
	while (i < length1&&j < length2) {
		if (array1[i] <= array2[j]) {
			array[k++] = array1[i++];
		}
		else
			array[k++] = array2[j++];
	}
	while (i < length1)
		array[k++] = array1[i++];
	while (j < length2)
		array[k++]=array2[j++];
	return array;
}
void test_question1() {
	int array1[ARRAY1_LEN] = { 1,3,6,9,10 };
	int array2[ARRAY2_LEN] = { 2,4,6,9,13 };
	int array[ARRAY_LEN];
	unionWithSeq(array, array1, ARRAY1_LEN, array2, ARRAY2_LEN);
	printf("The union array is:\n");
	for (int i = 0; i < ARRAY_LEN; i++)
		printf("%5d", array[i]);
	printf("\n");
	system("pause");
}
//question two
int graphMatrix[MATRIX_LEN][MATRIX_LEN] = {
	{0,1,1,0},
	{1,0,1,0},
	{1,1,0,1},
	{1,0,0,0},
};
int getMax_In_Number(int graphMatrix[][MATRIX_LEN]) {
	int in_count = 0,max_count=0;
	int number = 0;
	for (int i = 0; i < MATRIX_LEN; i++) {
		in_count = 0;
		for (int j = 0; j < MATRIX_LEN; j++) {
			if(graphMatrix[j][i]==1)
				in_count++;
		}
		if (in_count > max_count) {
			max_count = in_count;
			number = i;
		}
	}
	return number;
}
int getMax_Out_Number(int graphMatrix[][MATRIX_LEN]) {
	int in_count = 0, max_count = 0;
	int number = 0;
	for (int i = 0; i <MATRIX_LEN; i++) {
		in_count = 0;
		for (int j = 0; j <MATRIX_LEN; j++) {
			if (graphMatrix[i][j] == 1)
				in_count++;
		}
		if (in_count > max_count) {
			max_count = in_count;
			number = i;
		}
	}
	return number;
}
void test_question2() {
	printf("the max in number is :%5d\n", getMax_In_Number(graphMatrix));//出度
	printf("the max out number is :%5d\n", getMax_Out_Number(graphMatrix));//入度
	system("pause");
}
