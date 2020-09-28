#include <bits/stdc++.h>
using namespace std;

using pII = pair <int, int>;
#define fi first
#define se second
const int N = 2510;
int n, m, G[510][510], d[N], d_back[N];
struct Edge { int u, v, use; };
vector <Edge> vec;

bool check(int k) {
	for (auto &it : vec) it.use = 0;
	for (int i = 1; i <= n; ++i) d[i] = d_back[i];
	int cnt = 0;
	while (1) {
		int f = 0;
		for (auto &it : vec) if (!it.use) {
			int u = it.u, v = it.v;
			if (d[u] + d[v] >= k) {
				++d[u];
				++d[v];
				it.use = 1;
				++f;
				++cnt;
			}
		}
		if (!f) break;
	}
	return cnt == vec.size();
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(G, 0, sizeof G);
		memset(d_back, 0, sizeof d_back);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u][v] = G[v][u] = 1;
			++d_back[u]; ++d_back[v]; 
		}
		vec.clear();
		for (int i = 1; i <= n; ++i) 
			for (int j = i + 1; j <= n; ++j) {
				if (G[i][j] == 0)
					vec.push_back({i, j, 0});
			}
		int l = 0, r = n * 2 + 1, res = 0;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			} 
		}
		printf("%d\n", res);
	}
	return 0;
}
