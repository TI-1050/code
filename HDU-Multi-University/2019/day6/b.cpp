#include <bits/stdc++.h>
using namespace std;

#define N 50010
#define INF 0x3f3f3f3f
int n, a[N], b[N];
int f[2][N], g[2][N], res[N]; 

struct BIT {
	int a[N];
	void init() {
		memset(a, 0x3f, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] = min(a[x], v);
		}
	}
	int query(int x) {
		int res = INF;
		for (; x > 0; x -= x & -x) {
			res = min(res, a[x]);
		}
		return res;
	}
}bit;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i), g[1][b[i]] = i;
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			res[i] = f[1][i] = 1;
		}	
		int lst = 1; 
		for (int i = 2; i <= n; ++i) {
			if (lst == 0) break;
			int p = i & 1;
			bit.init();
			lst = 0;
		    for (int j = 1; j <= n; ++j) f[p][j] = 0, g[p][j] = n + 1; 	
			for (int j = 1; j <= n; ++j) {
				int t = max(g[p ^ 1][j], bit.query(a[j] - 1));
			//	cout << t << endl;
				if (t <= n) {
				// 	puts("bug");	
					f[p][j] = 1;
					g[p][j] = t;
					lst = 1;
					res[t] = i;
				}
				if (f[p ^ 1][j]) {
					bit.update(a[j], g[p ^ 1][j]);
				}
			}
	//		cout << lst << endl;
		//	for (int j = 1; j <= n; ++j)
		//		printf("%d%c", f[p][j], " \n"[j == n]);
		}
		for (int i = 1; i <= n; ++i) {
			res[i] = max(res[i], res[i - 1]);
			printf("%d%c", res[i], " \n"[i == n]);
		}
	}
	return 0;
}
