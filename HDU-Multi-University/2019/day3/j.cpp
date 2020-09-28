#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, q, f[N], y[N];
vector <vector<int>> G;
ll Y[N];  
template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;  
}

int fa[N], deep[N], sze[N], son[N], top[N], in[N], fin[N], cnt;
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
	if (!son[u]) return;
	gettop(son[u], tp);
	for (auto v : G[u]) if (v != fa[u] && v != son[u]) {
		gettop(v, v);
	}
}

struct SEG {
	struct node {
		ll F, Fy[2];
		node() {
			F = Fy[0] = Fy[1] = 0;
		}
		void up(int x) {
			F = f[x];
			Fy[0] = 1ll * f[x] * Y[x] % p;
			Fy[1] = 1ll * f[x] * (Y[x] - y[x] + p) % p;
		}
		node operator + (const node &other) const {
			node res = node();
			res.F = (F + other.F) % p;
			for (int i = 0; i < 2; ++i)
				res.Fy[i] = (Fy[i] + other.Fy[i]) % p;  
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].up(fin[l]);   
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int pos) {
		if (l == r) {
			t[id].up(fin[l]);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos);
		else update(id << 1 | 1, mid + 1, r, pos);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

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

void query(int u, int v) {
	seg.res = SEG::node();
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) swap(u, v);
		seg.query(1, 1, n, in[top[u]], in[u]);
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	seg.query(1, 1, n, in[u], in[v]);    
}

void init() {
	G.clear(); G.resize(n + 1);
	for (int i = 1; i <= n; ++i) son[i] = 0;
	cnt = 0;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); init();
		for (int i = 1; i <= n; ++i) scanf("%d", f + i);
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
		scanf("%d", &q);
		int op, s, t, x, c, v;
		while (q--) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d%d%d", &s, &t, &x);
				ll res = 0, Ly, Ry, F, Fy;
				int lca = querylca(s, t);
				//右边下去的贡献
				query(lca, t);
				F = seg.res.F; Fy = seg.res.Fy[1];
			    cout << F << " " << Fy << endl;	
				Ly = Y[s] - Y[lca]; 
				add(res, F * x % p);
				add(res, p - seg.res.F * Ly % p);
				add(res, p - Fy % p);
				add(res, F * (Y[lca] - y[lca] + p) % p);
				cout << res << endl;

				//左边上去的贡献
				query(s, lca); 
				Ry = Y[t] - Y[lca] + y[lca];
				F = (seg.res.F - f[lca] + p) % p;
				add(res, F * Ry % p);
				Fy = (seg.res.Fy[0] - f[lca] * Y[lca] % p + p) % p; 
				add(res, Fy);
				add(res, (p - (F * (Y[lca] - y[lca] + p) % p)) % p);
				ll remindx = (x - Y[s] - Y[t] + 2ll * Y[lca] - 2ll * y[lca] + p) % p;
				add(res, F * remindx % p);
				printf("%lld\n", res);
			} else {
				scanf("%d%d", &c, &v);
				f[c] = v;
				seg.update(1, 1, n, in[c]); 
			}
		}
	}
	return 0;
}
