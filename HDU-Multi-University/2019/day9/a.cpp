#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
ll n, m;
inline ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}
inline ll inv(ll x) {
	return qmod(x, mod - 2);
}
ll S[] =	
inline ll sum(ll n) {
	
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%lld%lld", &n, &m);
		if (n == m) puts("0");
		else {
			ll res = 4ll * inv(n + 1) % mod + 2ll * inv(m + 1) % mod;
			res %= mod;
			res += 2ll * sum(n) % mod;
			res -= 2ll * sum(m + 1) % mod;
			res = (res % mod + mod) % mod;
			printf("%lld\n", res);
		}
	}
	return 0;
}
