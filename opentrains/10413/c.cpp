#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector <vector<int>> G;
int n, m, fa[N], deep[N], son[N], sze[N], in[N], out[N], top[N];
struct qnode {
	int u, v, lca;
	qnode() {}
	qnode(int u, int v, int lca) : u(u), v(v), lca(lca) {}
	bool operator < (const qnode &other) const {
		return deep[lca] > deep[other.lca];
	}
}q[N];
void dfs(int u) {
	sze[u] = 1; son[u] = 0;
	for (auto &v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		dfs(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
	}
}

void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++*in;
	if (son[u]) gettop(son[u], tp);
	for (auto &v : G[u]) if (v != fa[u] && v != son[u])
		gettop(v, v);
	out[u] = *in;
}

int querylca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res += a[x];
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

bool cover(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		if (bit.query(in[top[u]], in[u])) return 1;
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return bit.query(in[u], in[v]);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1); *in = 0;
		bit.init();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		fa[1] = 1; deep[1] = 0;
		dfs(1); gettop(1, 1);
		scanf("%d", &m);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			q[i] = qnode(u, v, querylca(u, v));
		//	cout << u << " " << v << " " << querylca(u, v) << endl;
		}
		sort(q + 1, q + 1 + m);
		vector <int> res;
		for (int i = 1; i <= m; ++i) {
			int u = q[i].u, v = q[i].v, lca = q[i].lca;
			if (cover(u, v)) continue;
			res.push_back(lca);
			bit.update(in[lca], 1);
		}
		int sze = res.size();
		printf("%d\n", sze);
		for (int i = 0; i < sze; ++i) 
			printf("%d%c", res[i], " \n"[i == sze - 1]);
	}	
	return 0;	
}
