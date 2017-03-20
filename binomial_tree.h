#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef struct heap_node  *node_pointer;
struct heap_node {
	node_pointer parent;
	node_pointer child;
	node_pointer next;
	unsigned int degree;//the amount of its children
};
struct heap {
	node_pointer head;
	node_pointer min;
};
typedef struct heap *heap_pointer;
//初始化二项堆
void heap_init(heap_pointer heap)
{
	heap->head = NULL;
	heap->min = NULL;
}
