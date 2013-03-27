/*
 *有0，1，...,n-1这n个数排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数。求出这个圆圈里剩下的最后一个数字。（用循环链表实现之后，再考虑有木有空间复杂度为O(1)的算法）
 */
#include <stdio.h>
#include <stdlib.h>

//递归解法
int josephuse1(int n,int m)
{
	if(n == 1)return 0;
	return (josephuse1(n-1,m)+m)%n;
}

//递推解法
long josephuse2(long n,long m){
	int last = 0;
	int i = 0;
    for (i = 2; i <= n; i++)
        last = (last + m) % i; 
    return last;
}

int main()
{
	int n = 0, m = 0;
	while(scanf("%d%d",&n,&m) == 2){
		printf("1:%d\n",josephuse1(n,m));
		printf("2:%d\n",josephuse2(n,m));
	}
	return 0;
}
