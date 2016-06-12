//树状数组lazy标记的运用&&离散化
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
#define MAX 10010
int lisan[MAX*2],Hash[10000005];

struct data
{
	int l,r;
}posters[MAX];

struct Node
{
	int l,r;
	bool lazy;
}Tree[MAX*8];

void build(int p,int l,int r)
{
	Tree[p].l=l;
	Tree[p].r=r;
	Tree[p].lazy=false;
	if(l==r) {return;}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}

int Find(int p,int l,int r)
{
	if(Tree[p].lazy) return false;
	if(Tree[p].l==l&&Tree[p].r==r)
	{
		Tree[p].lazy=true;
		return true;
	}
	bool resule;
	int mid=(Tree[p].l+Tree[p].r)>>1;
	if(r<=mid) resule=Find(p<<1,l,r);
	else if(l>mid) resule=Find(p<<1|1,l,r);
	else{
		bool r1=Find(p<<1,l,mid);
		bool r2=Find(p<<1|1,mid+1,r);
		resule=r1||r2;
	}
	if(Tree[p<<1].lazy&&Tree[p<<1|1].lazy) Tree[p].lazy=true;
	return resule;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		int cnt=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&posters[i].l,&posters[i].r);
			lisan[cnt++]=posters[i].l;
			lisan[cnt++]=posters[i].r;
		}
		//离散化
		sort(lisan,lisan+cnt);
		cnt=unique(lisan,lisan+cnt)-lisan;//去重
		for(int i=0;i<cnt;i++)
		{
			Hash[lisan[i]]=i;
		}
		build(1,0,cnt-1);
		int ans=0;
		for(int i=n-1;i>=0;i--)
		{
			if(Find(1,Hash[posters[i].l],Hash[posters[i].r]))
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
