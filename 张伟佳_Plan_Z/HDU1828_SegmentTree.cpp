#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch p<<1
#define rch p<<1|1
typedef long long LL;
const int maxn=20010;
const int inf=10000;
int sum[maxn<<2], cnt[maxn<<2], seg[maxn<<2];
int lb[maxn<<2], rb[maxn<<2];
struct EG {
    int top, bottom, x, type;
    EG () {}
    EG (int top, int bottom, int x, int type):top(top), bottom(bottom), x(x), type(type) {}
    bool operator<(const EG &rhs) const {
        return (x==rhs.x)?type>rhs.type:x<rhs.x;
    }
}in[maxn<<2];

void pushUp(int p, int l, int r) {
    if (cnt[p]) {
        sum[p]=r-l+1;
        lb[p]=rb[p]=1;
        seg[p]=2;
    }else if (l==r) lb[p]=rb[p]=seg[p]=sum[p]=0;
    else {
        sum[p]=sum[lch]+sum[rch];
        seg[p]=seg[lch]+seg[rch];
        lb[p]=lb[lch];
        rb[p]=rb[rch];
        if (lb[rch]&&rb[lch]) seg[p]-=2;
    }
}

void change(int p, int l, int r, int x, int y, int c) {
    if (x<=l&&r<=y) {
        cnt[p]+=c;
        pushUp(p, l, r);
        return;
    }
    int mid=(l+r)>>1;
    if (x<=mid) change(lch, l, mid, x, y, c);
    if (mid<y) change(rch, mid+1, r, x, y, c);
    pushUp(p, l, r);
}

int main() {
    int n, m;
    while (scanf("%d", &n)!=EOF) {
        m=0;
        int lm=inf, rm=-inf;
        for (int i=0;i<n;++i) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            lm=min(lm, b);
            rm=max(rm, d);
            in[m++]=EG(d, b, a, 1);
            in[m++]=EG(d, b, c, -1);
        }
        sort(in, in+m);
        memset(cnt, 0, sizeof(cnt));
        int last=0, ans=0;
        for (int i=0;i<m;++i) {
            change(1, lm, rm-1, in[i].bottom, in[i].top-1, in[i].type);
            if (last<sum[1]) ans+=sum[1]-last;
            else ans+=last-sum[1];
            if (i<m-1) ans+=(in[i+1].x-in[i].x)*seg[1];
            last=sum[1];
        }
        printf("%d\n", ans);
    }
    return 0;
}
