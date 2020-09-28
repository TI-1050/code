#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll k, p;

ll phi(ll n) {
	ll ans = n;
	for (ll i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			ans -= ans / i;
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	if (n > 1) ans -= ans / n;
	return ans;
}

ll qmod(ll base, ll n, ll p) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res;
}

ll f(ll k, ll p, ll cnt) {  
	//cout << p << endl;
	if (p == 1) {
		return 0;
	}
	ll phip = phi(p);
	ll t = f(k, phip, cnt + 1);
	return qmod(qmod(k, cnt, p), t + phip, p);  
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &k, &p);
		printf("%lld\n", f(k, p, 1));
	}
	return 0;
}
