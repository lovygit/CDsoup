#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 24
#define IS_FULL(ptr) (!(ptr))
#define FALSE 0
#define TRUE 1
typedef struct node* node_pointer;
struct node{
	int data;
	node_pointer link;
};
void equal()
{
	short int out[MAX_SIZE];
	node_pointer seq[MAX_SIZE];
	node_pointer x, y, top;
	int i, j, n;
	printf("Enter the size (<=%d) ", MAX_SIZE);
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		out[i] = TRUE;
		seq[i] = NULL;
	}
	printf("Enter a pair of numbers (-1 -1 to quit): ");
	scanf_s("%d%d", &i, &j);
	while (i >= 0) {
		x = (node_pointer)malloc(sizeof(struct node));
		if (IS_FULL(x)) {
			fprintf(stderr, "The memory is full.\n");
			exit(1);
		}
		x->data = i; x->link = seq[j]; seq[j] = x;
		y = (node_pointer)malloc(sizeof(struct node));
		if (IS_FULL(y)) {
			fprintf(stderr, "The memory is full.\n");
			exit(1);
		}
		y->data = j; y->link = seq[i]; seq[i] = y;
		printf("Enter a pair of numbers (-1 -1 to quit): ");
		scanf_s("%d%d", &i, &j);
	}
	for (int i = 0; i < n; i++) {
		if (out[i]) {
			printf("\nNew class:%5d", i);
			out[i] = FALSE;
			x = seq[i], top = NULL;
			while (TRUE) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j);
						out[j] = FALSE;
						y = x->link;//record the regional next node,not reverse
						x->link = top;//reverse the node
						top = x;//push to stack;
						x = y;//x to the next node;
					}
					else x = x->link;
				}
				if (!top)break;
				x = seq[top->data]; top = top->link;//to the upper node
			}
		}
	}
	putchar('\n');
}