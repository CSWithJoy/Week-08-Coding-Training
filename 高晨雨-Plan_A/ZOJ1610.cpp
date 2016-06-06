//线段树&&lazy标记
#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAX 8010
int color[MAX];
struct node
{
	int l,r;
	int color;
}Tree[MAX*3];
void build(int p,int l,int r)
{
	Tree[p].l=l;
	Tree[p].r=r;
	Tree[p].color=-1;
	if(l+1==r) return;
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid,r);
}
void Insert(int p,int l,int r,int c)
{
	if(l==r) return;
	if(Tree[p].color==c) return;
	if(Tree[p].l>=l &&  Tree[p].r<=r)
	{
		Tree[p].color=c;
		return ;
	}
	if(Tree[p].color>=0)
	{
		Tree[p<<1].color=Tree[p].color;
		Tree[p<<1|1].color=Tree[p].color;
		Tree[p].color=-2;
	}
	int mid=(Tree[p].l+Tree[p].r)>>1;
	if(r<=mid) Insert(p<<1,l,r,c);
	else if(l>=mid) Insert(p<<1|1,l,r,c);
	else
	{
		Insert(p<<1,l,mid,c);
		Insert(p<<1|1,mid,r,c);
	}
	Tree[p].color=-2;
}
int tmp=0;
void Query(int p)
{
	if(Tree[p].color==-1)
	{
		tmp=-1;
		return;
	}
	if(Tree[p].color!=-2)
	{
		if(Tree[p].color!=tmp)
		{
			color[Tree[p].color]++;
			tmp=Tree[p].color;
		}
		return;
	}
	if(Tree[p].l+1!=Tree[p].r)
	{
		Query(p<<1);
		Query(p<<1|1);
	}
}
int main()
{
	int n,a,b,c;
	int num;
	while(scanf("%d",&n)!=EOF)
	{
		num=0;
		build(1,0,8000);
		while(n--)
		{
			scanf("%d%d%d",&a,&b,&c);
			Insert(1,a,b,c);
			if(c>num) num=c;
		}
		tmp=-1;
		memset(color,0,sizeof(color));
		Query(1);
		for(int i=0;i<=num;i++)
		{
			if(color[i]) printf("%d %d\n",i,color[i]);
		}
		printf("\n");
	}
	return 0;
}
