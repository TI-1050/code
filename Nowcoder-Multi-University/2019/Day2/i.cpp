#include <bits/stdc++.h>
using namespace std;

#define N 60
int n, m;
int G[N][N];

int solve(int x, int y, int n, int m) {
	int res = 0;
	for (int i = x; i <= n; ++i) {
		for (int j = x; j <= n; ++j) {
			int tmp = 0;
			for (int o = y; o <= m; ++o) {
				tmp += G[j][o] - G[i - 1][o];
				res = max(res, tmp);
				if (tmp < 0) tmp = 0;
			}
		}
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", G[i] + j);
			}
		}
		for (int j = 1; j <= m; ++j) {
			for (int i = 1; i <= n; ++i) {
				G[i][j] += G[i - 1][j];
			}
		}
		int res = 0;
		res = max(res, solve(1, 1, n, m));
		for (int i = 1; i < n; ++i) {
			res = max(res, solve(1, 1, i, m) + solve(i + 1, 1, n, m));
		}
		for (int i = 1; i < m; ++i) {
			res = max(res, solve(1, 1, n, i) + solve(1, i + 1, n, m));
		}
		printf("%d\n", res);
	}
	return 0;
}
