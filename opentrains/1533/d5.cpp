#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define N 4010
int n, m;
char s[N], t[N], str[N];
int dp[N][N];
int f[N][2], g[N][2];
int nx[2], ny[2];
struct node {
	
}

void up(int i, int j, int x, int y) {
	dp[x][y] = min(dp[x][y], dp[i][j] + 1);  
}

bool work(int nx[][2], int n, char *str) {
	int len = strlen(str + 1);
	for (int i = 1, j = 0; i <= len; ++i) {
		j = nx[j][str[i] - '0'];
		if (j == n + 1) {
			return 0;
		}
	}
	return 1;
}

bool ok() {
	if (work(f, n, str) || work(g, m, str)) {
		return 0;
	}
	return 1;
}

int main() {
	while (~scanf("%s %s", s + 1, t + 1)) {
		n = strlen(s + 1);
		m = strlen(t + 1);
		memset(dp, 0x3f, sizeof dp);
		for (int i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= m + 1; ++j) {
				pre[i][j] = node();
			}
		}
		nx[0] = nx[1] = n + 1;
		for (int i = n; i >= 0; --i) {
			f[i][0] = nx[0];
			f[i][1] = nx[1];
			if (i) {
				nx[s[i] - '0'] = i;
			}
		}
		ny[0] = ny[1] = m + 1;
		for (int i = m; i >= 0; --i) {
			g[i][0] = ny[0];
			g[i][1] = ny[1];
			if (i) {
				ny[t[i] - '0'] = i;
			}
		}
		f[n + 1][0] = n + 1;
		f[n + 1][1] = n + 1;
		g[m + 1][0] = m + 1;
		g[m + 1][1] = m + 1;
		dp[nx[0]][ny[0]] = 1;
		dp[nx[1]][ny[1]] = 1;
		int c;
		for (int i = 1; i <= n + 1; ++i) {
			for (int j = 1; j <= m + 1; ++j) if (dp[i][j] != INF) {
				if (i == n + 1 && j == m + 1) continue; 
				up(i, j, f[i][0], g[j][0]);
				up(i, j, f[i][1], g[j][1]);
				if (i != n + 1) {
					up(i, j, c, i, g[j][c]);
				}
				if (j != m + 1) {
					up(i, j, c, f[i][c], j);
				}
			}
		}
			
		node it = pre[n + 1][m + 1];
		int cnt = 0;
		while (it.x != 0 && it.y != 0) {
			str[++cnt] = it.c + '0';
			it = pre[it.x][it.y];
		}
		reverse(str + 1, str + 1 + cnt); 
		str[++cnt] = '0';
		str[cnt + 1] = 0;
		if (ok()) {
			printf("%s\n", str + 1);
		} else {
			str[cnt] = '1';
			printf("%s\n", str + 1);
		}
	}
	return 0;
}
