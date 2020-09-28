#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
int n, k, m;
const ll p = 998244353;
ll f[N][N];
char st[N], ed[N]; 
ll inv[N], fac[N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
ll C(int n, int m) {
	if (n == 0 && m == 0) {
		return 1;
	}
	if (n < m) {
		return 0;
	}
	return 1ll * fac[n] * inv[m] % p * inv[n - m] % p; 
}

void init() {
	for (int i = 0; i <= k; ++i) {
		for (int j = 0; j <= n; ++j) {
			f[i][j] = 0;
		}
	}
}
int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) {
		fac[i] = fac[i - 1] * i % p;
	}
	inv[100] = qmod(fac[100], p - 2); 
	for (int i = 100; i >= 1; --i) {
		inv[i - 1] = inv[i] * i % p;  
	}
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &k, &m);
		init();
		scanf("%s%s", st + 1, ed + 1);
		int ini = 0;
		for (int i = 1; i <= n; ++i) {
			ini += (st[i] == ed[i]);
		}
		//f[i][j] 表示第i轮  有j个在正确位置上
		f[0][ini] = 1;
		for (int i = 1; i <= k; ++i) {
			for (int j = 0; j <= n; ++j) {
				//当j >= o 的时候
				for (int o = 0; o <= j; ++o) {
					int gap = j - o;
					if (m >= gap && (m - gap) % 2 == 0) {
						//表示把x个正确的翻转成不正确的
						int x = (m - gap) / 2;
						//表示把y个不正确的翻转成正确的  
						int y = x + gap;
						(f[i][j] += C(o, x) * C(n - o, y) % p * f[i - 1][o] % p) %= p;
					}
				}
				//当j < o 的时候
				for (int o = j + 1; o <= n; ++o) {
					int gap = o - j;
					if (m >= gap && (m - gap) % 2 == 0) {
						//表示把x个不正确的翻转成正确的
						int x = (m - gap) / 2;
						//表示把y个正确的翻转成不正确的
						int y = x + gap;
						(f[i][j] += C(o, y) * C(n - o, x) % p * f[i - 1][o] % p) %= p;
					}
				}
			}
		}
	//	puts("#####################################");
	//	for (int i = 1; i <= k; ++i) {
	//		for (int j = 0; j <= n; ++j) {
	//			printf("%d %d %lld\n", i, j, f[i][j]);
	//		}
	//	}
		printf("%lld\n", f[k][n]);
	}
	return 0;
}
