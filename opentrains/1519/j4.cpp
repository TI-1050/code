#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 4e3 + 10;
const int INF = 0x3f3f3f3f; 
int n, m, a[N], b[N], c[N], g[N][N], f[N][2];
struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] = max(a[x], v); 
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x)
			res = max(res, a[x]);
		return res;
	}
}bit;


struct BIT2 {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x > 0; x -= x & -x)
			a[x] = max(a[x], v); 
	}
	int query(int x) {
		int res = 0;
		for (; x < N; x += x & -x)
			res = max(res, a[x]);
		return res; 
	}
}bit2;

int main() {
	while (scanf("%d", &n) != EOF) {
		*c = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), c[++*c] = a[i];
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) scanf("%d", b + i), c[++*c] = b[i];
		sort(c + 1, c + 1 + *c); *c = unique(c + 1, c + 1 + *c) - c - 1;
		for (int i = 1; i <= n; ++i) a[i] = lower_bound(c + 1, c + 1 + *c, a[i]) - c;
		for (int i = 1; i <= m; ++i) b[i] = lower_bound(c + 1, c + 1 + *c, b[i]) - c;
	    memset(g, 0, sizeof g);	
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				g[i][j] = max(g[i - 1][j], g[i][j - 1]);
				if (a[i] == b[j]) {
					g[i][j] = max(g[i][j], g[i - 1][j - 1] + 1);
				} 
			}
		}
		int res = min(2, g[n][m]);
		for (int i = 1; i <= n; ++i) {
			bit.init(); bit2.init();
			for (int j = 1; j <= m; ++j) {
				int t[2] = {0, 0};
				if (a[i] == b[j]) {
					t[1] = bit.query(b[j] - 1) + 1;
					t[0] = bit2.query(b[j] + 1) + 1;
				}
				bit.update(b[j], f[j][0]);
				bit2.update(b[j], f[j][1]);
				f[j][0] = max(f[j][0], t[0]);
				f[j][1] = max(f[j][1], t[1]);
				res = max(f[j][0], res);
				res = max(f[j][1], res);
			}
		}
		printf("%d\n", res);
	}	
	return 0;
}
