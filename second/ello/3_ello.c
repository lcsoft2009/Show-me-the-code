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
	int size;
}List;

List *createList()
{
	List *list = (List*)malloc(sizeof(List));
	list->head = NULL;
	list->size = 0;
	return list;
}

void destoryList(List *list)
{
	Node *pos = list->head;
	do{
		Node *nextPos = pos->next;
		free(pos);
		pos = nextPos;
	}while(list->head != pos);
	free(list);
}

void insert_after_pos(List *list,Node *pos,int data)
{
	if(NULL == list) return;
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	if(0 == list->size){
		newNode->next = newNode;
		list->head = newNode;
	}else{
		newNode->next = pos->next;
		pos->next = newNode;
	}
	list->size++;
}

void insert_tail(List *list,int data)
{
	if(NULL == list) return;
	Node *pos = list->head;
	if(0 != list->size){
		do{
			pos = pos->next;
		}while(list->head != pos->next);
	}
	insert_after_pos(list,pos,data);
}

void delete_after_pos(List *list,Node *pos)
{
	if(NULL == list || NULL == pos) return ;
	if(0 == list->size) return ;
	if(pos->next == pos){
		free(pos);
		list->head = NULL;
	}else{
		Node *oldNode = pos->next;
		pos->next = oldNode->next;
		if(oldNode == list->head){
			list->head = oldNode->next;
		}
		free(oldNode);
	}
	list->size--;
}

void printList(List *list)
{
	if(NULL == list) return ;
	Node *pos = list->head;
	if(NULL == pos) return ;
	do{
		printf("%d ",pos->data);
		pos = pos->next;
	}while(list->head != pos);
	printf("\n");
//	printf("%d %d %d\n",pos->data,pos->next->data,pos->next->next->data);
}

int josephuse(int n, int m)
{
	List *list = createList();
	int step = 0;
	int i = 0;
	for(i = 0;i < n;++i){
		insert_tail(list,i);
	}
//	printList(list);
	Node *pos = NULL;
	Node *startPos = list->head;
	while(1 < list->size){
		pos = startPos;
		for(i = 0;i < m-2;++i){
			pos = pos->next;
		}
		startPos = pos->next->next;
		printf("del %d\n",pos->next->data);
		delete_after_pos(list,pos);
	}
	return list->head->data;
}

int main()
{
	int n = 0, m = 0;
	while(scanf("%d%d",&n,&m) == 2){
		printf("%d\n",josephuse(n,m));
	}
	return 0;
}
