#include <bits/stdc++.h>
using namespace std;

#define ll long long 
const ll p = 1e9 + 7;

ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

int main() {
	ll n; cin >> n;
	for (int i = 1; i <= 1000; ++i) {
		for (int j = 1; j <= 1000; ++j) {
			if (1ll * i * qmod(j, p - 2) % p == n) {
				cout << i << " " << j << endl;
				return 0;	
			}
		}
	}
	return 0;
}
