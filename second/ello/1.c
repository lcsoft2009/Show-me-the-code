// 计算链表长度
// 反转单链表。
// 查找单链表倒数第k个元素(尾结点记为倒数第0个)。
// 查找单链表中间结点。
// 递归逆向打印单链表。
// 判断一个单链表是否有环，即链表尾的next指针指向了链表中的某一结点形成环。
// 找出单链表中环的入口结点，即链表尾的next指针指向了链表中的某一结点。
// 判断两个单链表是否相交，即两个单链表存在公共的部分。
// 找两个单链表相交的交点。
// O(1)时间删除单链表结点(无头结点)。
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct _Node{
    int data; 
    struct _Node *next;
}Node;

typedef Node List;

void list_display(Node *head)
{
    for (; head; head = head->next){
        printf("%d ", head->data);
	}
    printf("\n");
}

int list_len(Node *head)
{
	int len;
	for(len = 0; head; len++,head = head->next);
	return len;
}

void reverse(Node *head)
{

}

int main()
{
	Node d = {4,NULL},c = {3,&d},b = {2,&c},a = {1,&b};
	//计算链表长度
	printf("%d\n",list_len(&a));
	reverse(&a);
	list_display(&d);
	return 0;
}

