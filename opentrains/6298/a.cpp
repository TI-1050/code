#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e3 + 10, mod = 1e9 + 7;
int n, m, f[N][N][2], g[N][2];
//0表示当前点度数为0  1表示大于0
vector <vector<int>> G;
void chadd(int &x, int y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}
void dfs(int u, int fa) {
	bool f = 0; 
	for (auto &v : G[u]) if (v != fa) {
		dfs(v, u);
		memset(g, 0, sizeof g);  
		
		if (!f) {
			for (int i = 0; i <= m; ++i) {
					
			}
			f = 1;
		}
		//当前边指向u
		for (int i = 0; i <= m; ++i) {
		//	if (f[u][i][0] == 0) break;
			for (int j = 0; i + j <= m; ++j) {
		//		if (f[v][j][1] == 0) break;
				chadd(g[i + j][0], 1ll * f[u][i][0] * f[v][j][1] % mod);
				chadd(g[i + j][1], 1ll * f[u][i][1] * f[v][j][1] % mod);
			    if (i + j < m) {
					chadd(g[i + j + 1][0], 1ll * f[u][i][0] * f[v][j][0] % mod);
					chadd(g[i + j + 1][1], 1ll * f[u][i][1] * f[v][j][0] % mod);
				}
			}
		}

		//当前边指向v
		for (int i = 0; i <= m; ++i) {
		//	if (f[u][i][1] == 0) break;
			for (int j = 0; i + j <= m; ++j) {
		//		if (f[v][j][0] + f[v][j][1] == 0) break;
				chadd(g[i + j][1], 1ll * f[u][i][1] % mod * (f[v][j][0] + f[v][j][1]) % mod);
				if (i + j < m) 
					chadd(g[i + j + 1][1], 1ll * f[u][i][0] * (f[v][j][0] + f[v][j][1]) % mod);
			}
		}
		for (int i = 0; i <= m; ++i) 
			for (int j = 0; j < 2; ++j)
				f[u][i][j] = g[i][j];
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		G.clear(); G.resize(n + 1);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		memset(f, 0, sizeof f);
		dfs(1, 0);
		for (int i = 1; i <= n; ++i) 
			for (int j = 0; j <= m; ++j)
				dbg(i, j, f[i][j][0], f[i][j][1]);
		printf("%d\n", (f[1][m][0] + f[1][m][1]) % mod);
	}
	return 0;
}
