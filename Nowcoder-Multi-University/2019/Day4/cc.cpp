#include <bits/stdc++.h>
using namespace std;
 
#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 3000010
int n, a[N];
ll b[N];
 
struct Cartesian_Tree {
    struct node {
        int id, val, fa;
        int son[2];
        node() {}
        node (int id, int val, int fa) : id(id), val(val), fa(fa) {
            son[0] = son[1] = 0;
        }
    }t[N];
    int root;
    pii b[N];
    void init() {
        t[0] = node(0, -1e9, 0);
    }
    void build(int n, int *a) {
        for (int i = 1; i <= n; ++i) {
            t[i] = node(i, a[i], 0);
        }
        for (int i = 1; i <= n; ++i) {
            int k = i - 1;
            while (t[k].val > t[i].val) {
                k = t[k].fa;
            }
             
            t[i].son[0] = t[k].son[1];
            t[k].son[1] = i;
            t[i].fa = k;
            t[t[i].son[0]].fa = i;
        }
        root = t[0].son[1];
    }
    int DFS(int u) {
        if (!u) return 0;
        int lsze = DFS(t[u].son[0]); 
        int rsze = DFS(t[u].son[1]);
        b[t[u].id] = pii(lsze, rsze);
        return lsze + rsze + 1;
    }
}CT;
 
struct SEG {
    struct node {
        ll Max, Min;
        node() {
            Max = -INFLL;
            Min = INFLL;
        }
        node operator + (const node &other) const {
            node res = node();
            res.Max = max(Max, other.Max);
            res.Min = min(Min, other.Min);
            return res;
        }
    }t[N << 2], resl, resr;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            t[id].Max = t[id].Min = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    node query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return t[id];
        }
        int mid = (l + r) >> 1;
        node res = node();
        if (ql <= mid) res = res + query(id << 1, l, mid, ql, qr);
        if (qr > mid) res = res + query(id << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
}seg;
 
namespace IO
{
    const int S=(1<<20)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c<'a'||c>'z') c=Get();
        while(c>='a'&&c<='z') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
    inline void printd(int d,double x)
    {
        long long t=(long long)floor(x);
        print(t);putc('.');x-=t;
        while(d--)
        {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}using namespace IO;
 
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    b[0] = 0;
    for (int i = 1; i <= n; ++i) {
        b[i] = read();
        b[i] += b[i - 1];
    }
    CT.init();
    CT.build(n, a);
    CT.DFS(CT.root);
    ll res = -INFLL;
    seg.build(1, 0, n);
    for (int i = 1; i <= n; ++i) {
        int l = i - CT.b[i].fi, r = i + CT.b[i].se;
        seg.resl = seg.query(1, 0, n, l - 1, i - 1);
        seg.resr = seg.query(1, 0, n, i, r);
        res = max(res, 1ll * a[i] * (seg.resr.Max - seg.resl.Min));
        res = max(res, 1ll * a[i] * (seg.resr.Min - seg.resl.Max));
    }
    printf("%lld\n", res);
    return 0;
}
