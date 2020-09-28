#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 100;
int n, fa[N], md[N], hson[N], deep[N];
vector < vector <int> > G;
void pre(int u) {
	md[u] = deep[u];
	hson[u] = 0;
	for (auto &v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		pre(v);
		if (!hson[u] || md[v] > md[hson[u]]) hson[u] = v;
	}
	md[u] = md[hson[u]] + 1;
}
//f[u][i] 表示u的子树中和u的距离为i的点数
//g[u][i] 表示u的子树中到lca的距离为d 并且lca到u的距离为d - i的点对数
ll tmpf[N * 20], tmpg[N * 20], *f[N], *g[N], *tmp_f = tmpf, *tmp_g = tmpg, ans;   
void DFS(int u) {
	if (hson[u]) {
		int v = hson[u];
		f[v] = f[u] + 1;
		g[v] = g[u] - 1;
		DFS(v);
	}
	f[u][0] = 1; 
	//这里统计一个点对的点到他们的lca的距离为d，并且u到他们lca距离也为d的方案
	ans += g[u][0];
	for (auto &v : G[u]) {
		if (v == fa[u] || v == hson[u]) continue;
		f[v] = tmp_f; tmp_f += md[v] * 2;
		g[v] = tmp_g; tmp_g += md[v] * 2;
		DFS(v);
		for (int i = 1; i <= md[v]; ++i) {
			ans += g[u][i] * f[v][i - 1];
			ans += g[v][i] * f[u][i - 1];
		}
		for (int i = 0; i < md[v]; ++i) {
			//之前的儿子中选择一个点和当前遍历的儿子中选择一个点组成一个点对
			g[u][i + 1] += f[u][i + 1] * f[v][i];
			if (i) g[u][i - 1] += g[v][i];
			f[u][i + 1] += f[v][i];
		}
	}
}

int main() {
	scanf("%d", &n);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) { 
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	fa[1] = 1; deep[1] = 1;
	pre(1);
	f[1] = tmp_f, tmp_f += md[1] * 2;
	g[1] = tmp_g; tmp_g += md[1] * 2; 
	DFS(1);
	printf("%lld\n", ans);
	return 0;
}
