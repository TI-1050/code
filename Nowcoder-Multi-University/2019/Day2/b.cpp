#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
const ll p = 1e9 + 7;
ll n, m, k, inv2, invk;
ll f[N], g[N], fac[N], inv[N];
ll qmod(ll base, ll n) {
	base %= p;
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

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}



int main() {
	m = 1000000;
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % p; 
	inv[m] = qmod(fac[m], p - 2);
	for (int i = m; i >= 1; --i) inv[i - 1] = inv[i] * i % p;
	inv2 = 5e8 + 4;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &k, &n);
		invk = qmod(k, p - 2);
		if (n == -1) { 
			printf("%lld\n", inv2);
			continue;
		}
		for (int i = 1; i <= m; ++i) f[i] = 0;
		f[0] = 1; g[0] = 1;
		for (int i = 1; i <= m; ++i) {
			if (i > k) {
				add(f[i], invk * (g[i - 1] - g[i - k - 1] + p) % p);
			} else {
				add(f[i], invk * g[i - 1] % p);
			}
			g[i] = (g[i - 1] + f[i]) % p;
		}
		if (n <= m) {
			printf("%lld\n", f[n]);
		} else {
			ll tmp = 1;
			for (int i = 0; i <= m; ++i) tmp = tmp * (n - i) % p; 
			ll res = 0;
			ll one = (m & 1) ? -1 : 1;
			for (int i = 0; i <= m; ++i) {
				add(res, (one * f[i] % p * tmp % p * inv[m - i] % p * inv[i] % p * qmod(n - i, p - 2) % p + p) % p);
				one *= -1;
			}			
			printf("%lld\n", res);
		}
	}
	return 0;
}
