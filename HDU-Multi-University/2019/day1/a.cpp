#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
#define pii pair <int, int>
#define fi first
#define se second
const ll p = 998244353; 
int n, m;
vector <vector<pii>> vec;
ll f[2][N][N][N];

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;   
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		vec.clear(); vec.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			vec[i].push_back(pii(i, 1));
		}
		for (int i = 1, l, r, x; i <= m; ++i) {
			scanf("%d%d%d", &l, &r, &x);
			vec[r].push_back(pii(l, x));
		}
		for (int i = 0; i <= n; ++i) 
			for (int j = 0; j <= n; ++j) 
				for (int k = 0; k <= n; ++k)
					for (int t = 0; t < 2; ++t) 
						f[t][i][j][k] = 0;
		f[0][0][0][0] = 1;
		for (int i = 1, p = 1; i <= n; ++i, p ^= 1) {
			for (int j = 0; j <= i; ++j) {
				for (int k = 0; k <= i; ++k) {
					for (int t = 0; t <= i; ++t) {
						f[p][j][k][t] = 0;
					}
				}
			}
			for (int j = 0; j <= i; ++j) {
				for (int k = j; k <= i; ++k) {
					for (int t = k; t <= i; ++t) {
						add(f[p][j][k][t], f[p ^ 1][j][k][t]);
						add(f[p][j][k][i - 1], f[p ^ 1][j][k][t]);
						add(f[p][j][t][i - 1], f[p ^ 1][j][k][t]);
						add(f[p][k][t][i - 1], f[p ^ 1][j][k][t]);
					}
				}
			}
			for (int j = 0; j <= i; ++j) {
				for (int k = j; k <= i; ++k) {
					for (int t = k; t <= i; ++t) {
						for (auto it : vec[i]) {
							int l = it.fi, x = it.se;
							if ((j >= l) + (k >= l) + (t >= l) + 1 != x) {
								f[p][j][k][t] = 0;
							}
						}
					}
				}
			}
		}
		ll res = 0;
		for (int i = 0; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				for (int k = j; k <= n; ++k) {
					add(res, f[n & 1][i][j][k]);
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
