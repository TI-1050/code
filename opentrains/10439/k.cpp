#include <bits/stdc++.h>
using namespace std;

//0 red
//1 black
#define N 5100
vector <vector<int>> G;
int n, m, fa[N], root;
int f[N][N][2];
char res[N];

void DFS(int u) {
	if (G[u].empty()) {
		f[u][1][1] = 1;
		return;		
	}
	int ls = G[u][0];
	int rs = G[u][1];
	DFS(ls); DFS(rs); 
	for (int i = 1; i <= m; ++i) {
		f[u][i][0] = f[ls][i][1] & f[rs][i][1];
		f[u][i + 1][1] = (f[ls][i][0] | f[ls][i][1]) & (f[rs][i][0] | f[rs][i][1]); 
	}
}

void DFS2(int u, int x, int y) {
	if (G[u].empty()) return;
	int ls = G[u][0];
	int rs = G[u][1];  
	if (y == 1) { 
		--x;
	}
	if (f[u][x][0] && y != 0) {
		res[u] = 'R';
		y = 0;
	} else {
		assert(f[u][x][1]);
		res[u] = 'B';
		y = 1;
	}
	DFS2(ls, x, y);
	DFS2(rs, x, y);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear(); G.resize(N); 
		for (int i = 1; i <= n; ++i) {
			scanf("%d", fa + i);
			if (!fa[i]) {
				root = i;
			} else {
				G[fa[i]].push_back(i);  
			}
		}
		m = n;
		for (int i = 1; i <= n; ++i) {
			while (G[i].size() < 2) {
				G[i].push_back(++m);
				fa[m] = i;
			}
		}
		memset(f, 0, sizeof f);
		DFS(root);
		int ok = 0;
		for (int i = 1; i <= m; ++i) {
			if (f[root][i][0] || f[root][i][1]) {
				DFS2(root, i, -1);
				ok = 1;
				break;
			}
		}
		if (!ok) {
			puts("Impossible");
		} else {
			for (int i = 1; i <= n; ++i) {
				putchar(res[i]);
			}
			puts("");
		}
	}
	return 0;
}
