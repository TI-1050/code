#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db long double
const int N = 510;
db fac[N], f[N][N], g[N][N];
int n, a, b, x[N];

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i;
	while (scanf("%d%d%d", &n, &a, &b) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", x + i);
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		f[0][0] = 1;
		//f[i][j] 表示用了j张卡片，选取的卡片的和为i的方案数
		for (int i = 1; i <= n; ++i) {
			for (int j = a; j >= x[i]; --j) {
				for (int k = n; k >= 1; --k) {
					f[j][k] += f[j - x[i]][k - 1]; 
				}
			}
		}
		db res = 0;
		for (int i = n; i >= 1; --i) {
			for (int j = 0; j <= a; ++j) {
				for (int k = 0; k <= n; ++k) {
					if (j >= x[i] && k >= 1) g[j][k] = f[j][k] - g[j - x[i]][k - 1];
					else g[j][k] = f[j][k];
				}
			}	
			for (int j = 0; j <= a; ++j) {
				for (int k = 0; k <= n; ++k) {
					if (j + x[i] > a && j + x[i] <= b) {
						res += g[j][k] * fac[k] * fac[n - k - 1];
					}
				}
			}
		}
		printf("%.12Lf\n", res / fac[n]);
	}
	return 0;
}
