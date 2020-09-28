#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, M = 23;
int n, a[N], f[N][M], g[N][M];

bool check(int x) {
	for (int i = 1; i <= n; ++i) {
		int t = i;
		for (int j = M - 1; j >= 0; --j) {
			if ((x >> j) & 1) {
				t = f[t][j];
			}
		}
		if (t < n) return false;
		t = i;
		for (int j = M - 1; j >= 0; --j) {
			if ((x >> j) & 1) {
				t = g[t][j];
			}
		}
		if (t > 1) return false;
	}
	return true;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 0; i < M; ++i)
			f[n + 1][i] = n + 1;
		for (int i = n; i >= 1; --i) {
			f[i][0] = min(n + 1, i + a[i]);
			for (int j = 1; j < M; ++j)
				f[i][j] = f[f[i][j - 1]][j - 1];
		}
		for (int i = 0; i < M; ++i)
			g[0][i] = 0;
		for (int i = 1; i <= n; ++i) {
			g[i][0] = max(0, i - a[i]);
			for (int j = 1; j < M; ++j) {
				g[i][j] = g[g[i][j - 1]][j - 1];
			}
		}
		int l = 0, r = n, res = n;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
