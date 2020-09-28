#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 500010

struct Edge{
	int u, v, w;
	
	void input() {
		scanf("%d %d %d", &u, &v, &w);
	}

	bool operator < (const Edge &other) const {
		return w > other.w;
	}
}e[N];
	
int n, m;
int fa[N];

int find(int x) {
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

ll gao() {
	sort(e + 1, e + 1 + m);
	ll res = 0;
	for (int i = 1; i <= m; ++i) {
		if (e[i].w < 0) continue;
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) == find(v)) {
			continue;
		} else {
			u = find(u), v = find(v);
			fa[u] = v;
			res += w;
		}
	}
	return res;
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) fa[i] = i;
		ll sum = 0;
		for (int i = 1; i <= m; ++i) {
			e[i].input();
			sum += e[i].w;
		}
		sum -= gao();
		printf("%lld\n", sum);
	}
	return 0;
}
