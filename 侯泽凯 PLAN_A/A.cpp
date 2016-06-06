//边放边存
#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int n;
int tree[50010];

void add(int i,int x)
{
	while(i<=n)
	{
		tree[i]+=x;
		i+=(i&-i);
	}
}

int sum(int i)
{
	if(i==0)
		return 0;
	int s=0;
	while(i>0)
	{
		s+=tree[i];
		i-=(i&-i);
	}
	return s;
}

int main()
{
	int t;
	cin>>t;
	for(int z=1;z<=t;z++)
	{
		memset(tree,0,sizeof(tree));

		printf("Case %d:\n",z);

		int pos;
		int val;
		int s,e;
		int temp;
		cin>>n;

		for(int i=1;i<=n;i++)
		{
			scanf("%d",&temp);
			add(i,temp);
		}

		string op;
		while(cin>>op)
		{
			if(op=="End")break;

			if(op=="Add")
			{
				scanf("%d%d",&pos,&val);
				add(pos,val);
			}

			else if(op=="Sub")
			{
				scanf("%d%d",&pos,&val);
				add(pos,val*(-1));
			}

			else if(op=="Query")
			{
				scanf("%d%d",&s,&e);
				cout<<sum(e)-sum(s-1)<<endl;
			}
		}
	}
	return 0;
}
