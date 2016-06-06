//线段树+标记
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

const int MAXN=8010;

struct Node
{
    int l,r;
    int color;//************************非常巧妙地一个标记
}segTree[MAXN*3];//数组里面再不是放单一的值，而是变成了结构体

int color[MAXN];//记录颜色出现次数
int temp;

//从l到r，根为i
void Build(int i,int l,int r)
{
    segTree[i].l=l;
    segTree[i].r=r;
    segTree[i].color=-1;//-1表示没有颜色

    if(l+1==r)return;//到底了

    int mid=((l+r)>>1);
    Build(i<<1    ,l  ,mid);
    Build((i<<1)|1,mid,r  );
}

//从根i向下插入l到r颜色为c的线段
void insert(int i,int l,int r,int c)
{
    if(l==r)return;//到底了

    if(segTree[i].color==c)return;//子区间颜色相同

    if(l<=segTree[i].l&&r>=segTree[i].r)//盖子区间被完全包含
    {
        segTree[i].color=c;
        return;
    }

    //存在颜色，往下更新
    if(segTree[i].color>=0)
    {
        segTree[i<<1].color=segTree[i].color;
        segTree[(i<<1)|1].color=segTree[i].color;
        segTree[i].color=-2;//表示有多种颜色
    }

    int mid=((segTree[i].l+segTree[i].r)>>1);

    if(r<=mid) //在左子树
		insert(i<<1,l,r,c);

    else if(l>=mid)//在右子树
		insert((i<<1)|1,l,r,c);

    else//左右子树都有
    {
        insert(i<<1,l,mid,c);
        insert((i<<1)|1,mid,r,c);
    }

    segTree[i].color=-2;
}

//从以i为根向下计数
void Count(int i)//统计各颜色的段数
{
    if(segTree[i].color==-1)//该段无色
    {
        temp=-1;
        return;
    }

    if(segTree[i].color!=-2)//该段有确定的颜色
    {
        if(segTree[i].color!=temp)//temp存的是前一段的颜色
        {
            color[segTree[i].color]++;
            temp=segTree[i].color;
        }
        return;
    }

    if(segTree[i].l+1!=segTree[i].r)
    {
        Count(i<<1);
        Count((i<<1)|1);
    }
}

int main()
{
    int n,a,b,c;
    int Max;
    while(scanf("%d",&n)!=EOF)
    {
    	//初始化
        Build(1,0,8000);
        Max=0;

        while(n--)
        {
            scanf("%d%d%d",&a,&b,&c);
            insert(1,a,b,c);
            Max=max(c,Max);
        }

        temp=-1;
        memset(color,0,sizeof(color));
        Count(1);

        for(int i=0;i<=Max;i++)
        {
            if(color[i])//如果该颜色出现了
				printf("%d %d\n",i,color[i]);
        }
        printf("\n");
    }
    return 0;
}

