#include <bits/stdc++.h>

using namespace std;

using db = double;

const int N = 160;
const int M = 1e5 + 10;
const db eps = 1e-10;

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;
}

int n, w;
int vis[M], a[M];
db f[N][N], g[N][N];

int main() {
	while (scanf("%d %d", &n, &w) != EOF) {
		for (int i = 1; i < n; ++i) {
			vis[i] = 0;
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n - 1);
		memset(g, 0, sizeof g);
		memset(f, 0, sizeof f);
		for (int i = 1; i <= 150; ++i) {
			for (int j = 1; j <= i; ++j) {
				g[i][j] = w;
			}
		}
		for (int i = 2; i <= 150; ++i) {
			for (int j = 1; j <= i; ++j) {
				f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) / 2.0 + (g[i - 1][j] + g[i - 1][j - 1]) / 2.0;
			}
		}
		for (int i = 2; i <= 150; ++i) {
			sort(f[i] + 1, f[i] + 1 + i, [&](db x, db y) {
				return x > y;
			});
		}
		int res = 1;
		for (int i = 2; i <= 150; ++i) {
			bool F = true;
			for (int j = 1; j <= i; ++j) {
				bool flag = false;
				for (int k = 1; k < n; ++k) {
					if (!vis[k] && sgn(a[k] - f[i][j]) >= 0) {
						flag = true;
						vis[k] = 1;
						break;
					} 
				}
				if (!flag) {
					F = false;
					break;
				}
			}
			if (F) {
				res = i;
			} else {
				break;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
