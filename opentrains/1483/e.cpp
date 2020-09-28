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
	bit[0] = 1; 
	for (int i = 1; i < N; ++i) bit[i] = bit[i - 1] * 2 % mod;
	while (scanf("%d", &n) != EOF) {
		ll res = 0;
		for (int i = 1; i <= n - 1; ++i) {
			res += 1ll * i * qmod(bit[n - i] - 1 + mod, mod - 2) % mod;
			res %= mod;
		}
		printf("%lld\n", res);
	}
	return 0;
}
