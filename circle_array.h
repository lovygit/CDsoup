#include<stdio.h>
#include<stdlib.h>
#ifndef CIRCLE_ARRAY
#define CAPACITY 100
int circle[CAPACITY];
int front_circle = 0;
int rear_circle = 0;
int isEmpty_circle()
{
	return front_circle == rear_circle;
}
int isFull_circle()
{
	if (((rear_circle + 1) % CAPACITY) == front_circle)
		return 1;
	return 0;
}
int amount()
{
	if (isEmpty_circle())
		return 0;
	int count = 1;
	int pos = front_circle;
	while (((pos + 1) % CAPACITY) != rear_circle) {
		count++;
		pos = (pos + 1) % CAPACITY;
	}
	return count;
}
int delCircle(int k)
{
	if (k > amount()) {
		fprintf(stderr, "The data doesn't exist.\n");
		exit(1);
	}
	else {
		int pos = front_circle;
		//printf("pos is %d.\n", pos);
		while (k > 1) {
			pos = (pos + 1) % CAPACITY;
			k--;
		}
		while ((pos + 1) % CAPACITY != rear_circle) {
			//printf("pos is %d.\n", pos);
			circle[pos] = circle[(pos + 1) % CAPACITY];
			pos = (pos + 1) % CAPACITY;
		}
		circle[pos] = circle[(pos + 1) % CAPACITY];
		rear_circle = pos;
	}
}
void addCircle(int data, int k)
{
	if (isFull_circle()) {
		fprintf(stderr, "the list is full.\n");
		exit(2);
	}
	else {
		int i;
		for (i = 0; i < CAPACITY; i++) {
			if ((i + 1) % CAPACITY == front_circle)break;
		}
		front_circle = i;
		while (k) {
			circle[i] = circle[(i + 1) % CAPACITY];
			i = (i + 1) % CAPACITY;
			k--;
		}
		circle[i] = data;
	}
}
#endif
