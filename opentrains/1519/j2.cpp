#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 2e3 + 10;
const int INF = 0x3f3f3f3f; 
int n, m, a[N], b[N], g[N][N];
pII f[N][N][2];
void up(pII &x, pII y) {
	if (x.fi < y.fi) x = y;
	else if (x.fi == y.fi && x.se > y.se) x = y;
}
void down(pII &x, pII y) {
	if (x.fi < y.fi) x = y;
	else if (x.fi == y.fi && x.se < y.se) x = y;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) scanf("%d", b + i);
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j) {
				f[i][j][0] = pII(0, -INF);
				f[i][j][1] = pII(0, INF);
			}
	    memset(g, 0, sizeof g);	
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				up(f[i][j][0], f[i - 1][j][0]);
				up(f[i][j][0], f[i][j - 1][0]);
				down(f[i][j][1], f[i - 1][j][1]);
				down(f[i][j][1], f[i][j - 1][1]);
				g[i][j] = max(g[i - 1][j], g[i][j - 1]);
				if (a[i] == b[j]) {
					g[i][j] = max(g[i][j], g[i - 1][j - 1] + 1);
					if (a[i] > f[i - 1][j - 1][0].se) 
						down(f[i][j][1], pII(f[i - 1][j - 1][0].fi + 1, a[i]));
					if (a[i] < f[i - 1][j - 1][1].se)
						up(f[i][j][0], pII(f[i - 1][j - 1][1].fi + 1, a[i]));
				} 
			}
		}
	//	cout << f[n][m][0].fi << " " << f[n][m][1].fi << endl;
		int res = max(f[n][m][0].fi, f[n][m][1].fi);
		res = max(res, min(2, g[n][m]));
		printf("%d\n", res);
	}	
	return 0;
}
