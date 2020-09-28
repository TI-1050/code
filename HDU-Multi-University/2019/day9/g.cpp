#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
int n, e[N][2], fa[N], deep[N], sze[N], bson[N], top[N]; 
struct node { 
	int s, t; 
	node() {}
	node(int s, int t) : s(s), t(t) {}
};
struct Edge { int v; node pre, now, suf; }; 
vector <vector<Edge>> G; 
void pre(int u) {
	sze[u] = 1;
	bson[u] = 0;
	for (auto &it : G[u]) {
		int v = it.v;
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		pre(v);
		sze[u] += sze[v];
		if (!bson[u] || sze[v] > sze[bson[u]]) bson[u] = v;
	}
}
void gettop(int u, int tp) {
	top[u] = tp;
	if (bson[u]) gettop(bson[u], tp);
	for (auto &it : G[u]) {
		int v = it.v;
		if (v == fa[u] || v == bson[u]) continue;
		gettop(v, v);
	}
}
int querylca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}
int dis(int u, int v) {
	return deep[u] + deep[v] - 2 * deep[querylca(u, v)];
}
int dis(node x) {
	int u = x.s, v = x.t;
	return dis(u, v);
}
node merge(node A, node B) {
	node res = A;
	if (dis(B) > dis(res)) res = B;
	if (dis(A.s, B.s) > dis(res)) res = node(A.s, B.s); 
	if (dis(A.s, B.t) > dis(res)) res = node(A.s, B.t); 
	if (dis(A.t, B.s) > dis(res)) res = node(A.t, B.s);
	if (dis(A.t, B.t) > dis(res)) res = node(A.t, B.t);
	return res;
}
struct SEG {
	struct node {
		int v, lazy;
		node() { v = lazy = 0; }
		void add(int x) { v = max(v, x); lazy = max(lazy, x); } 
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
		if (l >= ql && r <= qr) {
			t[id].add(v);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
	}
	int query(int id, int l, int r, int pos) {
		if (l == r) return t[id].v;
		int mid = (l + r) >> 1;
		int res = t[id].lazy;
		if (pos <= mid) return max(res, query(id << 1, l, mid, pos));
		else return max(res, query(id << 1 | 1, mid + 1, r, pos));
	}
}seg;
void calc(node S, node T) {
	int x = dis(S) + 1, y = dis(T) + 1;
	seg.update(1, 1, n, 1, x, y);
	seg.update(1, 1, n, 1, y, x);
}
node g[N]; 
node DFS(int u) {
	g[u] = {u, u};
	for (auto &it : G[u]) {
		it.now = DFS(it.v); 
	}
	int sze = (int)G[u].size();
	for (int i = 0; i < sze; ++i) {
		if (!i) G[u][i].pre = G[u][i].now;
		else G[u][i].pre = merge(G[u][i - 1].pre, G[u][i].now);
	}
	for (int i = sze - 1; i >= 0; --i) {
		if (i == sze - 1) G[u][i].suf = G[u][i].now;
		else G[u][i].suf = merge(G[u][i + 1].suf, G[u][i].now);
	}
	if (G[u].empty()) return g[u];
	return merge(g[u], G[u].end()[-1].pre);
}
void DFS2(int u) {
	int sze = (int)G[u].size();
	for (int i = 0; i < sze; ++i) {
		int v = G[u][i].v;
		g[v] = merge(g[u], {v, v});  
		if (i < sze - 1) g[v] = merge(g[v], G[u][i + 1].suf);
		node anc = g[u]; 
		if (i < sze - 1) anc = merge(anc, G[u][i + 1].suf); 
		node son = {v, v};
		if (!G[v].empty()) son = merge(son, G[v].end()[-1].pre);
		calc(anc, son);
		DFS2(v);
		g[u] = merge(g[u], G[u][i].now);
	}
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		G.clear();
		G.resize(n + 1);
		for (int i = 1; i < n; ++i) {
			int &u = e[i][0], &v = e[i][1];
			scanf("%d%d", &u, &v);
			G[u].push_back({v, node(), node(), node()}); 
			G[v].push_back({u, node(), node(), node()});	
		}
		fa[1] = 1; deep[1] = 0; 
		pre(1); gettop(1, 1);
		G.clear(); G.resize(n + 1);
		for (int i = 1; i < n; ++i) {
			int &u = e[i][0], &v = e[i][1];
			if (fa[u] == v) swap(u, v);
			G[u].push_back({v, {v, v}, {v, v}, {v, v}});	
		}
		seg.build(1, 1, n);
		DFS(1); 
		DFS2(1);
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			res += seg.query(1, 1, n, i);
		}
		printf("%lld\n", res);
	}
	return 0;
}
