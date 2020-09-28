#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define M 21
struct Graph {
	struct node {
		int to, nx;
		node() {}
		node(int to, int nx) : to(to), nx(nx) {} 
	}a[N << 1]; 
	int head[N], pos;
	void init() {
		memset(head, -1, sizeof head);
		pos = 0;
	}
	void add(int u, int v) {
		a[pos] = node(v, head[u]); head[u] = pos++; 
	}
}G[2]; 
#define erp(G, u) for (int it = G.head[u], v = G.a[it].to; ~it; it = G.a[it].nx, v = G.a[it].to)

int n, m, q;
int f[N][M], deep[N], d[N], sze[N];
struct Dominator_Tree {
	int que[N], l, r;
	void add(int fa, int x) {
		f[x][0] = fa; deep[x] = deep[fa] + 1;
		for (int i = 1; i < 20; ++i)
			f[x][i] = f[f[x][i - 1]][i - 1];
	}
	int querylca(int u, int v) {
		if (!u) return v;
		if (!v) return u;
		if (deep[u] > deep[v]) swap(u, v);
		for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				v = f[v][i];		
			}
		}
		if (u == v) return u;
		for (int i = M - 1; i >= 0; --i) {
			if (f[u][i] == f[v][i])
				continue;
			u = f[u][i];
			v = f[v][i];
		}
		return f[u][0];
	}
    int getlca(int x) {
		int lca = 0;
		erp(G[1], x) {
			lca = querylca(lca, v);
		}
		return lca; 
	}	
	void work() {
		int S = n + 1; add(S, S);
		l = 1, r = 0;
		for (int i = 1; i <= n; ++i) if (d[i] == 0) {
			que[++r] = i;
			add(S, i);
		}
		while (l <= r) {
			int u = que[l]; ++l;
			erp(G[0], u) {
				--d[v]; 
				if (d[v] == 0) {
					que[++r] = v;
					add(getlca(v), v);
				}
			}
		}
	}
}dt;

void init() {
	for (int i = 0; i < 2; ++i)
		G[i].init();
	for (int i = 0; i <= n + 1; ++i)
		deep[i] = 0, f[i][0] = 0, d[i] = 0, sze[i] = 0;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		init();
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[0].add(v, u);
			G[1].add(u, v);
			++d[u]; 
		}
		dt.work();
		scanf("%d", &q);
		int a, b;
		while (q--) {
			scanf("%d%d", &a, &b);
			int lca = dt.querylca(a, b);
			printf("%d\n", deep[a] + deep[b] - deep[lca] - 1);
		}
	}
	return 0;
}
