#include<stdio.h>

typedef struct node
{
    char * data;
    struct node *next;
}node_t;

void list_display(node_t *head)
{
    for(;head;head=head->next)
    {
        printf ("%s ",head->data);
    }
    printf ("\n");
}

//the lenth of list
int list_len(node_t *head)
{
    int i=0;
    for(i=0;head;head=head->next,i++);
    return i;
}

//reverse the list
node_t * list_reverse(node_t *head)
{
    node_t *c=0,*p=0,*t=head;
    
    while(t)
    {
        c=t;
        t=t->next;
        c->next=p;
        p=c;
    }
    return c;
}

//Find the reciprocal of the k-th element
node_t * getRec_k_th(node_t *head,int k)
{
    node_t *n=head;
    int i=0;
    int len=list_len(head);
    if(k<0||k>len-1)
        return 0;
    while(list_len(head)-i-1!=k)
    {
        n=n->next;
        i++;
       
    }
    return n;
    
}

//find the middle node
node_t *getMidNode(node_t *head)
{
    node_t *node;
}
int main(int argc,const char *argv[])
{
    node_t * head=0,*node=0;
    node_t d={"d",0},c={"c",&d},b={"b",&c},a={"a",&b};
    head=&a;
    list_display(&a);
    printf ("%d\n",list_len(&a));
    //  head=list_reverse(&a);
    list_display(head);
    node=getRec_k_th(head,3);
    printf ("%s\n",node->data);
    return 0;
}

