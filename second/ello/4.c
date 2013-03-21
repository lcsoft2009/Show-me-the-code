/*************************************************************************
	> File Name: 4.c
	> Author: ellochen
	> Mail: god_mode@yeah.net
	> Created Time: Wed 20 Mar 2013 09:52:07 PM CST
 ************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _Node{
    int Coefficient;//系数
    int Exponent;//指数
    struct _Node *Next;
}Node;
typedef Node List;

#define NUM 1024

List *create_list_from_array(int cfts[], int epts[], int size)
{
	List *list = (List*)malloc(sizeof(List));
	assert(list);
	list->Coefficient = list->Exponent = 0;
	list->Next = NULL;
	int i;
	Node *pos = list;
	for(i = 0;i < size;++i){
		Node *newNode = (Node*)malloc(sizeof(Node));
		assert(newNode);
		newNode->Coefficient = cfts[i];
		newNode->Exponent = epts[i];
		newNode->Next = NULL;
		pos->Next = newNode;
		pos = pos->Next;
	}
	return list;
}

void insert_after_pos(List *list,Node *pos,Node *node)
{
	assert(list && pos && node);
	Node *newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->Coefficient = node->Coefficient;
	newNode->Exponent = node->Exponent;
	newNode->Next = pos->Next;
	pos->Next = newNode;
}

void insert_after_pos2(List *list,Node *pos,int Coefficient,int Exponent)
{
	assert(list && pos);
	Node *newNode = (Node*)malloc(sizeof(Node));
	assert(newNode);
	newNode->Coefficient = Coefficient;
	newNode->Exponent = Exponent;
	newNode->Next = pos->Next;
	pos->Next = newNode;
}

List *create_list()
{
	List *list = (List*)malloc(sizeof(List));
	assert(list);
	list->Coefficient = list->Exponent = 0;
	list->Next = NULL;
	return list;
}

void destory_list(List *list)
{
	assert(list);
	Node *pos = list;
	while(NULL != pos){
		Node *freeNode = pos;
		pos = pos->Next;
		free(freeNode);
	}
}

void printList(List *list)
{
	assert(list);
	Node *pos = list->Next;
	while(NULL != pos){
		if(pos->Coefficient > 0 && pos != list->Next){
			printf("+");
		}else if(0 == pos->Coefficient){
			pos = pos->Next;
			continue;
		}
		printf("%dx^%d",pos->Coefficient,pos->Exponent);
		pos = pos->Next;
	}
	printf("\n");
}

void addition(List *m, List *n,List *result)
{
	assert(m && n && result);
	Node *mPos = m->Next;
	Node *nPos = n->Next;
	Node *rPos = result;
	while(NULL != mPos && NULL != nPos){
		if(mPos->Exponent > nPos->Exponent){
			insert_after_pos(result,rPos,mPos);
			mPos = mPos->Next;
		}else if(mPos->Exponent < nPos->Exponent){
			insert_after_pos(result,rPos,nPos);
			nPos = nPos->Next;
		}else{
			insert_after_pos2(result,rPos,
					mPos->Coefficient + nPos->Coefficient,
					mPos->Exponent);
			mPos = mPos->Next;
			nPos = nPos->Next;
		}
		rPos = rPos->Next;
	}
	while(NULL != mPos){
		insert_after_pos(result,rPos,mPos);
		mPos = mPos->Next;
		rPos = rPos->Next;
	}
	while(NULL != nPos){
		insert_after_pos(result,rPos,nPos);
		nPos = nPos->Next;
		rPos = rPos->Next;
	}
}

void multiplication(List *m, List *n,List *result)
{
    assert(m && n && result);
	Node *mPos = m->Next;
	Node *nPos = n->Next;
	while(NULL != nPos){
		int nCpt = nPos->Coefficient;
		int nEpt = nPos->Exponent;
		List *temp = create_list();
		Node *tPos = temp;
		while(NULL != mPos){
			insert_after_pos2(temp,tPos,
					mPos->Coefficient * nCpt,
					mPos->nEpt + nEpt);
			mPos = mPos->Next;
			tPos = tPos->Next;
		}
		addition(temp,result,result);
		destory_list(temp);
		nPos = nPos->Next;
	}
}

List *getList()
{
    int cfts[NUM] = {0};
	int epts[NUM] = {0};
	int size = 0;
	printf("input size: ");
	scanf("%d",&size);
	printf("input cfts: ");
	int i;
	for(i = 0;i < size;++i){
		scanf("%d",&cfts[i]);
	}
	printf("input epts: ");
	for(i = 0;i < size;++i){
		scanf("%d",&epts[i]);
	}
	printf("output: ");
	List *list = create_list_from_array(cfts,epts,size);
	assert(list);
	printList(list);
	return list;
}

int main()
{
	printf("get first list: \n");
	List *m = getList();
	printf("get econd list: \n");
	List *n = getList();
	printf("addition: ");
	List *result = create_list();
	addition(m,n,result);
	printList(result);
	int pause;
	scanf("%d",&pause);
	return 0;
}
