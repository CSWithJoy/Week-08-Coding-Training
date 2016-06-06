#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

#define maxn 11111

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

bool hsh[maxn];
int li[maxn],ri[maxn];
int x[maxn*3];
int col[maxn<<4];
int cnt;

void push(int rt)
{
	if(col[rt]!=-1)
	{
		col[rt<<1]=col[rt<<1|1]=col[rt];
		col[rt]=-1;
	}
}

void updata(int L,int R,int c,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		col[rt]=c;
		return;
	}
	push(rt);
	int m=(l+r)>>1;
	if(L<=m)
		updata(L,R,c,lson);
	if(m<R)
		updata(L,R,c,rson);
}

void query(int l,int r,int rt)
{
	if(col[rt]!=-1)
	{
		if(!hsh[col[rt]])
			cnt++;
		hsh[col[rt]]=true;
		return ;
	}
	if(l==r)return;
	int m=(l+r)>>1;
	query(lson);
	query(rson);
}

int bin(int key,int n,int x[])
{
	int l=0,r=n-1;
	while(l<=r)
	{
		int m=(l+r)>>1;
		if(x[m]==key)
		{
			return m;
		}
		if(x[m]<key)
		{
			l=m+1;
		}
		else
		{
			r=m-1;
		}
	}
	return -1;
}

int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		int nn=0;
		for(int i=0;i<n;i++)
		{
			cin>>li[i]>>ri[i];
			x[nn++]=li[i];
			x[nn++]=ri[i];
		}

		sort(x,x+nn);

		int m=1;
		for(int i=1;i<nn;i++)
		{
			if(x[i]!=x[i-1])
			{
				x[m++]=x[i];
			}
		}
		for(int i=m-1;i>0;i--)
		{
			if(x[i]!=x[i-1]+1)
			{
				x[m++]=x[i-1]+1;
			}
		}

		sort(x,x+m);

		memset(col,-1,sizeof(col));

		for(int i=0;i<n;i++)
		{
			int l=bin(li[i],m,x);
			int r=bin(ri[i],m,x);
			updata(l,r,i,0,m,1);
		}

		cnt=0;

		memset(hsh,false,sizeof(hsh));

		query(0,m,1);

		cout<<cnt<<endl;
	}
	return 0;
}

/*
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
*/
