#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define lch p<<1
#define rch p<<1|1
typedef long long LL;
const int maxn=2010;
struct EG {
    int bot, top, x, type;
    EG() {}
    EG(int bot, int top, int x, int type):bot(bot), top(top), x(x), type(type) {}
    bool operator<(const EG &rhs) const {
        return (x==rhs.x)?type>rhs.type:x<rhs.x;
    }
}eg[1010][maxn];
int len1[maxn<<2], len2[maxn<<2], len3[maxn<<2], cnt[maxn<<2];
int pos[maxn], m[1010], n;
map<int, int> mp;

void pushup(int p, int l, int r) {
    if (cnt[p]>2) {
        len3[p]=pos[r+1]-pos[l];
        len2[p]=len1[p]=0;
    }else if (cnt[p]==2) {
        len2[p]=pos[r+1]-pos[l];
        if (l!=r)
            len3[p]=len3[lch]+len3[rch]+len1[lch]+len1[rch]+len2[lch]+len2[rch];
        else len3[p]=0;
        len1[p]=0;
        len2[p]-=len3[p];
    }else if (cnt[p]==1) {
        len1[p]=pos[r+1]-pos[l];
        if (l!=r) {
            len3[p]=len2[lch]+len2[rch]+len3[lch]+len3[rch];
            len2[p]=len2[lch]+len2[rch]+len1[lch]+len1[rch];
        }else len3[p]=len2[p]=0;
        len1[p]-=len3[p]+len2[p];
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
    int T, icase=1, sz;
    int ss, tt;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(m, 0, sizeof(m));
        sz=0;
        tt=0, ss=0x3f3f3f3f;
        for (int i=0;i<n;++i) {
            int a, b, c, d, e, f;
            scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
            c+=505, f+=505;
            tt=max(tt, f);
            ss=min(ss, c);
            pos[sz++]=b;
            pos[sz++]=e;
            for (int j=c;j<f;++j) {
                eg[j][m[j]++]=EG(b, e, a, 1);
                eg[j][m[j]++]=EG(b, e, d, -1);
            }
        }
        if (n<3) {
            printf("Case %d: 0\n", icase++);
            continue;
        }
        for (int i=ss;i<tt;++i) sort(eg[i], eg[i]+m[i]);
        sort(pos, pos+sz);
        sz=unique(pos, pos+sz)-pos;
        mp.clear();
        for (int i=0;i<sz;++i) mp[pos[i]]=i;

        LL ans=0;
        for (int i=ss;i<tt;++i) {
            memset(cnt, 0, sizeof(cnt));
            for (int j=0;j<m[i];++j) {
                update(1, 0, sz-1, mp[eg[i][j].bot], mp[eg[i][j].top]-1, eg[i][j].type);
                if (j<m[i]-1) ans+=(LL)len3[1]*(LL)(eg[i][j+1].x-eg[i][j].x);
            }
        }
        printf("Case %d: %lld\n", icase++, ans);
    }
    return 0;
}
