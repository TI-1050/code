#include <bits/stdc++.h>
using namespace std;

#define dbg(...) { printf("# "); printf(__VA_ARGS__); puts(""); }
#define N 200010
#define M 20
#define pii pair <int, int>
#define fi first
#define se second
vector <vector<int>> G;
int n, q, m;
struct node {
	pii x[3];
	int op, id;  
	node() {}
	//0表示插入
	//1表示查询
	node(pii x0, pii x1, pii x2, int op = 0, int id = -1) : op(op), id(id) {
		x[0] = x0; x[1] = x1; x[2] = x2;
		sort(x, x + 3);
	}
	void reset() {
		sort(x, x + 3, [](pii a, pii b) {
			return a.se < b.se;		
		});
	}
	bool operator < (const node &other) const {
		for (int i = 0; i < 3; ++i) {
			if (x[i].fi != other.x[i].fi) { 
				return x[i].fi > other.x[i].fi;
			}
		}
		return op < other.op;
	}
}qrr[N << 1], ans[N];

int fa[N][M], deep[N], in[N], out[N], cnt;
pii f[N][3], g[N];
void DFS(int u) {
	in[u] = ++cnt;
	f[u][0] = pii(0, u);
	f[u][1] = pii(-1, -1);
	f[u][2] = pii(-1, -1);
	for (int i = 1; i < M; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (auto v : G[u]) {
		if (v == fa[u][0]) continue;
		fa[v][0] = u;
		deep[v] = deep[u] + 1;
		DFS(v);
		if (f[v][0].fi + 1 > f[u][0].fi) {
			f[u][2] = f[u][1];
			f[u][1] = f[u][0];
			f[u][0] = f[v][0];
			++f[u][0].fi;
		} else if (f[v][0].fi + 1 > f[u][1].fi) {
			f[u][2] = f[u][1];
			f[u][1] = f[v][0];
			++f[u][1].fi;
		} else if (f[v][0].fi + 1 > f[u][2].fi) {
			f[u][2] = f[v][0];
			++f[u][2].fi;
		}
	}
	out[u] = cnt;
}

void DFS2(int u) {
	for (auto v : G[u]) {
		if (v == fa[u][0]) continue;
		g[v] = g[u]; ++g[v].fi; 
		if (in[v] <= in[f[u][0].se] && in[f[u][0].se] <= out[v]) {
			if (f[u][1].fi + 1 > g[v].fi) {
				g[v] = f[u][1];
				++g[v].fi;
			}
		} else {
			if (f[u][0].fi + 1 > g[v].fi) {
				g[v] = f[u][0];
				++g[v].fi; 
			}
		}
		DFS2(v);
	}
}

int querylca(int u, int v) {
	if (deep[u] > deep[v]) swap(u, v);
	for (int gap = deep[v] - deep[u], i = 0; gap; gap >>= 1, ++i) {
		if (gap & 1) {
			v = fa[v][i];
		}
	}
	if (u == v) return u;
	for (int i = M - 1; i >= 0; --i) {
		if (fa[u][i] == fa[v][i]) continue;
		u = fa[u][i];
		v = fa[v][i];
	}
	return u;
}

int dis(int u, int v) {
	return deep[u] + deep[v] - 2 * deep[querylca(u, v)];
}

int querykth(int u, int k) {
	for (int i = M - 1; i >= 0; --i) {
		if ((k >> i) & 1) {
			u = fa[u][i]; 
		}
	}
	return u;
}

struct BIT {
	pii a[N];
	void init() {
		memset(a, -1, sizeof a);
	}
	void update(int x, pii v) {
		for (; x > 0; x -= x & -x) {
			a[x] = max(a[x], v);
		}
	}
	pii query(int x) {
		pii res = pii(-1, -1);
		for (; x < N; x += x & -x) {
			res = max(res, a[x]);
		}
		return res;
	}
}bit;

int find(int O, int x, int Dis) {
	//在子树内
	if (in[x] >= in[O] && in[x] <= out[O]) {
		return querykth(x, deep[x] - deep[O] - Dis);
	} else { //子树外
		int lca = querylca(O, x);
		if (deep[O] - deep[lca] >= Dis) {
			return querykth(O, Dis);
		} else {
			return querykth(x, deep[x] - deep[lca] - (Dis - deep[O] + deep[lca]));
		}
	}
}

void work(int x, int y) {
	int O = qrr[x].id;
	for (int i = 0; i < 3; ++i) {
	    //assert(qrr[x].x[i].fi >= qrr[y].x[i].fi);
		assert(qrr[y].x[i].se != -1);
		//	assert(dis(O, qrr[x].x[i].se) >= qrr[y].x[i].fi);	
		ans[qrr[y].id].x[i] = pii(find(O, qrr[x].x[i].se, qrr[y].x[i].fi), qrr[y].x[i].se);
	}
}

int main() {
	int x = 2, y = 3;
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1); cnt = 0;
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			++u, ++v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		fa[1][0] = 1;
		g[1] = pii(0, 1);  
		deep[1] = 0;
		DFS(1); DFS2(1);
		scanf("%d", &q);
		m = 0;
		for (int i = 1, a, b, c; i <= q; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			int Max = max(a, max(b, c));
			int Sum = a + b + c;
			if (Sum - Max < Max || Sum % 2) {
				ans[i].x[0].fi = -1;
			} else { 
				qrr[++m] = node(pii((a + b - c) / 2, 0), pii((a + c - b) / 2, 1), pii((b + c - a) / 2, 2), 1, i);
			}
		}
		vector <pii> vec;
		for (int i = 1; i <= n; ++i) {
			vec.clear();
			for (int j = 0; j < 3; ++j) { 
				if (f[i][j].se != -1) {
					vec.push_back(f[i][j]);
				}
			}
			vec.push_back(g[i]);
			sort(vec.begin(), vec.end(), [](pii x, pii y) {
				return x.fi > y.fi;			
			});
	//		vec.erase(unique(vec.begin(), vec.end()), vec.end());
			if ((int)vec.size() >= 3) {
			//	printf("%d %d %d %d\n", i, vec[0].se, vec[1].se, vec[2].se);
				qrr[++m] = node(vec[0], vec[1], vec[2], 0, i);
			}	
		}
		sort(qrr + 1, qrr + 1 + m);
		bit.init();
		for (int i = 1; i <= m; ++i) {
			if (qrr[i].op == 0) {
				bit.update(qrr[i].x[1].fi, pii(qrr[i].x[2].fi, i));
			} else {
				pii tmp = bit.query(qrr[i].x[1].fi);
				if (tmp.fi >= qrr[i].x[2].fi) {
					work(tmp.se, i);  
				} else {
					ans[qrr[i].id].x[0].fi = -1;
				}
			}
		}
		for (int i = 1; i <= q; ++i) {
			if (ans[i].x[0].fi == -1) puts("-1");
			else {
				ans[i].reset();
				printf("%d %d %d\n", ans[i].x[0].fi - 1, ans[i].x[1].fi - 1, ans[i].x[2].fi - 1); 
			}
		}
	}
	return 0;
}
