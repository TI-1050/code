#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5010
#define M 20000
const ll p = 1e9 + 7;
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
int x1[M], x2[M], r[M];
void NTT(int *P,int opt)
{
    for(int i=0;i<len;++i)if(i<r[i])swap(P[i],P[r[i]]);
    for(int i=1;i<len;i<<=1)
    {
        int W=qpow(pr,phi/(i<<1));
        for(int p=i<<1,j=0;j<len;j+=p)
        {
            int w=1;
            for(int k=0;k<i;++k,w=1ll*w*W%p)
            {
                int X=P[j+k],Y=1ll*w*P[i+j+k]%p;
                P[j+k]=(X+Y)%p;P[i+j+k]=(X-Y+p)%p;
            }
        }
    }
    if(opt==-1){
		reverse(&P[1], &P[len]);
		int inv = qmod(len, p - 2);
		for (int i = 0; i < len; ++i) {
			
		}
	}
}

int n, m, k, len;
vector < vector<int> > G;
int f[N][N], g[N];
int vis[N];  

void DFS(int u, int fa) {
	for (int i = 0; i <= k; ++i) {
		f[u][i] = 0;
	}
	if (vis[u]) {
		f[u][0] = 1;
	}
	for (auto v : G[u]) if (v != fa) {
		DFS(v, u);
		for (int i = 0; i < len; ++i) {
			x1[i] = x2[i] = 0;
		}
		for (int i = 0; i <= k; ++i) {
			x1[i] = f[u][i];
			x2[i] = f[v][i];
		}
		for (int i = 0; i <= k; ++i) {
			printf("%d %d %d %d %d\n", u, v, i, x1[i], x2[i]);
		}
		NTT(x1, len, 1);
		NTT(x2, len, 1);
		for (int i = 0; i < len; ++i) {
			x1[i] = 1ll * x1[i] * x2[i] % p;
		}
		NTT(x1, len, -1);
		for (int i = 0; i <= k; ++i) {
			printf("%d %d %d %d\n", u, v, i, x1[i]);
		}
		for (int i = 0; i <= k; ++i) {
			g[i] = f[u][i];
			if (i) {
				(g[i] += x1[i - 1] + f[v][i - 1]) %= p;
			}
		}
		for (int i = 0; i <= k; ++i) {
			f[u][i] = g[i];
		}
	}
//	for (int i = 0; i <= k; ++i) {
//		printf("%d %d %d\n", u, i, f[u][i]);
//	}
}

void init() {
	G.clear();
	G.resize(n + 1);
}
int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		init();
		memset(vis, 0, sizeof vis);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			vis[x] = 1;
		}
		len = 1, l = 0;
		while (len <= 2 * k) {
			len <<= 1;
			++l;
		}
		for (int i = 0; i < len; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
		DFS(1, 1);
		ll res = 0;
		for (int i = 0; i <= k; ++i) {
			(res += f[1][i]) %= p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
