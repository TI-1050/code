#include <bits/stdc++.h>
using namespace std;
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
}
using namespace IO;
#define N 100010
int n, m, D, a[N], b[N];

struct SEG {
	struct node {
		int sum, ls, rs;
		node() {
			sum = 0;
			ls = rs = -1;
		}
	}t[N * 60];
	int rt[N], cnt = 0;
	void init() {
		cnt = 0;
		t[0] = node();
		for (int i = 0; i <= n; ++i) rt[i] = 0;
	}
	void pushup(int id, int l, int r) {
		t[id].sum = 0;
		if (l != -1) t[id].sum += t[l].sum;
		if (r != -1) t[id].sum += t[r].sum;
	}
	void update(int &now, int pre, int l, int r, int pos) {
		int tmp = ++cnt; 
		t[tmp] = t[pre];
		if (l == r) {
			++t[tmp].sum;
			now = tmp; 
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(t[tmp].ls, t[pre].ls, l, mid, pos);
		else update(t[tmp].rs, t[pre].rs, mid + 1, r, pos);
		pushup(tmp, t[tmp].ls, t[tmp].rs);
	    now = tmp;	
	}
	int query(int now, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (now == -1) return 0;
		if (l >= ql && r <= qr) return t[now].sum;
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res += query(t[now].ls, l, mid, ql, qr);
		if (qr > mid) res += query(t[now].rs, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int check(int p, int x, int L, int R) {
	int l = lower_bound(b + 1, b + 1 + b[0], p - x) - b;
	l = max(1, l);
	int r = upper_bound(b + 1, b + 1 + b[0], p + x) - b - 1;
	r = min(D, r);
	return seg.query(seg.rt[R], 1, D, l, r) - seg.query(seg.rt[L - 1], 1, D, l, r);
}

int main() {
	int T; T = read();
	assert(T <= 3);
	while (T--) {
		n = read(); m = read();
		seg.init();
		D = 0; b[0] = 0;
		for (int i = 1; i <= n; ++i) a[i] = read(), b[++b[0]] = a[i]; 
		sort(b + 1, b + 1 + b[0]);
		b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
		D = b[0];
		for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + b[0], a[i]) - b;
		for (int i = 1; i <= n; ++i) {
			seg.update(seg.rt[i], seg.rt[i - 1], 1, D, a[i]);
		}
		int lst = 0;	
		int L, R, p, k;
		while (m--) {
			L = read(); R = read(); p = read(); k = read();
			L ^= lst;
			R ^= lst;
			if (L > R) swap(L, R);
			p ^= lst;
			k ^= lst;
			int l = 0, r = 1e6, res = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (check(p, mid, L, R) >= k) {
					res = mid;
					r = mid - 1;
				} else {
					l = mid + 1;
				}
			}
			lst = res;
			print(lst); putc('\n');
		}
	}
	flush();
	return 0;
}
