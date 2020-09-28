#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define ll long long 
int k, m, n;
ll p;
ll a[N];
ll qmod(ll base, ll n, ll p) {
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
ll mul(ll u, ll v, ll p) {
	return (u * v - (ll)((long double)u * v / p) * p + p) % p; 
}


ll f(int x) {
	return ((qmod(n, x, (ll)1e15) - 1) / (n - 1)) % p;
}

int main() {
	while (scanf("%d%d%d%lld", &k, &m, &n, &p) != EOF) {
		for (int i = 1; i <= k; ++i) {
			scanf("%lld", a + i);
		}
		sort(a + 1, a + 1 + k);
		ll res = 0;
		for (int i = 1, j = 1, now = 0; i <= m; ++i, j *= n) {
			if (i > 1) for (int o = 1; o <= j; ++o) {
				(res += mul(f(m - i + 1), a[++now], p)) %= p;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
