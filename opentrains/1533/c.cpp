#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
int n, m, p, F;
int x[N], y[N]; 
bitset <510> bt[2010];

void work(int x, int i) {
	if (bt[x].any()) {
		F = 1;
		if (bt[x][0] == 0) {
			bt[x] >>= 1;
		} else {
			if (bt[0][i] == 0) {
				bt[0][i] = 1;
				bt[x] >>= 1;
			} else {
				for (int j = 0; j < m - 1; ++j) {
					if (bt[x][j] == 0) {
						bt[x][j] = bt[x][j + 1];
						bt[x][j + 1] = 0;
					}
				}
			}
		}
	}
}

int main() {
	while (scanf("%d%d%d", &n, &m, &p) != EOF) {
		for (int i = 0; i <= 2 * n; ++i) {
			bt[i].reset(); 
		}
		for (int i = 1, x, y; i <= p; ++i) {
			scanf("%d%d", &x, &y);
			x = n - x + 1;
			if (y > m) {
				bt[x * 2][y - 1 - m] = 1; 
			} else {
				bt[x * 2 - 1][m - y] = 1;
			}
		}
		ll res = 0;
		while (1) {
			F = 0;
			if (bt[0].any()) {
				bt[0] >>= 1;
				F = 1;
			}
			for (int i = 1; i <= n; ++i) {
				work(i * 2 - 1, i - 1);
				work(i * 2, i - 1);
			}
			res += F;
			if (!F) break;
		}
		printf("%lld\n", res);
	}
	return 0;
}
