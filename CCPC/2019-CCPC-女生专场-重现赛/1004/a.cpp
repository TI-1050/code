#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, q, a[N];
vector <vector<int>> G;

int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], tot;
void DFS(int u) {
	sze[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) {
			son[u] = v;
		}
	}
}
void gettop(int u, int tp) {
	in[u] = ++tot;
	fin[tot] = u;
	top[u] = tp;
	if (!son[u]) return;
	gettop(son[u], tp);
	for (auto v : G[u]) {
		if (v != son[u] && v != fa[u]) {
			gettop(v, v);
		}
	}
}

struct SEG {
	struct node {
		ll sum;
		int tot;
		node() {
			sum = tot = 0;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.tot = tot + other.tot;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id].sum = a[fin[l]];
			t[id].tot = (t[id].sum == 1);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int ql, int qr) {
		if (l == r) {
			t[id].sum = floor(sqrt(t[id].sum));
			if (t[id].sum == 1) {
				t[id].tot = 1;
			}
			return;
		}
		if (l >= ql && r <= qr) {
			if (t[id].tot == r - l + 1) return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
	    if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;	
	}
}seg;

void update(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		seg.update(1, 1, n, in[top[u]], in[u]);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	seg.update(1, 1, n, in[u], in[v]);
}
ll query(int u, int v) {
	ll res = 0;
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		res += seg.query(1, 1, n, in[top[u]], in[u]);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return res + seg.query(1, 1, n, in[u], in[v]);
}

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(son, 0, sizeof son);
		tot = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}	
		DFS(1); gettop(1, 1);
		seg.build(1, 1, n);
		int op, u, v;
		while (q--) {
			scanf("%d%d%d", &op, &u, &v);
			switch(op) {
				case 0 :
					update(u, v);
					break;
				case 1 :
					printf("%lld\n", query(u, v));
					break;
			}
		}
	}
	return 0;
}
