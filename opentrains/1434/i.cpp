#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e5 + 10;
int n, a[N], d[N], fa[N];
ll t[N]; 
vector < vector <int> > G;

void pre(int u) {
	for (auto v : G[u]) if (v != fa[u]) {
		fa[v] = u;
		d[v] = d[u] + 1;
		pre(v);  
	}
}

void DFS(int u, ll Min) {
	t[u] = min(1ll * -a[u], Min);
	for (auto v : G[u]) if (v != fa[u]) {
		DFS(v, t[u]);
	}
}

struct node {
	int u, t;
	node() {}
	node(int u, int t) : u(u), t(t) {}
	bool operator < (const node &other) const {
		return t > other.t;
	}
};

ll gao() {
	DFS(1, 2e9);	
	memset(d, 0, sizeof d);
	for (int i = 2; i <= n; ++i) {
		++d[fa[i]];
	}
	priority_queue <node> pq;
	for (int i = 1; i <= n; ++i) if (!d[i]) {
		pq.push(node(i, t[i]));
	}
	int cnt = 0;
	ll res = 0;
	while (!pq.empty()) {
		node it = pq.top(); pq.pop();
		res = max(res, 1ll * cnt - it.t);
		++cnt;
		if (it.u == 1) return res;
		int v = fa[it.u];
		if (--d[v] == 0) {
			pq.push(node(v, t[v]));
		}
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u); 
		} 
		d[1] = 0; pre(1);
		for (int i = 1; i <= n; ++i) a[i] += d[i]; 
	   	printf("%lld\n", gao());
	}
	return 0;
}
