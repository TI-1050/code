#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, S, T;
vector <vector<int>> G;

int fa[N], deep[N], sze[N], in[N], out[N], cnt;
void DFS(int u) {
	in[u] = ++cnt;
	sze[u] = 1;
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		sze[u] += sze[v];
	}
	out[u] = cnt;
}

struct SEG {
	struct node {
		ll sum, lazy, cnt;
		node(int cnt = 0) {
			this->cnt = cnt;
			sum = lazy = 0;
		}
		node (ll sum, ll lazy) : sum(sum), lazy(lazy) {}
		void add(ll x) {
			sum += x * cnt;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.cnt = cnt + other.cnt;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node(r - l + 1);
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll x) {
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int pos) {
		if (l == r) return t[id].sum; 
		int mid = (l + r) >> 1;
		pushdown(id);
		if (pos <= mid) return query(id << 1, l, mid, pos);
		else return query(id << 1 | 1, mid + 1, r, pos);
	}
}seg;

ll work(int u, int S) {
	ll res = 0;
	for (auto v : G[u]) if (v != fa[u]) {
		seg.update(1, 1, n, in[v], out[v], 1ll * (sze[v] + S) * (n - sze[v] - S));
		res += work(v, S); 
	}
	seg.update(1, 1, n, in[u], in[u], res); 
	return res + 1ll * sze[u] * (n - sze[u]); 
}

ll query(int u) {
	ll res = seg.query(1, 1, n, in[u]);
	for (auto v : G[u]) if (v != fa[u]) {
		res = min(res, query(v));
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		cnt = 0;
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = -1;
		for (int i = 1, u, v; i < n - 1; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		int rt[2]; rt[0] = 1;
		fa[1] = 1;
		DFS(1); S = out[1] - in[1] + 1; T = n - S;
		for (int i = 1; i <= n; ++i) {
			if (fa[i] == -1) {
				rt[1] = i;
				fa[i] = i;
				DFS(i);
				break;
			}
		}
		seg.build(1, 1, n);
		work(1, T); work(rt[1], S); 
		ll res = query(rt[0]) + query(rt[1]) + 1ll * S * T;
		printf("%lld\n", res); 
	}
	return 0;
}
