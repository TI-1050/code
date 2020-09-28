#include <bits/stdc++.h>

using namespace std;

#define N 4010
struct node {
	int x, y, c;
	node() {}
	node (int x, int y, int c) : x(x), y(y), c(c) {}
}pre[N][N];
int n, m;
char s[N], t[N];
int dp[N][N];
char str[N];
int f[N][2], g[N][2];
int nx[2], ny[2];

int main() {
	while (~scanf("%s %s", s + 1, t + 1)) {
		n = strlen(s + 1);
		m = strlen(t + 1);
		memset(dp, 0x3f, sizeof dp);
		nx[0] = nx[1] = 0;
		for (int i = 1; i <= n; ++i) {
			f[i][0] = nx[0];
			f[i][1] = nx[1];
			nx[s[i] - '0'] = i;
		}
		ny[0] = ny[1] = 0;
		for (int i = 1; i <= m; ++i) {
			g[i][0] = ny[0];
			g[i][1] = ny[1];
			ny[t[i] - '0'] = i;
		}
		f[n + 1][0] = nx[0];
		f[n + 1][1] = nx[1];
		g[m + 1][0] = ny[0];
		g[m + 1][1] = ny[1];
		dp[n + 1][m + 1] = 0;
		for (int  i = n + 1; i >= 0; --i) {
			for (int j = m + 1; j >= 0; --j) {
				if (i == 0 && j == 0) {
					continue;
				}
				if (dp[f[i][1]][g[j][1]] > dp[i][j] + 1) {
					dp[f[i][1]][g[j][1]] = dp[i][j] + 1;
					pre[f[i][1]][g[j][1]] = node(i, j, 1);
				} 
				if (dp[f[i][0]][g[j][0]] > dp[i][j] + 1) {
					dp[f[i][0]][g[j][0]] = dp[i][j] + 1;
					pre[f[i][0]][g[j][0]] = node(i, j, 0);
				}
					if (dp[f[i][0]][g[j][0]] == dp[i][j] + 1) {
						pre[f[i][0]][g[j][0]] = node(i, j, 0); 
					}
			}
		}
		int cnt = 0;
		node st = pre[0][0];
		while (st.x != n + 1 && st.y != m + 1) {
			str[++cnt] = st.c + '0';
			st = pre[st.x][st.y];
		}
		str[++cnt] = st.c + '0';
		for (int i = 1; i <= cnt; ++i) {
			printf("%c", str[i]);
		}
		puts("");
	}
	return 0;
}
