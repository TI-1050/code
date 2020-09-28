#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;

ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

ll C(int n, int m) {
	if (n < m || n < 0 || m < 0) return 0;
	if (n == 0 || m == 0) return 1; 
	ll a = 1, b = 1;
	for (int i = n; i > n - m; --i) a = a * i % mod;
	for (int i = 1; i <= m; ++i) b = b * i % mod;
	return a * qpow(b, mod - 2) % mod; 
}

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		if (n < m) swap(n, m);
	//	if (n + m == 0) puts("1");
	//	else if (n == 0 || m == 0) printf("%lld\n", (C(2 * n, n) - C(2 * n, n - 1) + mod) % mod);
		printf("%lld\n", (C(2 * (n + m), n + m) - C(2 * (n + m), n - 1) - C(2 * (n + m), m - 1) + 2 * mod) % mod);
	}
	return 0;
}
