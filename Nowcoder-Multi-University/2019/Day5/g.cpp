#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3010
const ll p = 998244353;
int n, m;
char s[N], t[N];
ll dp[N][2];
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

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

ll fac[N], inv[N];
ll C(int n, int m) {
	return fac[n] * inv[m] % p * inv[n - m] % p;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % p;
	inv[N - 1] = qmod(fac[N - 1], p - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		scanf("%s%s", s + 1, t + 1);
		for (int i = 0; i <= n; ++i) {
			dp[i][0] = dp[i][1] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = m - 1; j >= 1; --j) {
				ll f;
				if (s[i] == t[j + 1]) {
					f = dp[j][1];
					add(dp[j + 1][1], f);
				} else if (s[i] > t[j + 1]) {
					f = dp[j][1];
					add(dp[j + 1][0], f);
				}
				f = dp[j][0];
				add(dp[j + 1][0], f);
			}
			if (s[i] != '0') {
				if (s[i] == t[1]) {
					add(dp[1][1], 1);
				} else if (s[i] > t[1]) {
					add(dp[1][0], 1);
				}
			}
		}
		ll res = dp[m][0];
		for (int i = 1; i <= n; ++i) {
			if (s[i] != '0') {
				int tot = n - i;
				for (int j = m + 1; j <= n - i + 1; ++j) {
					add(res, C(tot, j - 1));
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
