#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, k;
int fa[N], sze[N];
unordered_map<int, int> vis[N], cant[N];
vector<int> res;

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool Union(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return true;
	if (cant[x].size() > cant[y].size()) swap(x, y);
	for (auto &v : cant[x]) {
		if (vis[y].count(v.first)) return false;
	}
	if (sze[x] > sze[y]) swap(x, y);
	for (auto &v : vis[x]) {
		vis[y][v.first] = 1;
	}
	if (cant[x].size() > cant[y].size()) swap(cant[x], cant[y]);
	for (auto &v : cant[x]) {
		cant[y][v.first] = 1;
	}
	fa[x] = y;
	sze[y] += sze[x];
	vis[x].clear(), cant[x].clear();
	return true;
}

int main() {
	while (scanf("%d %d %d", &n, &k, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i, sze[i] = 1;
			vis[i].clear(), cant[i].clear();
			vis[i][i] = 1;
		}
		res.clear();
		for (int i = 1, u, v; i <= k; ++i) {
			scanf("%d %d", &u, &v);
			cant[u][v] = cant[v][u] = 1;
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d %d", &u, &v);
			if (Union(u, v)) res.push_back(i);
		}
		printf("%d\n", (int)res.size());
		for (int i = 0, sze = res.size(); i < sze; ++i) {
			printf("%d%c", res[i], " \n"[i == sze - 1]);
		}
	}
	return 0;
}
