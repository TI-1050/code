#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define INF 0x3f3f3f3f
int n, q, m;
map <ll, int> mp; int cnt;

namespace IO
{
    const int S=(1<<22)+5;
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
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) s[tot++]=c,c=Get();
        s[tot++]='\0';
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
		//输出换行
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
}

ll change(char *s) {
	ll r;
	sscanf(s, "%lld", &r);
	return r + 10000000000ll*(strlen(s)-1);
}

int get(ll s) { 
	if (mp.count(s) == 0) {
		return mp[s] = ++cnt;
	}
	return mp[s];  
}

struct SEG {
	struct node {
		int pos, lst, v;
		node() {
			pos = -1;
			lst = INF;
			v = 0;
		}
		node (int lst, int v) : lst(lst), v(v) {}
		node operator + (const node &other) const {
			node res = node();
			if (lst < other.lst) {
				res.lst = lst;
				res.pos = pos;
				res.v = v;
			} else {
				res.lst = other.lst;
				res.pos = other.pos;
				res.v = other.v;  
			}
			return res; 
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].pos = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos, int lst, int v) {
		if (l == r) {
			t[id].pos = pos; 
			t[id].lst = lst;
			t[id].v = v;
			return;
		}	
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, lst, v);
		else update(id << 1 | 1, mid + 1, r, pos, lst, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int pos) {
		if (l == r) {
			res = t[id]; 
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) query(id << 1, l, mid, pos);
		else query(id << 1 | 1, mid + 1, r, pos); 
	}
}seg;


struct SEG2 {
	struct node {
		int v, pos;
		node() {
			v = 0;
			pos = 0;
		}
		node (int v, int pos) : v(v), pos(pos) {}
		node operator + (const node &other) const {
			node res = node();
			res.v = v + other.v;
			return res;	
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int lst, int v, int pos) {
		if (l == r) {
			t[id].v = v;
			t[id].pos = pos;
			return;
		}
		int mid = (l + r) >> 1;
		if (lst <= mid) update(id << 1, l, mid, lst, v, pos);
		else update(id << 1 | 1, mid + 1, r, lst, v, pos);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query1(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].v;
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res += query1(id << 1, l, mid, ql, qr);
		if (qr > mid)  res += query1(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
	int query2(int id, int l, int r, int k) {
		if (l == r) return t[id].pos;
		int mid = (l + r) >> 1;
		if (t[id << 1].v >= k) return query2(id << 1, l, mid, k);
		else {
			return query2(id << 1 | 1, mid + 1, r, k - t[id << 1].v);
		}
	}
}seg2;

void No() {
	IO::prints("Invalid");
}

int main() {
	int T; T = IO::read();
	while (T--) {
		q = IO::read();
		m = IO::read();
		mp.clear();	cnt = 0;
		int tot = 0;
		n = q;
		seg.build(1, 1, n);
		seg2.build(1, 1, n); 
		int op, v, id; char tmp[20]; ll s;
		for (int i = 1; i <= q; ++i) {
			op = IO::read(); IO::reads(tmp); v = IO::read();
			s = change(tmp);
			id = get(s);
			if (op == 0) {
				seg.query(1, 1, n, id);
				if (seg.res.lst == INF) {
					seg.update(1, 1, n, id, i, v);
					seg2.update(1, 1, n, i, 1, id);
					IO::print(v);
					if (tot >= m) {
						int iid = seg.t[1].pos;
						seg2.update(1, 1, n, seg.t[1].lst, 0, iid);
						seg.update(1, 1, n, iid, INF, seg.t[1].v);   
					} else {
						++tot;
					} 
				} else {
					seg2.update(1, 1, n, seg.res.lst, 0, id); 
					seg2.update(1, 1, n, i, 1, id);
					seg.update(1, 1, n, id, i, seg.res.v);
					IO::print(seg.res.v);
				}
			} else {
				seg.query(1, 1, n, id);
				if (seg.res.lst == INF) {
					No();
					continue;
				}
				if (v == 0) {
					IO::print(seg.res.v);
				}
				else {
					int Rank = seg2.query1(1, 1, n, 1, seg.res.lst);
					if ((v == -1 && Rank == 1) || (Rank == tot && v == 1)) No();
					else {
						int ppos = seg2.query2(1, 1, n, Rank + v);
						seg.query(1, 1, n, ppos);
						IO::print(seg.res.v);
					}
				}
			}
		}
	}
	IO::flush();
	return 0;
}
