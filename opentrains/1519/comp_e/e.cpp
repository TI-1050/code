#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e6 + 10, OFFSET = 2e6; 
int n, rt, all, sze[N], f[N], vis[N]; ll ans;
vector <vector<int>> G;

struct BIT {
	int a[N], pos[N], POS;
	inline void init() { POS = 0; }
	void update(int x) {
		for (; x < N; x += x & -x) {
			if (pos[x] < POS) {
				pos[x] = POS;
				a[x] = 1;
			} else {
				++a[x];
			}
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			if (pos[x] == POS) {
				res += a[x];
			}
		}
		return res;
	}
	int query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit;

struct E {
	int a, b, c;
	E(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
	bool operator < (const E &other) const {
		return a < other.a; 
	}
}e[N]; int ce;

struct W {
	int v, op, id, l, r;
	W(int v = 0, int op = 0, int id = 0, int l = 0, int r = 0) : v(v), op(op), id(id), l(l), r(r) {}
	bool operator < (const W &other) const {
		if (v != other.v) return v < other.v;
		return id < other.id;
	}
}w[N]; int cw;

void getrt(int u, int fa) {
	sze[u] = 1; f[u] = 0;
	for (auto &v : G[u]) {
		if (v == fa || vis[v]) continue;
		getrt(v, u);
		sze[u] += sze[v];
		f[u] = max(f[u], sze[v]);
	}
	f[u] = max(f[u], all - sze[u]);
	if (f[u] < f[rt]) rt = u;
}

ll calc() {
	ll res = 0;
	sort(e + 1, e + 1 + ce);
	cw = 0;
	//ma - mi = cx + cy
	for (int i = 1; i <= ce; ++i) {
		w[++cw] = W(e[i].a - e[i].c, 0, i << 1, 0, e[i].b);
		w[++cw] = W(e[i].a - e[i].b - e[i].c + OFFSET, 0, i << 1, e[i].b + 1, n);
		w[++cw] = W(e[i].b + e[i].c, 1, i << 1 | 1, e[i].b, 0); 
		w[++cw] = W(e[i].c + OFFSET, 1, i << 1 | 1, e[i].b, 0);
	}
	sort(w + 1, w + 1 + cw);
	for (int i = 1; i <= cw; ++i) {
		if (i == 1 || w[i].v != w[i - 1].v) ++bit.POS;
		if (w[i].op == 1) bit.update(w[i].l);
		else ans += bit.query(w[i].l, w[i].r);
	}
	return res;
}

void dfs(int u, int fa, int dis, int ma, int mi, int op) {
	ma = max(ma, u);
	mi = min(mi, u);
	if (ma - mi == dis) ans += op;
	e[++ce] = E(ma, mi, dis);
	for (auto &v : G[u]) if (!vis[v] && v != fa) dfs(v, u, dis + 1, ma, mi, op);
}

void gao(int u) {
	vis[u] = 1;
	for (auto &v : G[u]) if (!vis[v]) {
		ce = 0;
		dfs(v, u, 1, u, u, 1);
		ans -= calc();
	}	
	ce = 0;
	for (auto &v : G[u]) if (!vis[v]) dfs(v, u, 1, u, u, 0);
	ans += calc();
	for (auto &v : G[u]) if (!vis[v]) {
		all = f[0] = sze[v]; rt = 0;
		getrt(v, u); gao(rt); 
	}
}


int main() {
	bit.init();
	scanf("%d", &n);
//	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(vis, 0, sizeof vis);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		ans = 0;
		all = f[0] = n; rt = 0;
		getrt(1, 0); gao(rt); 
		printf("%lld\n", ans + n);
//	}
	return 0;
}
