#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e5 + 10;
int n;
vector <vector<int>> G;
ll tmp[N * 10], *f[N], *g[N], *id = tmp, res;   
int fa[N], hson[N], md[N];
void dfs(int u) {
	md[u] = 1;
	hson[u] = 0;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		dfs(v);
		md[u] = max(md[u], md[v] + 1);
		if (!hson[u] || md[v] > md[hson[u]]) hson[u] = v;
	}
}

void dfs2(int u) {
	if (hson[u]) {
		int v = hson[u];
		f[v] = f[u] + 1;
		g[v] = g[u] - 1;
		dfs2(v);
	}
	f[u][0] = 1;
	res += g[u][0]; 
	for (auto &v : G[u]) if (v != fa[u] && v != hson[u]) {
		f[v] = id; id += md[v] * 2;
		g[v] = id; id += md[v] * 2;
		dfs2(v);
		for (int i = 1; i <= md[v]; ++i) {
			res += g[u][i] * f[v][i - 1];
			res += g[v][i] * f[u][i - 1]; 
		}
		for (int i = 0; i <= md[v]; ++i) { 
			if (i) g[u][i] += f[u][i] * f[v][i - 1]; 
			if (i) f[u][i] += f[v][i - 1];
			g[u][i] += g[v][i + 1];
		}
	}
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		memset(tmp, 0, sizeof tmp);
		G.clear(); G.resize(n + 1);
		res = 0;
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		fa[1] = 1; 
		dfs(1);
		id = tmp;
		f[1] = id, id += md[1] * 2;
		g[1] = id; id += md[1] * 2; 
		dfs2(1);
		printf("%lld\n", res);
	}
	return 0;
}
