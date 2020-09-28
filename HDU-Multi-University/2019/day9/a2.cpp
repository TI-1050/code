#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;
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
	int S = 500000;
	ll tot = 0;
	printf("{");
	bool F = 0;
	for (int i = 1; i <= 1000000000; ++i) {
		tot += qmod(i, mod - 2);
		tot %= mod;
		if (i % S == 0) {
			if (F) printf(",");
			F = 1;
			printf("%lld", tot);
		}
	}
	puts("};");
	return 0;
}
