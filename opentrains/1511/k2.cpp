#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e5 + 10;
int n;
vector <vector<int>> G;
ll tmpf[N * 20], tmpg[N * 20], *f[N], *g[N], *tmp_f = tmpf, *tmp_g = tmpg, res;   
int fa[N], hson[N], deep[N], md[N];
void dfs(int u) {
	md[u] = deep[u];
	hson[u] = 0;
	for (auto &v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		deep[v] = deep[u] + 1;
		dfs(v);
		if (!hson[u] || md[v] > md[hson[u]]) hson[u] = v;
	}
	md[u] = md[hson[u]] + 1; 
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
		f[v] = tmp_f; tmp_f += md[v] * 2;
		g[v] = tmp_g; tmp_g += md[v] * 2;
		dfs2(v);
		for (int i = 1; i <= md[v]; ++i) {
			res += g[u][i] * f[v][i - 1];
			res += g[v][i] * f[u][i - 1]; 
		}
		for (int i = 0; i < md[v]; ++i) {
			//之前的儿子中选择一个点和当前遍历的儿子中选择一个点组成一个点对
			g[u][i + 1] += f[u][i + 1] * f[v][i];
			if (i) g[u][i - 1] += g[v][i];
			f[u][i + 1] += f[v][i];
		}
	//	for (int i = 0; i <= md[v]; ++i) { 
	//		if (i) g[u][i] += f[u][i] * f[v][i - 1]; 
	//		if (i) f[u][i] += f[v][i - 1];
	//		g[u][i] += g[v][i + 1];
	//	}
	}
}

int main() {
	scanf("%d", &n);
	G.clear(); G.resize(n + 1);
	memset(tmpf, 0, sizeof tmpf);
	memset(tmpg, 0, sizeof tmpg);
	res = 0;
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	fa[1] = 1; deep[1] = 1;
	dfs(1);
	tmp_f = tmpf; tmp_g = tmpg;
	f[1] = tmp_f, g[1] = tmp_g; tmp_f += md[1] * 2; tmp_g += md[1] * 2;
	dfs2(1);
	printf("%lld\n", res);
	return 0;
}
