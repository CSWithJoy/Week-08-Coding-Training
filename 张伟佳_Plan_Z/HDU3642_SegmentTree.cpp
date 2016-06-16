#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int maxn=2010;
typedef long long LL;
#define lch p<<1
#define rch p<<1|1
int cnt[maxn<<2], len1[maxn<<2], len2[maxn<<2], len3[maxn<<2], pos[maxn];
struct EG {
    int top, bot, x, z, type;
    EG () {}
    EG(int bot, int top, int x, int z, int type):
        top(top), bot(bot), x(x), z(z), type(type) {}
    bool operator<(const EG&rhs) const {
        if (z==rhs.z) {
            if (x==rhs.x) return type>rhs.type;
            return x<rhs.x;
        }
        return z<rhs.z;
    }
}seq[1010][maxn];
int n, m[maxn], sz;
map<int, int> mp;

void pushup(int p, int l, int r) {
    //printf("%d %d\n", l, r);
    if (cnt[p]>2) {
        len3[p]=pos[r+1]-pos[l];
        len1[p]=len2[p]=0;
    }else if (cnt[p]==2) {
        len1[p]=0;
        if (l!=r)
            len3[p]=len3[lch]+len3[rch]+len2[lch]+len2[rch]+len1[lch]+len1[rch];
        else len3[p]=0;
        len2[p]=pos[r+1]-pos[l]-len3[p];
    }else if (cnt[p]==1) {
        len1[p]=pos[r+1]-pos[l];
        if (l!=r) {
            len2[p]=len1[lch]+len1[rch];
            len3[p]=len3[lch]+len3[rch]+len2[lch]+len2[rch];
        } else len3[p]=len2[p]=0;
        len1[p]-=len2[p]+len3[p];
    }else {
        len1[p]=len1[lch]+len1[rch];
        len2[p]=len2[lch]+len2[rch];
        len3[p]=len3[lch]+len3[rch];
    }
}

void update(int p, int l, int r, int x, int y, int c) {
    if (x<=l&&r<=y) {
        cnt[p]+=c;
        pushup(p, l, r);
        return;
    }
    int mid=(l+r)>>1;
    if (x<=mid) update(lch, l, mid, x, y, c);
    if (mid<y) update(rch, mid+1, r, x, y, c);
    pushup(p, l, r);
}

int main() {
    int icase=1, T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(m, 0, sizeof(m));
        sz=0;
        int tt=0, bb=maxn;
        for (int i=0;i<n;++i) {
            int a, b, c, d, e, f;
            scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
            c+=505;
            f+=505;
            pos[sz++]=b;
            pos[sz++]=e;
            tt=max(tt, f);
            bb=min(bb, c);
            for (int j=c;j<f;++j) {
                seq[j][m[j]++]=EG(b, e, a, j, 1);
                seq[j][m[j]++]=EG(b, e, d, j, -1);
            }
        }
        sort(pos, pos+sz);
        for (int i=bb;i<tt;++i) {
            sort(seq[i], seq[i]+m[i]);
        }
        sz=unique(pos, pos+sz)-pos;
        mp.clear();
        for (int i=0;i<sz;++i) mp[pos[i]]=i;

        LL ans=0;
        for (int i=bb;i<tt;++i) {
            memset(cnt, 0, sizeof(cnt));
            //printf("==%d\n", i);
            for (int j=0;j<m[i];++j) {
                update(1, 0, sz-1, mp[seq[i][j].bot], mp[seq[i][j].top]-1, seq[i][j].type);
                //printf("%d %d %d %d\n", seq[i][j].type, len1[1], len2[1], len3[1]);
                if (j<m[i]-1) ans+=(LL)(seq[i][j+1].x-seq[i][j].x)*(LL)len3[1];
            }
        }
        printf("Case %d: %lld\n", icase++, ans);
    }
    return 0;
}
/*
10
4
1 1 0 5 5 1
2 2 0 6 6 1
3 3 0 7 7 1
4 4 0 8 8 1
4
1 1 1 5 5 5
2 2 2 6 6 6
3 3 3 7 7 7
4 4 4 8 8 8
*/
