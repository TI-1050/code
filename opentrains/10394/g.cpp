#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 10;
int n, m; char G[N][N], h[N][N];
bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}
void dfs(int x, int y, int dy) {
	G[x][y] = '#';
	int nx, ny;
	//down
	bool flag = 0;
	nx = x + 1, ny = y;
	if (ok(nx, ny) && G[nx][ny] == '.') {
		dfs(nx, ny, 0); 
		flag = 1;
	}
	if (!flag) {
		if (dy) {
			nx = x, ny = y + dy;
			if (ok(nx, ny) && G[nx][ny] == '.') {
				dfs(nx, ny, dy);
			}
		} else {
			nx = x, ny = y - 1; 
			if (ok(nx, ny) && G[nx][ny] == '.') {
				dfs(nx, ny, -1); 
			}
			nx = x, ny = y + 1;
			if (ok(nx, ny) && G[nx][ny] == '.') {
				dfs(nx, ny, 1); 
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%s", G[i] + 1);
			for (int j = 1; j <= m; ++j)
				h[i][j] = G[i][j];
			h[i][m + 1] = 0;
		}
		for (int i = 1; i <= m; ++i) {
			if (G[1][i] == '.') {
				dfs(1, i, 0); 
			}
		}
//		for (int i = 1; i <= n; ++i)
//			printf("%s\n", G[i] + 1);
		bool flag = 0;
		for (int i = 1; i <= n && flag == 0; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (G[i][j] == '.') {
					h[i][j] = 'X';
					flag = 1;
					break;
				}
			}
		}
		if (!flag) puts("No");
		else {
			puts("Yes");
			for (int i = 1; i <= n; ++i)
				printf("%s\n", h[i] + 1);
		}
	}
	return 0;
}
