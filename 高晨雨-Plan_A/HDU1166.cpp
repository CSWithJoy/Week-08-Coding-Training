//树状数组模板题
#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
#define MAX 50005
int Tree[MAX],len;
int lowbit(int x)
{
	return (-x)&x;
}
int Query(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=Tree[x];
		x-=lowbit(x);
	}
	return ret;
}
void update(int x,int d)
{
	while(x<=len)
	{
		Tree[x]+=d;
		x+=lowbit(x);
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int cas=1;cas<=T;cas++)
	{
		int a;
		scanf("%d",&len);
		memset(Tree,0,sizeof(Tree));
		for(int i=1;i<=len;i++)
		{
			scanf("%d",&a);
			update(i,a);
		}
		char words[10];
		int x,y;
		printf("Case %d:\n",cas);
		while(scanf("%s",words)!=EOF)
		{
			if(words[0]=='Q')
			{
				scanf("%d%d",&x,&y);
				int ans;
				ans=Query(y)-Query(x-1);
				printf("%d\n",ans);
			}
			else if(words[0]=='A')
			{
				scanf("%d%d",&x,&y);
				update(x,y);
			}
			else if(words[0]=='S'){
				scanf("%d%d",&x,&y);
				update(x,-y);
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
