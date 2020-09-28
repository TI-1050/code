#include <bits/stdc++.h>
using namespace std;

const int N = 3e3 + 10;
const int mod = 1e9 + 7;
int n, m, w[N], ans, all, rt;
int val[N], sze[N], msze[N], vis[N], f[N][N], tmp[N];
vector <vector<int>> G;
void up(int &x, int y) { x += y; if (x >= mod) x -= mod; }
void chmax(int &x, int y) { if (x < y) x = y; }

void findroot(int u, int fa) {
	sze[u] = 1; 
	msze[u] = 0;
	for (auto v : G[u]) if (v != fa && !vis[v]) {
		findroot(v, u);  
		sze[u] += sze[v];
		chmax(msze[u], sze[v]);
	}
	chmax(msze[u], all - sze[u]);
	if (msze[u] < msze[rt]) rt = u; 
}

void calc(int u, int fa) {
	for (auto v : G[u]) if (v != fa && !vis[v]) {
		for (int i = 1; i <= val[0]; ++i) f[v][i] = 0;
		for (int i = 1, j = 1, k = w[v]; i <= val[0]; ++i) {
			int t = val[i] / k;
			if (!t) continue;
			while (val[j] > t) ++j;
			up(f[v][j], f[u][i]);
		}
		calc(v, u);
		for (int i = 1; i <= val[0]; ++i) up(f[u][i], f[v][i]); 
	}
}

void gao(int u) {
	for (int i = 1; i <= val[0]; ++i) f[u][i] = (m / w[u] == val[i] ? 1 : 0);
	vis[u] = 1;
	calc(u, 0);
	for (int i = 1; i <= val[0]; ++i) up(ans, f[u][i]);
	for (auto v : G[u]) if (!vis[v]) {
		msze[0] = all = sze[v];
		findroot(v, rt = 0);
		gao(rt); 
	}
}

void gogogo() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", w + i);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u,  &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	val[0] = 0;
	for (int i = 1, j; i <= m; i = j + 1) {
		j = m / (m / i);
		val[++val[0]] = m / i;
	}
	for (int i = 1; i <= n; ++i) vis[i] = 0;
	ans = 0;
	msze[0] = all = n;
	findroot(1, rt = 0); gao(rt);
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) gogogo();
	return 0;
}
