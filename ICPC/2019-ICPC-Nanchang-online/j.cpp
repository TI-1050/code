#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m, res[N]; 
vector < vector <int> > G;
struct Edge {
	int u, v, w;
	Edge () {}
	void scan() {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(v);
		G[v].push_back(u); 
	}
	bool operator < (const Edge &other) const {
		return w < other.w;
	}
}e[N];
struct qnode {
	int u, v, k, id;
	qnode () {}
	void scan(int id) {
		this->id = id;
		scanf("%d%d%d", &u, &v, &k);
	}
	bool operator < (const qnode &other) const {
		return k < other.k; 
	}
}qrr[N];

int fa[N], deep[N], son[N], sze[N], top[N], p[N], fp[N], cnt_p;
void DFS(int u) {
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

void gettop(int u, int sp) {
	top[u] = sp;
	p[u] = ++cnt_p;
	fp[cnt_p] = u;
	if (!son[u]) {
		return;
	}
	gettop(son[u], sp);
	for (auto v : G[u]) if (v != son[u] && v != fa[u]) {
		gettop(v, v);
	}
}

struct SEG {
	struct node {
		int sum;
		node () {
			sum = 0;
		}
		void add(int x) {
			sum += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int v) {
		if (l == r) {
			t[id].add(v);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) {
			update(id << 1, l, mid, pos, v);
		} else {
			update(id << 1 | 1, mid + 1, r, pos, v);
		}
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id].sum;
		}
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

int query(int u, int v) {
	int res = 0;
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		res += seg.query(1, 1, n, p[top[u]], p[u]);
		u = fa[top[u]];
	}
	if (u == v) {
		return res;
	}
	if (deep[u] > deep[v]) {
		swap(u, v);
	}
	return res + seg.query(1, 1, n, p[son[u]], p[v]);
}

void init() {
	G.clear();
	G.resize(n + 2);
	memset(son, 0, sizeof son); 
	cnt_p = 0;
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1, u, v; i < n; ++i) {
			e[i].scan();
		}
		for (int i = 1; i <= m; ++i) {
			qrr[i].scan(i);
		}	
		sort(qrr + 1, qrr + 1 + m);
		sort(e + 1, e + n);
		DFS(1); gettop(1, 1);
		seg.build(1, 1, n);
		for (int i = 1; i < n; ++i) {
			if (deep[e[i].u] > deep[e[i].v]) {
				swap(e[i].u, e[i].v); 
			}
		}
		for (int i = 1, j = 1; i <= m; ++i) {
			while (j < n && e[j].w <= qrr[i].k) {
				seg.update(1, 1, n, p[e[j].v], 1);
				++j;
			}
			res[qrr[i].id] = query(qrr[i].u, qrr[i].v); 
		}
		for (int i = 1; i <= m; ++i) {
			printf("%d\n", res[i]);
		}
	}
	return 0;
}
