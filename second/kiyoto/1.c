#include<stdio.h>

typedef struct node
{
    char * data;
    struct node *next;
}node_t;

void list_display(node_t *head)
{
      printf ("The list is as follows \n");
    for(;head;head=head->next)
    {
        printf("%s ",head->data);
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
    while(len-i-1!=k)
    {
        n=n->next;
        i++;
       
    }
    return n;
    
}

//find the middle node
node_t *getMidNode( node_t *head)
{
    int len=list_len(head);
    node_t *node=head;
    int i=0;
    while(node->next)
    {
        if(i==len/2)
        {
          return node;
        }
        i++;
        node=node->next;
    }
}

//print list reversely  recursion
void list_display_reserve(node_t *head)
{
    node_t *node=head;
    if(node)
    {
        list_display_reserve(node->next);
        printf("%s ",node->data);
    }
 }

//find the loop in list
int isLoop(node_t *head)
{
    node_t *slow=head;
    node_t *fast=head;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast)
            return 1;       
    }
    return 0;
    
}
//find the entry node of loop list
node_t * getLoopNode(node_t *head)
{
    node_t *slow=head;
    node_t *fast=head;
    int i=0;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast)
        {
            slow=head;
            while (slow!=fast)
            {
                 slow=slow->next;
                 fast=fast->next;
                 i++;
            } 
            printf ("the loop node is located list[%d]\n",i);
            return fast;
        }
    }
    return 0;
}


//is_intersect
int is_intersect(node_t *head1,node_t *head2)
{
    for(;head1->next;head1=head1->next);
   for(;head2->next;head2=head2->next);
   if(head1==head2) 
      return 1;       
   else
    return 0;
}

node_t *get_intersect_node(node_t *head1,node_t *head2)
{
    node_t *node1=head1;
    for(;node1->next;node1=node1->next);
    node1->next=head2;
    
    node_t *slow=head1;
    node_t *fast=head1;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast)
        {
            slow=head1;
             while (slow!=fast)
            {
                 slow=slow->next;
                 fast=fast->next;
            }
             return fast;
        }
    }
    return 0;
}


int main(int argc,const char *argv[])
{
    node_t * head=0,*node=0;
    node_t e={"e",0},d={"d",&e},c={"c",&d},b={"b",&d},a={"a",&b};
   
    head=&a;
    list_display(&a);
    printf ("%d\n",list_len(&a));
    //  head=list_reverse(&a);
    // list_display(head);
    node=getRec_k_th(head,1);
    printf ("Find the reciprocal of the k-th element : %s\n",node->data);
    node=getMidNode(head);
    printf ("The middle node is %s\n",node->data);

    list_display_reserve(head);
    printf("\n");
    node_t f = {"f",0}, g = {"g",&f}, h = {"h",&g}, i = {"i",&h};
	f.next = &g;
    if(isLoop(&i))
        printf("the list  have a loop\n");
    else
            printf("the list does'nt have a loop\n");
    node=getLoopNode(&i);
    printf ("The loop node is %s\n",node->data);

    
    node_t ee = {"1", 0}, dd = {"2", &ee}, cc = {"3", &dd}, bb = {"4", &cc}, aa = {"5", &bb};
	node_t z = {"8",&cc}, y = {"7", &z}, x = {"6", &y};
      if(is_intersect(&aa, &x))
      printf("the two lists are intersect\n");
      if(node=get_intersect_node(&aa,&x))
    printf("the intersect node is %s",node->data);
    return 0;
}

