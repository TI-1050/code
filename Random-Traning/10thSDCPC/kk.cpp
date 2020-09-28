#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll qpow(ll x, ll n, ll p) {
	ll res = 1;
	while(n) {
		if (n & 1) res = res * x % p;
		x = x * x % p;
		n >>= 1;
	} 
	return res;
}

int main() {
	for (int n = 1; n <= 30; ++n) {
		ll sum = 0;
		ll limit = 1;
		if (n & 1) {
			for (int p = 1; p <= 30; ++p) {
				cout << "1,";
				fflush(stdout);
			}
			continue;
		}
		int i = 1;
		for (int p = 1; p <= 30; ++p) {
			limit <<= 1;
			for (; i <= limit; ++i) {
				if (qpow(n, i, limit) == qpow(i, n, limit)) {
					sum++;
				}
			}
			cout << sum << ",";
			fflush(stdout);
		}
	}
	return 0;
}
