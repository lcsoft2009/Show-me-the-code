/*************************************************************************
	> File Name: 8.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: 2013年03月18日 20时16分42秒 CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _Node{
	int value;
	struct _Node *next;
}Node;

typedef struct _Stack{
	Node *head;
}Stack;

typedef struct _Queue{
	Stack *in;
	Stack *out;
}Queue;

Stack *createStack()
{
	Stack * stack = (Stack*)malloc(sizeof(Stack));
	if(NULL == stack) return NULL;
	stack->head = (Node*)malloc(sizeof(Node));
	if(NULL == stack->head) return NULL;
	stack->head->value = 0;
	stack->head->next = NULL;
	return stack;
}

int skIsEmpy(Stack *stack)
{
	if(NULL == stack) return -1;
	return stack->head->next == NULL;
}

void skPush(Stack *stack,int value)
{
	if(NULL == stack || NULL == stack->head) return;
	Node *newNode = (Node*)malloc(sizeof(Node));
	if(NULL == newNode) return;
	newNode->value = value;
	newNode->next = stack->head->next;
	stack->head->next = newNode;
}

int skPop(Stack *stack)
{
	if(NULL == stack || NULL == stack->head) return -1;
	Node *freeNode = stack->head->next;
	if(NULL == freeNode) return -1;
	int reValue = freeNode->value;
	stack->head->next = freeNode->next;
	free(freeNode);
	return reValue;
}

int skTop(Stack *stack)
{
	if(NULL == stack || NULL == stack->head
			|| NULL == stack->head->next || skIsEmpy(stack)) return -1;
	return stack->head->next->value;
}

Queue *createQueue()
{
	Queue *queue = (Queue*)malloc(sizeof(Queue));
	if(NULL == queue) return NULL;
	queue->in = createStack();
	if(NULL == queue->in) return NULL;
	queue->out = createStack();
	if(NULL == queue->out) return NULL;
	return queue;
}

void qePush(Queue *queue,int value)
{
	if(NULL == queue || NULL == queue->in) return;
	skPush(queue->in,value);
}

int qePop(Queue *queue)
{
	if(NULL == queue || NULL == queue->out
			|| NULL == queue->in) return -1;
	if(skIsEmpy(queue->out)){
		while(!skIsEmpy(queue->in)){
			skPush(queue->out,skPop(queue->in));
		}
	}
	return skPop(queue->out);
}

int qeFront(Queue *queue)
{
	if(NULL == queue || NULL == queue->out
			|| NULL == queue->in) return -1;
	if(skIsEmpy(queue->out)){
		while(!skIsEmpy(queue->in)){
			skPush(queue->out,skPop(queue->in));
		}
	}
	return skTop(queue->out);
}

void printStack(Stack *stack)
{
	if(NULL == stack || NULL == stack->head) return;
	Node *pPos = stack->head->next;
	if(NULL == pPos) printf("(nul)");
	while(NULL != pPos){
		printf("%d ",pPos->value);
		pPos = pPos->next;
	}
	printf("\n");
}

void printQueue(Queue *queue)
{
	if(NULL == queue || NULL == queue->in
			|| NULL == queue->out) return;
	printStack(queue->in);
	printStack(queue->out);
}

int main()
{
	Queue *queue = createQueue();
	int i;
	for(i = 0;i < 10;++i){
		qePush(queue,i);
	}
	printQueue(queue);
	for(i = 0;i < 10;++i){
		printf("\n%d\n",qePop(queue));
	}
	return 0;
}
