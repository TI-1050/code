#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2050
const ll p = 1e9 + 7;
int n, m;
ll f[N][N];

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		f[0][0] = 1;
		for (int i = 0; i <= n + m; ++i) { 
			for (int j = 0; j <= n + m; ++j) {
				if ((i + 1 - j) <= n && (j - (i + 1)) <= m) {
					add(f[i + 1][j], f[i][j]); 
				}
				if ((i - (j + 1)) <= n && (j + 1 - i) <= m) { 
					add(f[i][j + 1], f[i][j]);  
				}
			}
		}
		printf("%lld\n", f[n + m][n + m]);
		for (int i = 0; i <= n + m + 10; ++i) {
			for (int j = 0; j <= n + m + 10; ++j) {
				f[i][j] = 0;
			}
		}
	}
	return 0;
}
