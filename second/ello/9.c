/*************************************************************************
	> File Name: 9.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: 2013年03月18日 22时49分16秒 CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _Node{
	int value;
	struct _Node *next;
}Node;

typedef struct _Queue{
	Node *front;
	Node *tail;
}Queue;

Queue* init_queue(void)
{
	Queue *queue = (Queue*)malloc(sizeof(Queue));
	assert(queue);
	Node *node = (Node*)malloc(sizeof(Node));
	node->value = 0;
	node->next = NULL;
	queue->tail = queue->front = node;

	return queue;
}

int isEmpty_queue(Queue *queue)
{
	assert(queue);
	return queue->front == queue->tail;
}

int count_queue(Queue *queue)
{
	assert(queue);
	assert(queue->front);
	Node *pos = queue->front->next;
	int num = 0;
	while(NULL != pos){
		pos = pos->next;
		++num;
	}
	return num;
}

void push(Queue *queue,int value)
{
	assert(queue);
	assert(queue->tail);
	Node *newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->value = value;
	newNode->next = NULL;
	queue->tail->next = newNode;
	queue->tail = newNode;
}

int pop(Queue *queue)
{
	assert(queue);
	assert(queue->front);
	if(isEmpty_queue(queue)){
		return -1;
	}
	Node *freeNode = queue->front->next;
	assert(freeNode);
	int reValue = freeNode->value;
	queue->front->next = freeNode->next;
	if(NULL == freeNode->next){
		queue->tail = queue->front;
	}
	free(freeNode);
	return reValue;
}

void print_queue(Queue *queue)
{
	assert(queue);
	Node *pos = queue->front->next;
	while(NULL != pos){
		printf("%d ",pos->value);
		pos = pos->next;
	}
	printf("\n");
}

void destory_queue(Queue *queue)
{
	assert(queue);
	Node *pos = queue->front;
	while(NULL != pos){
		Node *freeNode = pos;
		pos = pos->next;
		free(freeNode);
	}
	free(queue);
}

int main()
{
	int input = 0;
	int i = 0;
	while(scanf("%d",&input) == 1){
		Queue* queue = init_queue();
		assert(queue);
		for(i = 1;i <= input;++i){
			push(queue,i);
		}
		// print_queue(queue);
		while(2 <= count_queue(queue)){
			printf("%d ",pop(queue));
			push(queue,pop(queue));
		}
		if(!isEmpty_queue(queue)){
			printf("%d ",pop(queue));
		}
		// print_queue(queue);
		destory_queue(queue);
		printf("\n");
	}
	system("pause");
	return 0;
}
