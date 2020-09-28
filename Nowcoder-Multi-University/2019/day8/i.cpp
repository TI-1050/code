#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 3e5 + 10;
int n, m, q, l[N], r[N], in[N], fin[N], out[N], cnt;  
ll res[N];
struct qnode {
	int l, r, id, f;
	qnode() {}
	qnode(int l, int r, int id, int f) : l(l), r(r), id(id), f(f) {}
};
vector <vector<qnode>> qvec; 
vector <vector<int>> G; 
void DFS(int u) {
	in[u] = ++cnt; fin[cnt] = u;  
	for (auto v : G[u]) DFS(v); 
	out[u] = cnt;
}

struct SEG {
	struct node {
		int cnt;
		ll sum, lazy;
		node() {
			cnt = 0;
			sum = lazy = 0;
		}
		void add(ll x) {
			sum += x * cnt;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.cnt = cnt + other.cnt;
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) {
			t[id].cnt = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void down(int id) {
		ll &lazy = t[id].lazy;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, int v) {
		if (l >= ql && r <= qr) {
			t[id].add(v);
			return;
		}
		int mid = (l + r) >> 1;
		down(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		down(id);
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(m + 5);
		l[1] = 1; r[1] = n; 
		for (int i = 1, u, v, _l, _r; i <= m; ++i) {
			scanf("%d%d%d%d", &u, &v, &_l, &_r);
			l[v] = _l; r[v] = _r;
			G[u].push_back(v); 
		}
		cnt = 0; DFS(1);
		scanf("%d", &q);
		qvec.clear(); qvec.resize(m + 5); 
		for (int i = 1, x, l, r; i <= q; ++i) {
			scanf("%d%d%d", &x, &l, &r);
			if (in[x] > 1) qvec[in[x] - 1].push_back(qnode(l, r, i, -1)); 
			qvec[out[x]].push_back(qnode(l, r, i, 1));
		}
		memset(res, 0, sizeof res);
		++m;
		seg.build(1, 1, m); 
		for (int i = 1; i <= m; ++i) {
			int x = fin[i]; 
		//	cout << x << " " << l[x] << " " << r[x] << endl; 
			seg.update(1, 1, m, l[x], r[x], 1);
			for (auto &it : qvec[i]) {
				res[it.id] += 1ll * it.f * seg.query(1, 1, m, it.l, it.r);
			}
		}
		for (int i = 1; i <= q; ++i)
			printf("%lld\n", res[i]);
	}
	return 0;
}
