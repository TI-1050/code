#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, s, m, fa[N], deep[N], top[N], sze[N], in[N], out[N], son[N];
vector <vector<int>> G, vec;

void dfs(int u) {
	sze[u] = 1; son[u] = 0;
	for (auto &v : G[u]) if (v != fa[u]) {
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

struct SEG {
	struct node {
		int sum, lazy;
		node() {
			sum = lazy = 0;
		}
		void up() {
			sum = 0;
			lazy = 1;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].sum = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		if (!t[id].lazy) return;
		t[id].lazy = 0;
		t[id << 1].up();
		t[id << 1 | 1].up();
	}
	void update(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			t[id].up();
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		down(id);
		int res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int gao(int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		res += seg.query(1, 1, n, in[top[u]], in[u]);
		seg.update(1, 1, n, in[top[u]], in[u]);
		u = fa[top[u]];	
	}
	if (u == v) return res;
	if (deep[u] > deep[v]) swap(u, v);
	res += seg.query(1, 1, n, in[son[u]], in[v]);
	seg.update(1, 1, n, in[son[u]], in[v]);
	return res;
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d%d", &n, &s, &m);
		G.clear(); G.resize(n + 1); *in = 0;
		vec.clear(); vec.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		fa[m] = m; deep[m] = 0;
		dfs(m); gettop(m, m);
		int Max = *max_element(deep + 1, deep + 1 + n);
		seg.build(1, 1, n);
		for (int i = 1; i <= n; ++i) vec[deep[i]].push_back(i);
		int res = 1e9, sum = deep[s];
		for (int i = Max; i >= 0; --i) {
			res = min(res, sum + i);
			for (auto &v : vec[i]) {
				int lca = querylca(s, v);
				sum += 2 * gao(lca, v);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
