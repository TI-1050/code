#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll p, x;
ll mul(ll u, ll v, ll p) {
	return (u * v - (ll)((long double)u * v / p) * p + p) % p;
}

ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = mul(res, base, p);
		}
		base = mul(base, base, p);
		n >>= 1;
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &p, &x);
		x = qmod(x, p - 2);
		for (int i = 1; i <= 100; ++i) {
			printf("%lld %lld\n", i, 1ll * i * x % p);
		}
	}
	return 0;
}
