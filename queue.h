#include<stdio.h>
#include<stdlib.h>
#define CAPACITY 100
int queue[CAPACITY];
int front = 0;
int rear = 0;
int isEmpty_queue()
{
	return front == rear;
}
int isFull_queue()
{
	int	i = (rear + 1) % CAPACITY;
	if (i == front)return 1;
	else return 0;
}
void addQueue(int data)
{
	if (!isFull_queue()) {
		rear = (rear + 1) % CAPACITY;
		queue[rear] = data;
	}
	else {
		fprintf(stderr, "queue is full.\n");
		exit(2);
	}
}
int  delQueue()
{
	if (isEmpty_queue()) {
		fprintf(stderr, "queue is empty.\n");
		exit(3);
	}
	else {
		front = (front + 1) % CAPACITY;
		return queue[front];
	}
}