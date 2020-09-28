#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll p = (ll)1e9 + 7;

ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % p;
		base = base * base % p;
		n >>= 1;
	}
	return res;
}
int n, m;

int main() {
	ll res = 1;
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		if (n == 1) {
			res *= 1;
		} else if (m == 0) {
			res = 0;
		} else {
			res = res * qmod(n - 1, p - 2) % p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
