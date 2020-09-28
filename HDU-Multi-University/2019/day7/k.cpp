#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e5 + 10;

const ll p = 1e9 + 7;

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * x % p;
		x = x * x % p;
		n >>= 1;
	} 
	return res;
}

int n, q;
ll r, s, x, a;
ll f[N];

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld %lld %lld %lld", &r, &s, &x, &a);
			f[i + 1] = ((a + f[i] - f[x] + p) % p * s % p * qpow(r, p - 2) % p + f[x] + p) % p;
		}
		for (int _q = 1, l, r; _q <= q; ++_q) {
			scanf("%d %d", &l, &r);
			printf("%lld\n", (f[r] - f[l] + p) % p);
		}
	}
	return 0;
}
