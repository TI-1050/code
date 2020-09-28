#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e5 + 10;

struct Edge {
	int u, v, w;

	Edge() {}

	Edge(int u, int v, int w): u(u), v(v), w(w) {}

	bool operator < (const Edge &other) const {
		return w > other.w;
	}

	void input() {
		scanf("%d %d %d", &u, &v ,&w);
	}
}edge[N << 1];

int n, m;
int fa[N], sze[N], mark[N];

void Init() {
	for (int i = 1; i <= n; ++i) {
		fa[i] = i, sze[i] = 1, mark[i] = 0;
	}
}

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool Union(int x, int y) {
	x = find(x), y = find(y);
	if (mark[x] != 0 && mark[y] != 0 && mark[x] != mark[y]) return false;
	if (sze[x] > sze[y]) swap(x, y);
	fa[x] = y;
	sze[y] += sze[x];
	if (!mark[y]) mark[y] = mark[x];
	return true;
}

ll gao() {
	sort(edge + 1, edge + 1 + n - 1);
	ll res = 0;
	for (int i = 1; i < n; ++i) {
		int u = edge[i].u, v = edge[i].v, w = edge[i].w;
		if (!Union(u, v)) {
			res += w;
		}
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		Init();
		for (int i = 1; i < n; ++i) {
			edge[i].input();
		}
		scanf("%d", &m);
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			mark[x] = 1;
		}
		scanf("%d", &m);
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			mark[x] = 2;
		}
		ll res = gao();
		printf("%lld\n", res);
	}
	return 0;
}
