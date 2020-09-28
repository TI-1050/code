#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 4e5 + 10, M = 23;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, e[N][3], ans[N];

struct Dijkstra {
	vector <vector<pII>> G;
	bool used[N]; ll dis[N];
	void init() { G.clear(); G.resize(n + 1); }
	inline void addedge(int u, int v, int w) { G[u].emplace_back(v, w); }
	struct node {
		int u; ll w;
		node() {}
		node(int u, ll w) : u(u), w(w) {}
		bool operator < (const node &other) const {
			return w > other.w;
		}
	};
	void gao(int S) {
		for (int i = 1; i <= n; ++i) {
			used[i] = 0;
			dis[i] = INFLL;
		}
		dis[S] = 0;
		priority_queue<node> pq;
		pq.emplace(S, 0);
		while (!pq.empty()) {
			int u = pq.top().u; pq.pop();
			if (used[u]) continue;
			used[u] = 1;
			for (auto &it : G[u]) {
				int v = it.fi, w = it.se;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					pq.emplace(v, dis[v]);
				}
			}
		}	
	}
}dij;

struct Dominator_Tree {
	int f[N][M], deep[N], d[N], sze[N], que[N], l, r;
	//0 原图 1 反图 2 支配树中的边
	vector <vector<pII>> G[3]; 
	void init() {
		for (int i = 0; i < 3; ++i) {
			G[i].clear();
			G[i].resize(n + 10);
		}
		memset(d, 0, sizeof d);
	}
	inline void addedge(int id, int u, int v, int w) {
//		if (!id) cout << u << " " << v << endl;
		G[id][u].emplace_back(v, w);
	}
	void add(int fa, int x, int id) {
		if (fa != x) addedge(2, fa, x, id); 
		f[x][0] = fa; deep[x] = deep[fa] + 1;
		for (int i = 1; i < 20; ++i)
			f[x][i] = f[f[x][i - 1]][i - 1];
	}
	int querylca(int u, int v) {
		if (!u) return v;
		if (!v) return u;
		if (deep[u] > deep[v]) swap(u, v);
		for (int det = deep[v] - deep[u], i = 0; det; det >>= 1, ++i) {
			if (det & 1) {
				v = f[v][i];		
			}
		}
		if (u == v) return u;
		for (int i = M - 1; i >= 0; --i) {
			if (f[u][i] == f[v][i])
				continue;
			u = f[u][i];
			v = f[v][i];
		}
		return f[u][0];
	}
    int getlca(int x) {
		int lca = 0;
		for (auto &it : G[1][x]) {
			int v = it.fi;
			lca = querylca(lca, v);
		}
		return lca; 
	}	
	void DFS(int u) {
	//	cout << u << endl;
		sze[u] = 1;
		for (auto &it : G[2][u]) {
			int v = it.fi, id = it.se;
			if (sze[v]) continue;
	//		cout << it.se << " " << v << endl;
			DFS(v);
			sze[u] += sze[v];
			ans[id] = sze[v];
		}
	}
	void work() {
		int S = n + 1; add(S, S, 0);
		l = 1, r = 0;
		for (int i = 1; i <= n; ++i) if (d[i] == 0) { 
			que[++r] = i;
			add(S, i, 0);
		}
		while (l <= r) {
			int u = que[l]; ++l;
			for (auto &it : G[0][u]) {
				int v = it.fi, id = it.se;
				--d[v]; 
				if (d[v] == 0) {
					que[++r] = v; 
				//	cout << id << " " << getlca(v) << " " << v << endl;
					int lca = getlca(v);
					if (lca != u) id = 0;
					add(getlca(v), v, id);
				}
			}
		}
		DFS(S);
	}
}dt;

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(ans, 0, sizeof ans);
		dij.init();
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", e[i], e[i] + 1, e[i] + 2);
			dij.addedge(e[i][0], e[i][1], e[i][2]); 
			dij.addedge(e[i][1], e[i][0], e[i][2]);
		}
		dij.gao(1);
	 //   for (int i = 1; i <= n; ++i) cout << dij.dis[i] << endl;	
		dt.init();
		for (int i = 1; i <= m; ++i) {
			int u = e[i][0], v = e[i][1], w = e[i][2];  
			if (dij.dis[u] + w == dij.dis[v]) { 
				dt.addedge(0, u, v, i);
				++dt.d[v];
				dt.addedge(1, v, u, i);
			}
			if (dij.dis[v] + w == dij.dis[u]) {
				dt.addedge(0, v, u, i);
				++dt.d[u];
				dt.addedge(1, u, v, i);
			}
		}
		dt.work();
		for (int i = 1; i <= m; ++i) 
			printf("%d\n", ans[i]);
	}
	return 0;
}
