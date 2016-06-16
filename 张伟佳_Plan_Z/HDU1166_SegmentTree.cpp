#include <cstdio>
#include <cstring>
#define lch p<<1
#define rch p<<1|1
using namespace std;
const int maxn=50000;
int st[maxn<<2];

void build(int p, int l, int r) {
    if (l==r) {
        scanf("%d", &st[p]);
        return;
    }
    int mid=(l+r)>>1;
    build(lch, l, mid);
    build(rch, mid+1, r);
    st[p]=st[lch]+st[rch];
}

void change(int p, int l, int r, int x, int y) {
    if (l==r) {
        st[p]+=y;
        return;
    }
    int mid=(l+r)>>1;
    if (x<=mid) change(lch, l, mid, x, y);
    else change(rch, mid+1, r, x, y);
    st[p]=st[lch]+st[rch];
}

int query(int p, int l, int r, int x, int y) {
    if (x<=l&&r<=y) {
        return st[p];
    }
    int ans=0, mid=(l+r)>>1;
    if (x<=mid) ans+=query(lch, l, mid, x, y);
    if (y>mid) ans+=query(rch, mid+1, r, x, y);
    return ans;
}

int main() {
    int T, icase=1;
    int n;
    char dir[10];
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(st, 0, sizeof(st));
        build(1, 1, n);
        printf("Case %d:\n", icase++);
        while (scanf("%s", dir)) {
            int x, y;
            if (strcmp(dir, "End")==0) break;
            scanf("%d%d", &x, &y);
            if (strcmp(dir, "Add")==0) {
                change(1, 1, n, x, y);
            }else if (strcmp(dir, "Sub")==0) {
                change(1, 1, n, x, -y);
            }else {
                printf("%d\n", query(1, 1, n, x, y));
            }
        }
    }
    return 0;
}
