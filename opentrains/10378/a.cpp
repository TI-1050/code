#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, m, d[N], nd[N], fa[N], vis[N], rt_1, rt_3; 
vector <vector<int>> G;
int find(int x) { return fa[x] == 0 ? x : fa[x] = find(fa[x]); }
void join(int x, int y) { x = find(x), y = find(y); if (x != y) fa[x] = y; }
bool connected() {
	memset(fa, 0, sizeof fa);
	for (int u = 1; u <= n; ++u)
		for (auto &v : G[u])
			join(u, v);
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
		cnt += (fa[i] == 0);
	return cnt == 1;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(d, 0, sizeof d);
		memset(nd, 0, sizeof nd);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			++d[u]; ++d[v];
		}
		if (!connected()) puts("No");
		else {
			int d4 = 0;
			for (int i = 1; i <= n; ++i) ++nd[d[i]], d4 += (d[i] > 3);
			if (d4 || nd[3] != 1 || nd[1] != 1) puts("No");
			else {
				puts("Yes");
			//	for (int i = 1; i <= n; ++i) {
			//		if (d[i] == 1) rt_1 = i;
			//		if (d[i] == 3) rt_3 = i;
			//	}
			//	memset(vis, 0, sizeof vis);
			//	delone(rt_1);		
			}
		}
	}
	return 0;
}
