/*
 *有0，1，...,n-1这n个数排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数。求出这个圆圈里剩下的最后一个数字。（用循环链表实现之后，再考虑有木有空间复杂度为O(1)的算法）
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int data;
	struct _Node *next;
}Node;

typedef struct _List{
	Node *head;
}List;

void insert_after_pos(List *list,Node *pos,int data)
{
	if(NULL == list) return;
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	if(NULL == pos){
		newNode->next = list->head;
		list->head = newNode;
	}else{
		newNode->next = pos->next;
		pos->next = newNode;
	}
}

void insert_tail(List *list,int data)
{
	if(NULL == list) return;
	Node *pos = list->head;
	if(NULL != pos){
		while(NULL != pos->next){
			pos = pos->next;
		}
	}
	insert_after_pos(list,pos,data);
}

int main()
{
	
	return 0;
}
