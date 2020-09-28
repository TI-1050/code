#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;
const int N = 1e5 + 10;
ll bit[N]; int n; 
ll qmod(ll base, ll n) {
	base %= mod;
	ll res = 1;
	while (n) {
		if (n & 1)  res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		ll res = 1ll * (n - 1) + 1ll * (n - 1) * (n - 2) % mod * qmod(6, mod - 2) % mod;
		res %= mod;
		printf("%lld\n", res);
	}
	return 0;
}
