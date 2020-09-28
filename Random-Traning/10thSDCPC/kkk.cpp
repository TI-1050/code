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
	for (int n = 2; n <= 10; n += 2) {
		int pre = 0;
		for (int p = 1; p <= 10; ++p) {
			int sum = 0;
			ll limit = 1ll << p;
			for (int i = 1; i <= limit; ++i) {
				if (qpow(n, i, limit) == qpow(i, n, limit)) {
					if(qpow(n, i, limit) != 0) {
						cout << n << " " << p << " " << i << " " << qpow(n, i, limit) << endl;
						cout << "bug" << endl;
					}
				}
			}
		}
	}
	return 0;
}

