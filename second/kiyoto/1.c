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

void list_reverse(node_t *head)
{
    node_t *c=0,*p=0,*t=head;
    
    while(t)
    {
        c=t;
        t=t->next;
        c->next=p;
        p=c;
    }
    
}

int main(int argc,const char *argv[])
{
    node_t d={"d",0},c={"c",&d},b={"b",&c},a={"a",&b};
    list_display(&a);
    printf ("%d\n",list_len(&a));
    list_reverse(&a);
    list_display(&d);
    return 0;
}

