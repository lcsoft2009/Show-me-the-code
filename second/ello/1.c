// ����������
// ��ת������
// ���ҵ���������k��Ԫ��(β����Ϊ������0��)��
// ���ҵ������м��㡣
// �ݹ������ӡ������
// �ж�һ���������Ƿ��л���������β��nextָ��ָ���������е�ĳһ����γɻ���
// �ҳ��������л�����ڽ�㣬������β��nextָ��ָ���������е�ĳһ��㡣
// �ж������������Ƿ��ཻ����������������ڹ����Ĳ��֡�
// �������������ཻ�Ľ��㡣
// O(1)ʱ��ɾ����������(��ͷ���)��
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
	Node *c = head, *p = 0, *n = 0;
	while(c){
		n = c->next;
		c->next = p;
		p = c;
		c = n;
	}
}

Node *find_k(Node *head, int k)
{
	Node *p, *q;
	p = q = head;
	int i;
	for(i = 0; q && i < k; q = q->next,++i);
	if(i < k) return NULL;
	while(q){
		q = q->next;
		p = p->next;
	}
	return p;
}

Node *find_middle(Node *head)
{
	Node *p, *q;
	p = q = head;
	while(q && q->next){
		p = p->next;
		q = q->next;
		q = q->next;
	}
	return p;
}

int main()
{
	Node d = {4,NULL},c = {3,&d},b = {2,&c},a = {1,&b};
	// ����������
	printf("%d\n",list_len(&a));
	// ��ת������
	list_display(&a);
	reverse(&a);
	list_display(&d);
	// ���ҵ���������k��Ԫ��(β����Ϊ������0��)
	Node *re = find_k(&d,4);
	if(re){
		printf("%d\n",re->data);
	}else{
		printf("(null)\n");
	}
	// ���ҵ������м���
	re = find_middle(&d);
	if(re){
		printf("%d\n",re->data);
	}else{
		printf("(null)\n");
	}
	return 0;
}

