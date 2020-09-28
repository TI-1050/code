#include <bits/stdc++.h>
using namespace std;

#define N 300010
int n, m, l[N], r[N], d[N];
vector <vector<int>> G;

bool Toposort() {
	queue <int> q;
	for (int i = 1; i <= n; ++i) {
		if (d[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", l + i, r + i);
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			++d[u]; ++d[v];
		}
		if (!Toposort()) {
		
		}
	}
	return 0;
}
