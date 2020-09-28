#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
int n, e[N], f[N], d[N], ord[N]; 
vector <vector<int>> G;
struct node {
	int u, w;
	node() {}
	node(int u, int w) : u(u), w(w) {}
	bool operator < (const node &other) const {
		return w > other.w;
	}
};
int Toposort() {
	priority_queue <node> pq;
	for (int i = 1; i <= n; ++i) if (!d[i]) {
		pq.push(node(i, f[i]));
	}
	int ans = 0;
	*ord = 0;
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		ans = max(ans, *ord + e[u]);
		ord[++*ord] = u;
		for (auto &v : G[u]) if (--d[v] == 0)
			pq.push(node(v, f[v]));		
	}
	return ans;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(d, 0, sizeof d);
		for (int i = 1, m, x; i <= n; ++i) {
			scanf("%d%d", e + i, &m); 
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &x);
				G[x].push_back(i);
				++d[i];
			}
		}
		Toposort();
		for (int i = 1; i <= n; ++i) 
			for (auto &v : G[i]) ++d[v];
		for (int i = *ord; i >= 1; --i) {
			f[i] = -e[i];
			for (auto &v : G[i]) f[i] = min(f[i], f[v]); 
		}
		printf("%d\n", Toposort());
	}
	return 0;
}
