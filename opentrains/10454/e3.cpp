#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 50;
int n, m, a[N][N];
//第i行第j个数字
int f[22][1 << 21];
//大于1 小于0
unsigned g[N][N]; 
int ord[N], vec[N];

inline bool ok(int i) {
	bool F1 = 1, F2 = 1;
	for (int j = 2; j <= ord[0]; ++j) {
		if (a[i][ord[j]] > a[i][ord[j - 1]]) {
			F1 = 0;
		} else {
			F2 = 0;
		}
	}
	return F1 or F2;
}

inline void get(unsigned mask) {
	ord[0] = 0;
	for (int j = 0; j < m; ++j) {
		if ((mask >> j) & 1) {
			ord[++ord[0]] = j + 1;
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", a[i] + j);
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				unsigned S = 0;
				for (int k = m; k >= 1; --k) {
					S = S * 2 + (a[j][k] > a[i][k]);
				}
				g[i][j] = S;
			}
		}
		ll res = 0;
		unsigned limit = 1 << m;
		for (unsigned mask = 1; mask < limit; ++mask) {
			get(mask);
			vec[0] = 0;
			for (int i = 1; i <= n; ++i) {
				if (ok(i)) {
					vec[++vec[0]] = i;
				}
			}
			int sze = vec[0], now, pre;  
			for (int i = 1; i <= sze; ++i) {
				now = vec[i]; 
				++res; 
				for (int j = 1; j < i; ++j) {
					pre = vec[j]; 
					unsigned S = 0;
					for (int k = 1; k <= m; ++k) {
						if ((mask >> (k - 1)) & 1) {
							S = S * 2 + (a[now][k] > a[pre][k]);
						} else {
							S = S * 2;
						}
					}
					if (S != (g[pre][now] & mask)) {
						cout << mask << " " << pre << " " << now << " " << S << " " << g[pre][now] << endl;
						return 0;
					}
					//	assert(S == (g[pre][now] & mask));
					res += f[pre][S] + 1;
					f[now][S] += f[pre][S] + 1;
				}		
			}
			for (int i = 1; i <= sze; ++i) {
				now = vec[i]; 
				for (int j = 1; j < i; ++j) {
					pre = vec[j]; 
					unsigned S = 0;
					for (int k = 1; k <= m; ++k) {
						if ((mask >> (k - 1)) & 1) {
							S = S * 2 + (a[now][k] > a[pre][k]);
						} else {
							S = S * 2;
						}
					}
					f[now][S] = f[pre][S] = 0;
				}		
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
