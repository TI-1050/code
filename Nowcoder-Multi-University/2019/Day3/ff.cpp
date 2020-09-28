#include <bits/stdc++.h>
using namespace std;

#define N 510
#define INF 0x3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second
int a[N][N];
int g[2][N], que[2][N], l[2], r[2]; 

int main() {
	int n, m;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				scanf("%d", &a[i][j]);
			}
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				g[0][j] = -INF;
				g[1][j] = INF;
			}
			for (int j = i; j <= n; ++j) {  
				l[0] = l[1] = 1;
				r[0] = r[1] = 0;
				int pos = 1;
				for (int k = 1; k <= n; ++k) {
					g[0][k] = max(g[0][k], a[j][k]);
					g[1][k] = min(g[1][k], a[j][k]);   
					while (l[0] <= r[0] && g[0][k] >= g[0][que[0][r[0]]]) --r[0];
					que[0][++r[0]] = k;
					while (l[1] <= r[1] && g[1][k] <= g[1][que[1][r[1]]]) --r[1];
					que[1][++r[1]] = k;
					while (pos <= k && g[0][que[0][l[0]]] - g[1][que[1][l[1]]] > m) {
						++pos;
						for (int o = 0; o < 2; ++o) {
							while (l[o] <= r[o] && que[o][l[o]] < pos) ++l[o];
						}
					}
					if (pos <= k) {
						res = max(res, (j - i + 1) * (k - pos + 1));
					}
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
