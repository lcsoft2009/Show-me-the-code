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

}

int main()
{
	Node d = {4,NULL},c = {3,&d},b = {2,&c},a = {1,&b};
	//����������
	printf("%d\n",list_len(&a));
	reverse(&a);
	list_display(&d);
	return 0;
}

