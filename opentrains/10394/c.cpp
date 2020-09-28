#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, x, y, res, a[N], b[N], vis[N];
int fac[110];
bool ok(int x) {
	for (int i = 1; i <= n; ++i)
		if (x > a[i])
			return false;
	return true;
}
vector <vector<int>> G;
vector <int> vec;
void dfs(int u, int cnt) {
	if (cnt == y) {
		++res;
		return;
	}
	if (u > n) return;
	dfs(u + 1, cnt);
	for (auto &v : G[u]) {
		if (!vis[v]) {
			vis[v] = 1;
			dfs(u + 1, cnt + 1);
			vis[v] = 0;
		}
	}
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < 15; ++i) fac[i] = fac[i - 1] * i;
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(n + 1);
		memset(vis, 0, sizeof vis);
		vec.clear();
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		x = y = 0;
		for (int i = 1; i <= n; ++i) {
			if (ok(b[i])) ++x;
			else {
				++y;
				vec.push_back(b[i]);
			}
		}
		if (x == n) {
			printf("%lld\n", fac[x]);
			continue;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < y; ++j) {
				if (a[i] >= vec[j])
					G[i].push_back(j);
			}
		}
	//	for (int i = 1; i <= n; ++i) {
	//		for (auto &it : G[i]) {
	//			cout << it << " ";
	//		}
	//		cout << endl;
	//	}
		res = 0;
		dfs(1, 0);
		printf("%lld\n", res * fac[x]);
	}
	return 0;
}
