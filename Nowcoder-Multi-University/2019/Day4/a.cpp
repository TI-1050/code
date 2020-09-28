#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k;
vector <vector<int>> G;
int f[N][2], pos[N][2], g[N], vis[N], res; 

int deep[N], fa[N]; 
void DFS(int u) { 
	if (vis[u]) {
		f[u][0] = deep[u]; 
		pos[u][0] = u;
		f[u][1] = -1;
		pos[u][1] = -1;	
	} else {
		f[u][0] = -1;
		f[u][1] = -1;
		pos[u][0] = -1;
		pos[u][1] = -1;
	}
	for (auto v : G[u]) if (v != fa[u]) {
		deep[v] = deep[u] + 1;
		fa[v] = u;
		DFS(v);
		if (f[v][0] > f[u][0]) {
			f[u][1] = f[u][0];
			pos[u][1] = pos[u][0];
			f[u][0] = f[v][0];
			pos[u][0] = v;
		} else if (f[v][0] > f[u][1]) {
			f[u][1] = f[v][0];
			pos[u][1] = v;  
		}
	}
}

void DFS2(int u) {
	if (u == 1) {
		g[u] = -1;	
	} else {
		g[u] = -1;
		int pre = fa[u];
		if (g[pre] != -1) g[u] = g[pre] + 1;
		if (f[pre][0] != -1 && pos[pre][0] != u) {
			g[u] = max(g[u], 1 + f[pre][0] - deep[pre]);
		} 
		if (f[pre][1] != -1 && pos[pre][1] != u) {
			g[u] = max(g[u], 1 + f[pre][1] - deep[pre]);
		}
	}
	res = min(res, max(f[u][0] - deep[u], g[u]));
	for (auto v : G[u]) if (v != fa[u]) {
		DFS2(v);
	}
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		memset(vis, 0, sizeof vis);
		for (int i = 1, x; i <= k; ++i) {
			scanf("%d", &x);
			vis[x] = 1;
		}
		fa[1] = 0; deep[1] = 0; 
		res = 1e9;
		DFS(1); 
		DFS2(1);
	//	for (int i = 1; i <= n; ++i) printf("%d %d %d %d\n", i, f[i][0] - deep[i], f[i][1], g[i]);
		printf("%d\n", res);
	}
	return 0;
}
