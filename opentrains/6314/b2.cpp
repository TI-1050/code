#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;

struct node {
	int u, w;
	
	node() {}

	node(int u, int w): u(u), w(w){}

	bool operator < (const node &other) const {
		return w > other.w;
	}
};

int n;
int e[N], d[N];
vector<vector<int> >G;

int gao() {
	priority_queue<node> pq;
	int now = n - 1;
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (d[i] == 0) {
			pq.push(node(i, e[i]));
		}
	}
	while (!pq.empty()) {
		int u = pq.top().u; pq.pop();
		res = max(res, now + e[u]);
		now--;
		for (auto &v: G[u]) {
			--d[v];
			if (d[v] == 0) {
				pq.push(node(v, e[v]));
			}
		}
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear();
		G.resize(n + 1);
		memset(d, 0, sizeof d);
		for (int i = 1, m, x; i <= n; ++i) {
			scanf("%d %d", e + i, &m);
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &x);
				G[i].push_back(x);
				d[x]++;
			}
		}
		printf("%d\n", gao());
	}
	return 0;
}
