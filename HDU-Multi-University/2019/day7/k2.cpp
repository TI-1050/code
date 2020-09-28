#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
const int mod = 1e9 + 7;
int n, q; ll f[N];
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &n, &q);
		++n;
		f[1] = 0;
		for (int i = 2, r, s, x, a; i <= n; ++i) {
			scanf("%d%d%d%d", &r, &s, &x, &a);
			f[i] = f[i - 1] + a + (1ll * s * qmod(r, mod - 2) % mod - 1 + mod) % mod * ((f[i - 1] - f[x] + a + mod) % mod) % mod;
			f[i] %= mod;
		}
		for (int i = 1, l, r; i <= q; ++i) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", (f[r] - f[l] + mod) % mod);
		}
	}
	return 0;
}

