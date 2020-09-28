#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, S, T;
vector <vector<int>> G;

int fa[N], sze[N];
ll f[N], g[N];
void DFS(int u) {
	sze[u] = 1;
	f[u] = 0; 
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		DFS(v);
		sze[u] += sze[v];
		f[u] += f[v]; 
		f[u] += 1ll * sze[v] * (n - sze[v]);
	}
}

ll DFS2(int u, int rt, int S) {
	if (u != rt) {
		g[u] = g[fa[u]] + f[fa[u]] - f[u] + 1ll * (n - sze[u] - S) * (sze[u] + S) - 1ll * sze[u] * (n - sze[u]);
	} else {
		g[u] = 0;
	}
	ll res = f[u] + g[u]; 
	for (auto v : G[u]) if (v != fa[u]) {
		res = min(res, DFS2(v, rt, S)); 
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) fa[i] = -1;
		for (int i = 1, u, v; i < n - 1; ++i) {
			scanf("%d%d", &u, &v);    
			G[u].push_back(v);
			G[v].push_back(u);
		}
		int rt[2]; rt[0] = 1;
		fa[1] = 1;
		DFS(1); S = sze[1]; T = n - S;
		for (int i = 1; i <= n; ++i) {
			if (fa[i] == -1) {
				rt[1] = i;
				fa[i] = i;
				DFS(i);
				break;
			}
		}
		ll res = DFS2(1, 1, T) + DFS2(rt[1], rt[1], S) + 1ll * S * T;
		printf("%lld\n", res);
	}
	return 0;
}
