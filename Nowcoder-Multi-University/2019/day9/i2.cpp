#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const ll inv2 = 5e8 + 4;

ll gao(ll a, ll b, ll c, ll n) {
	if (a == 0) {
		return (n + 1) * (b / c) % mod; 
	}
	if (a >= c || b >= c) {
		ll tmp = gao(a % c, b % c, c, n);
		ll res = (tmp + (a / c) % mod * (n % mod) % mod * ((n + 1) % mod) % mod * inv2 % mod + (b / c) % mod * ((n + 1) % mod) % mod) % mod;
		res = (res + mod) % mod;
		return res;
	}
	ll m = ((__int128)a * n + b) / c;
	ll tmp = gao(c, c - b - 1, a, m - 1);
	ll res = ((__int128)n * (m % mod) % mod - tmp + mod) % mod;
	res = (res + mod) % mod;
	return res;
}

int main() {
	ll n, m; cin >> n >> m;
	ll res = 0;
	for (int i = 45; i >= 0; --i) if ((m >> i) & 1) {
		ll tmp = (gao(m, 0, 1ll << i, n) - 2ll * gao(m, 0, 1ll << (i + 1), n) % mod + mod) % mod;
		res = res + (1ll << i) % mod * tmp % mod;
		res %= mod;
	}
	cout << res << "\n";
	return 0;
}
