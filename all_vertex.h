#pragma once
#include"SOMD.h"
#include<stdio.h>
#include<stdlib.h>
int distance2[MAX_VERTICE][MAX_VERTICE];
//所有定点对之间的最短距离
void allcosts(int cost[][MAX_VERTICE], int n)
{
	int i, j, k;
	for (i = 0; i < MAX_VERTICE; i++)
		for (j = 0; j < MAX_VERTICE; j++)
			distance2[i][j] = cost[i][j];
	for (k = 0; k <=n; k++)
		for (i = 0; i < MAX_VERTICE; i++)
			for (j = 0; j < MAX_VERTICE; j++)
				if (distance2[i][k] + distance2[k][j] < distance2[i][j])
					distance2[i][j] = distance2[i][k] + distance2[k][j];
	printf("-------------------------------\n");
	for (int i = 0; i < MAX_VERTICE; i++) {
		for (int j = 0; j < MAX_VERTICE; j++)
			printf("%5d", distance2[i][j]);
		putchar('\n');
	}
	printf("-------------------------------\n");
}
//传递闭包

