#include <bits/stdc++.h>
using namespace std;

#define N 510
#define INF 0x3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second

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

int a[N][N];
struct RMQ {
	int f[N][N][9][9], g[N][N][9][9];
	int mm[N];
	inline void init(int n, int m, int a[][N]) {
		mm[0] = -1;
		for (int i = 1; i < N; ++i) {
			mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				f[i][j][0][0] = a[i][j];
				g[i][j][0][0] = a[i][j];
			}
		}
		for (int ii = 0; ii <= mm[n]; ++ii) {
			for (int jj = 0; jj <= mm[m]; ++jj) {
				if (ii + jj) {
					for (int i = 1; i + (1 << ii) - 1 <= n; ++i) {
						for (int j = 1; j + (1 << jj) - 1 <= m; ++j) {
							if (ii) {
								f[i][j][ii][jj] = max(f[i][j][ii - 1][jj], f[i + (1 << (ii - 1))][j][ii - 1][jj]);
								g[i][j][ii][jj] = min(g[i][j][ii - 1][jj], g[i + (1 << (ii - 1))][j][ii - 1][jj]);
							} else {
								f[i][j][ii][jj] = max(f[i][j][ii][jj - 1], f[i][j + (1 << (jj - 1))][ii][jj - 1]);
								g[i][j][ii][jj] = min(g[i][j][ii][jj - 1], g[i][j + (1 << (jj - 1))][ii][jj - 1]);
							}
						}
					}
				}
			}
		}
	} 
	
	inline void Max(int &x, int y) {
		if (x < y) x = y;
	}
	
	inline void Min(int &x, int y) {
		if (x > y) x = y;
	}
	
	inline pii query(int x1, int y1, int x2, int y2) {
		int k1 = mm[x2 - x1 + 1];
		int k2 = mm[y2 - y1 + 1];
		x2 = x2 - (1 << k1) + 1;
		y2 = y2 - (1 << k2) + 1;
		pii res = pii(-INF, INF);
		Max(res.fi, f[x1][y1][k1][k2]);
		Max(res.fi, f[x1][y2][k1][k2]);
		Max(res.fi, f[x2][y1][k1][k2]);
		Max(res.fi, f[x2][y2][k1][k2]);
		Min(res.se, g[x1][y1][k1][k2]);
		Min(res.se, g[x1][y2][k1][k2]);
		Min(res.se, g[x2][y1][k1][k2]);
		Min(res.se, g[x2][y2][k1][k2]);
		return res;
	}
}rmq;

int main() {
	int n, m;
	int T; T = IO::read();
	while (T--) {
		n = IO::read(); m = IO::read();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				a[i][j] = IO::read();
			}
		}
		rmq.init(n, n, a);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				int pos = 1;
				for (int k = 1; k <= n; ++k) {
					while (pos <= k) {
						pii tmp = rmq.query(i, pos, j, k);
						if (tmp.fi - tmp.se > m) ++pos;
						else break;
					}
					if (pos <= k) res = max(res, (j - i + 1) * (k - pos + 1));
					if ((j - i + 1) * (n - pos + 1) <= res) break;
				}
			}
		}
		IO::print(res);
	}
	IO::flush();
	return 0;
}
