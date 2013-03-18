/*
 *给你两个链表L1和L2，分别编写函数得到L1与L2的交集和并集。
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int data;
	struct _Node *next;
}Node;

typedef struct{
	Node *head;
}List;

List *createList()
{
	List * list = (List*)malloc(sizeof(List));
	list->head = NULL;
	return list;
}

void destoryList(List *list)
{
	Node *pos = list->head;
	while(NULL != pos){
		Node *nextPos = pos->next;
		free(pos);
		pos = nextPos;
	}
	free(list);
}

void insert(List *list, Node *pos, int data)
{
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

void insertTail(List* list, int data)
{
	if(NULL == list) return;
	Node *p = list->head;
	if(NULL != p){
		while(NULL != p->next){
			p = p->next;
		}
	}
	insert(list,p,data);
}

List *getInterSect(List *l1, List *l2)
{
	if(NULL == l1 || NULL == l2) return NULL;
	List *reList = createList();
	Node *p1 = l1->head;
	Node *p2 = l2->head;
	while(NULL != p1 && NULL != p2){
		if(p1->data > p2->data){
			p2 = p2->next;
		}else if(p1->data < p2->data){
			p1 = p1->next;
		}else{
			insertTail(reList,p1->data);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return reList;
}

List *getUnion(List *l1, List *l2)
{
	if(NULL == l1 || NULL == l2) return NULL;
	List *reList = createList();
	Node *p1 = l1->head;
	Node *p2 = l2->head;
	while(NULL != p1 && NULL != p2){
		if(p1->data > p2->data){
			insertTail(reList,p2->data);
			p2 = p2->next;
		}else if(p1->data < p2->data){
			insertTail(reList,p1->data);
			p1 = p1->next;
		}else{
			insertTail(reList,p1->data);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	if(NULL == p1 && NULL != p2){
		while(NULL != p2){
			insertTail(reList,p2->data);
			p2 = p2->next;
		}
	}else if(NULL == p2 && NULL != p1){
		while(NULL != p1){
			insertTail(reList,p1->data);
			p1 = p1->next;
		}
	}
	return reList;
}

void printList(List *list)
{
	if(NULL == list) return;
	Node *p = list->head;
	while(NULL != p){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	List *l1 = createList();
	List *l2 = createList();

	//input l1
	printf("Input l1: \n");
	int temp = 0;
	while(scanf("%d",&temp) == 1){
		insertTail(l1, temp);
	}
	printf("Input l2: \n");
	//input l2
	while(scanf("%d",&temp) == 1){
		insertTail(l2,temp);
	}

	printList(getInterSect(l1,l2));
	printList(getUnion(l1,l2));
	destoryList(l1);
	destoryList(l2);
	return 0;
}
