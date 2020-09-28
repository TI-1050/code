#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, a[N << 1], f[N][N], res;

int gao(int *a) {
	memset(f, 0, sizeof f);
	for (int len = 2; len <= n; ++len) {
		for (int l = 1; l + len - 1 <= n; ++l) {
			int r = l + len - 1;
			for (int i = l; i < r; ++i)  {
				f[l][r] = max(f[l][r], f[l][i] + f[i + 1][r] + abs(a[l] - a[i + 1]));
			}
		}
	}
	return f[1][n];
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = n + 1; i <= 2 * n; ++i) {
			a[i] = a[i - n];
		}
		res = 0;
		for (int i = 0; i < n; ++i) {
			res = max(res, gao(a + i));
		}
		printf("%d\n", res);
	}
	return 0;
}
