#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
const ll p = 1e9 + 7;
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
int n;
ll f[N], g[N], inv[N]; 

ll Sf(int l, int r) {
	if (l > r) return 0;
	return (f[r] - f[l - 1] + p) % p;
}

ll Sg(int l, int r) {
	if (l > r) return 0;
	return (g[r] - g[l - 1] + p) % p; 
}

void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

int main() {
	inv[1] = 1;
	for (int i = 2; i < N; ++i) inv[i] = inv[p % i] * (p - p / i) % p;
	for (int i = 1; i < N; ++i) {
		f[i] = (f[i - 1] + i) % p;
		g[i] = (g[i - 1] + inv[i]) % p;
	}
	while (scanf("%d", &n) != EOF) {
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			add(res, 1ll * i * inv[n] % p * inv[n] % p * Sg(i + 1, n) % p);
			add(res, 1ll * inv[i] * inv[n] % p * inv[n] % p * (1ll * i * (i + 1) % p - Sf(1, i) + p) % p);
		}
		printf("%lld\n", res);
	}
	return 0;
}
