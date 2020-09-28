#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 1e9 + 7;
int n, q, f[N], y[N];
vector <vector<int>> G;
ll Y[N];     
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], out[N], cnt;
void DFS(int u) {
	sze[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		Y[v] = (Y[u] + y[v]) % p;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
		if (!son[u] || sze[u] > sze[son[u]]) {
			son[u] = v;
		}
	}
}

void gettop(int u, int tp) {
	top[u] = tp;
	in[u] = ++cnt;
	fin[cnt] = u;
	if (!son[u]) {
		out[u] = cnt;
		return;
	}
	gettop(son[u], tp);
	for (auto v : G[u]) if (v != fa[u] && v != son[u]) {
		gettop(v, v);
	}
	out[u] = cnt;
}

int querylca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

struct SEG {
	struct node {
		ll F, Fy[2], lazy[3];     
		node() {
			F = Fy[0] = Fy[1] = 0;
			lazy[0] = lazy[1] = lazy[2] = 0;
		}
		void up(ll F, ll Fy0, ll Fy1) { 
			add(this->F, F);
			add(Fy[0], Fy0);
			add(Fy[1], Fy1);
			add(lazy[0], F);
			add(lazy[1], Fy0);
			add(lazy[2], Fy1);
		}
	}t[N << 2], S, T, lca; 
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		t[id << 1].up(t[id].lazy[0], t[id].lazy[1], t[id].lazy[2]);
		t[id << 1 | 1].up(t[id].lazy[0], t[id].lazy[1], t[id].lazy[2]);
		t[id].lazy[0] = t[id].lazy[1] = t[id].lazy[2] = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll F, ll Fy0, ll Fy1) {
		if (l >= ql && r <= qr) {
			t[id].up(F, Fy0, Fy1);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, F, Fy0, Fy1);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, F, Fy0, Fy1);
	}
	node query(int id, int l, int r, int pos) {
		if (l == r) return t[id];
		int mid = (l + r) >> 1;
		pushdown(id);
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
}seg;

void init() {
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) son[i] = 0;
	cnt = 0;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); init(); 
		for (int i = 1; i <= n; ++i) scanf("%d", f + i), f[i] %= p;
		for (int i = 1; i <= n; ++i) scanf("%d", y + i);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Y[1] = y[1]; 
		DFS(1); 
		gettop(1, 1);
		seg.build(1, 1, n);
		for (int i = 1; i <= n; ++i) {
			seg.update(1, 1, n, in[i], out[i], f[i], Y[i] * f[i] % p, (Y[i] - y[i] + p) % p * f[i] % p);
		}
		scanf("%d", &q);
		int op, s, t, x, c, v;
		while (q--) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d%d", &s, &t, &x);
				ll res = 0, Ly, Ry, F, Fy;
				int lca = querylca(s, t);
				seg.S = seg.query(1, 1, n, in[s]);
				seg.T = seg.query(1, 1, n, in[t]);
				seg.lca = seg.query(1, 1, n, in[lca]); 
				//右边下去的贡献
				F = (seg.T.F - seg.lca.F + f[lca] + p) % p;   
				Fy = (seg.T.Fy[1] + p - seg.lca.Fy[1] + 1ll * f[lca] * (Y[lca] + p - y[lca]) % p) % p;
				Ly = (Y[s] + p - Y[lca]) % p; 
				add(res, F * x % p);
				add(res, p - F * Ly % p);
				add(res, p - Fy);
				add(res, F * (Y[lca] + p - y[lca]) % p);
				
				//左边上去的贡献
				Ry = (Y[t] + p - Y[lca] + y[lca]) % p;
				F = (seg.S.F + p - seg.lca.F) % p;
				Fy = (seg.S.Fy[0] + p - seg.lca.Fy[0]) % p;
				add(res, F * Ry % p);
				add(res, Fy);
				add(res, p - (F * Y[lca] % p));
				ll remindx = (x + p - Y[s] + p - Y[t] + 2ll * Y[lca] + p - y[lca]) % p;
				add(res, F * remindx % p);
				printf("%lld\n", res);
			} else {
				scanf("%d%d", &c, &v);
				seg.update(1, 1, n, in[c], out[c], p - f[c], Y[c] * (p - f[c]) % p, (Y[c] + p - y[c]) % p * (p - f[c]) % p);
				f[c] = v % p;
				seg.update(1, 1, n, in[c], out[c], f[c], Y[c] * f[c] % p, (Y[c] + p - y[c]) % p * f[c] % p);
			}
		}
	}
	return 0;
}
