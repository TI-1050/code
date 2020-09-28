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

#define ll long long
#define N 200010
int n, m, a[N], b[N]; 
struct SEG {
	struct node {
		ll sum; int cnt;
		node() {
			sum = cnt = 0;
		}
		node (ll sum, int cnt) : sum(sum), cnt(cnt) {}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.cnt = cnt + other.cnt;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int x) {
		if (l == r) {
			t[id].sum += b[l];
			++t[id].cnt;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) update(id << 1, l, mid, x);
		else update(id << 1 | 1, mid + 1, r, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, ll need) {
		if (need <= 0) return 0;
		if (l == r) {
			return need / b[l] + (need % b[l] != 0);
		}
		int mid = (l + r) >> 1;
		if (t[id << 1 | 1].sum >= need) 
			return query(id << 1 | 1, mid + 1, r, need);
		else
			return t[id << 1 | 1].cnt + query(id << 1, l, mid, need - t[id << 1 | 1].sum);
	}
}seg;

void Hash(int *b) {
	sort(b + 1, b + 1 + b[0]);
	b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
}

int get(int x) {
	return lower_bound(b + 1, b + 1 + b[0], x) - b;
}

int main() {
	int T; T = read();
	while (T--) {
		n = read(); m = read();
		b[0] = 0;
		for (int i = 1; i <= n; ++i) a[i] = read(), b[++b[0]] = a[i];
		Hash(b);
		seg.build(1, 1, b[0]);
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			sum += a[i];
			print(seg.query(1, 1, b[0], sum - m));
			putc(' ');
			seg.update(1, 1, b[0], get(a[i]));
		}
		putc('\n');
	}
	flush();
	return 0;
}
