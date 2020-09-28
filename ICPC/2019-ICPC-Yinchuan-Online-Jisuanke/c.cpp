#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 220;
int n, f[N][10][10], pre[N][10][10], a[N], b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", a + i, b + i);
		memset(f, 0, sizeof f);
		memset(pre, -1, sizeof pre); 
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= 8; ++j) {
				for (int k = 1; k <= 8; ++k) { 
					f[i][j][k] = f[i - 1][j][k];
					pre[i][j][k] = pre[i - 1][j][k]; 
					if (f[i - 1][j - 1][k]) {
						if (f[i - 1][j - 1][k] + a[i] > f[i][j][k]) {
							f[i][j][k] = f[i - 1][j - 1][k] + a[i];
							pre[i][j][k] = pii(j - 1, k); 
						}
					}
					if (f[i - 1][j][k - 1]) {
						if (f[i - 1][j][k - 1] + b[i] > f[i][j][k]) {
							f[i][j][k] = f[i - 1][j][k - 1] + b[i];
							pre[i][j][k] = pii(j, k - 1);
						}
					}
				}
			}
		}
			
	}
	return 0;
}
