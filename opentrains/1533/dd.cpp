#include <bits/stdc++.h>

using namespace std;

#define N 4010

int n, m;
char s[N], t[N];
int dp[N][N];
pair<int,int> pre[N][N];
int f[N][2], g[N][2];
int nx[2], ny[2];

int main() {
	while (~scanf("%s %s", s + 1, t + 1)) {
		n = strlen(s + 1);
		m = strlen(t + 1);
		memset(dp, 0x3f, sizeof dp);
		nx[0] = nx[1] = n + 1;
		for (int i = n; i >= 1; --i) {
			f[i][0] = nx[0];
			f[i][1] = nx[1];
			nx[s[i] - '0'] = i;
		}
		ny[0] = ny[1] = m + 1;
		for (int i = m; i >= 1; --i) {
			g[i][0] = ny[0];
			g[i][1] = ny[1];
			ny[t[i] - '0'] = i;
		}
		f[0][0] = nx[0];
		f[0][1] = nx[1];
		g[0][0] = ny[0];
		g[0][1] = ny[1];
		f[n + 1][0] = n + 1;
		f[n + 1][1] = n + 1;
		g[m + 1][0] = m + 1;
		g[m + 1][1] = m + 1;
		dp[0][0] = 0;
		for (int  i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= m + 1; ++j) {
				if (dp[f[i][0]][g[i][0]] < dp[i][j] + 1) {
					dp[f[i][0]][g][i][0] = dp[i][j] + 1;
					pair[f[i][0]][g[i][0] = ]		
				}
				dp[f[i][0]][g[j][0]] = min(dp[f[i][0]][g[j][0]], dp[i][j] + 1);
				dp[f[i][1]][g[j][1]] = min(dp[f[i][1]][g[j][1]], dp[i][j] + 1);
			}
		}
		printf("%d\n", dp[n + 1][m + 1]);
	}
	return 0;
}
