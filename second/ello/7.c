/*************************************************************************
	> File Name: 7_ello.c
	> Author: ello
	> Mail: god_mode@yeah.net
	> Created Time: 2013年03月14日 23时26分13秒 CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_NUM 256

typedef struct _Stack{
	int array[MAX_NUM];
	int top;
}Stack;

Stack *createStack()
{
	Stack *stack = (Stack*)malloc(sizeof(Stack));
	stack->top = -1;
}

int isFull(Stack *stack)
{
	assert(stack);
	return stack->top == (MAX_NUM - 1);
}

int isEmpty(Stack *stack)
{
	assert(stack);
	return stack->top == -1;
}

void push(Stack* stack, int data)
{
	assert(stack);
	if(isFull(stack)) return;
	stack->array[++stack->top] = data;
}

int pop(Stack *stack)
{
	assert(stack);
	if(isEmpty(stack)) return -1;
	return stack->array[stack->top--];
}

int top(Stack *stack)
{
	assert(stack);
	if(isEmpty(stack)) return -1;
	return stack->array[stack->top];
}

int judge(int array[],int len)
{
	int A = 1;
	int i = 0;
	Stack *stack = createStack();
	while (len >= A || top(stack) == array[i]) {
		if(top(stack) == array[i]){
			++i;
			pop(stack);
		}else if (A == array[i]) {
			++A;
			++i;
		}else{
			push(stack,A);
			++A;
		}
	}
	if(isEmpty(stack)){
		return 1;
	}else{
		return 0;
	}
}

int main()
{
	int len = 0;
	int array[MAX_NUM] = {0};
	scanf("%d",&len);
	int i = 0;
	for(i = 0;i < len;++i){
		scanf("%d",&array[i]);
	}
	if(judge(array,len)){
		printf("Yes\n");
	}else{
		printf("No\n");
	}

	return 0;
}
