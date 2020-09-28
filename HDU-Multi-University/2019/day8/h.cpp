#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e4 + 10;
int n, m, k;
struct Graph {
	struct node {
		int to, nx, w;
		node() {}
		node(int to, int nx, int w) : to(to), nx(nx), w(w) {}
	}a[N << 1];
	int head[N], pos;
	void init(int n) {
		pos = 0;
		memset(head, 0, sizeof (head[0]) * (n + 1));
	}
	void add(int u, int v, int w) {
		a[++pos] = node(v, head[u], w); head[u] = pos;
		a[++pos] = node(u, head[v], w); head[v] = pos; 
	} 
}G;
#define erp(u) for (int it = G.head[u], v = G.a[it].to, w = G.a[it].w; it; it = G.a[it].nx, v = G.a[it].to, w = G.a[it].w) 

int c[N];
int f[N][1 << 6];
mt19937 rnd(time(NULL));
int iteration() {
	memset(f, -1, sizeof (f[0]) * (n + 1));
	for (int i = 1; i <= n; ++i) {
		c[i] = rnd() % k;
		f[i][1 << c[i]] = 0;
	}
	for (unsigned mask = 0; mask < (1 << k); ++mask) {
		for (int u = 1; u <= n; ++u) if ((mask >> c[u]) & 1) {
			erp(u) {
				if (f[v][mask ^ (1 << c[u])] >= 0)
					f[u][mask] = max(f[u][mask], f[v][mask ^ (1 << c[u])] + w); 
			}
		}
	}
	int ans = -1;
	for (int i = 1; i <= n; ++i) ans = max(ans, f[i][(1 << k) - 1]);
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		G.init(n);
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			G.add(u, v, w);
		}
		int ans = -1;
		for (int i = 0; i <= 50; ++i) ans = max(ans, iteration());
		if (ans == -1) puts("impossible");
		else printf("%d\n", ans);
	}
	return 0;
}
