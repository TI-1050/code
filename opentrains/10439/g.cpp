#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int n, fa[N], deep[N], f[N], Min;
vector <vector<int>> G;

void DFS(int u) {
	if (G[u].empty()) {
		f[u] =1;
	} else {
		f[u] = -1;
	}
	for (auto v : G[u]) {
		deep[v] = deep[u] + 1;
		DFS(v);
		f[u] += f[v];	
	}
	f[u] = max(f[u], 0);
}

void DFS2(int u) {
	if (G[u].empty()) {
		Min = u;
		return;
	}
	int Max = 0;
	for (auto v : G[u]) {
		Max = max(Max, f[v]);
	}
	for (auto v : G[u]) {
		if (f[v] == Max) {
			DFS2(v);
			return;
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 2; i <= n; ++i) {
			scanf("%d", fa + i);
			G[fa[i]].push_back(i);
		}
		Min = 1e9; deep[1] = 0;
		DFS(1);
		DFS2(1);
		if (f[1] > 0) {
			puts("SECOND");
		} else {
			puts("FIRST");
			printf("%d\n", Min);
		}
	}
	return 0;
}
