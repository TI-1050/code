#include <bits/stdc++.h>
using namespace std;

#define N 6010
#define ll long long
const ll p = 998244353;
int n, m;
ll fac[N], inv[N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
ll C(int n, int m) {
	if (m > n) return 0;
	return fac[n] * inv[m] % p * inv[n - m] % p;
}
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % p;
	inv[N - 1] = qmod(fac[N - 1], p - 2);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		if (m > n) puts("0");
		else {
			ll res = 0;
			for (int i = 1; i <= n; ++i) {
				for (int j = 0; j <= n - 1ll * i * m; ++j) {
					add(res, (C(j + 2 * i - 1, 2 * i - 1) - C(j + i - 1, 2 * i - 1) + p) % p);
				}
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}
