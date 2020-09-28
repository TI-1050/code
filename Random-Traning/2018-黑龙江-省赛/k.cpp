#include <bits/stdc++.h>
using namespace std;

#define ll long long

int f(ll x) {
	int res = 0;
	while (x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

int main() {
	int T; cin >> T;
	while (T--) {
		ll n; scanf("%lld", &n);
		if (n < 10) {
			printf("%lld\n", n);
		} else {
			int res = f(n);
			ll t = n;
			ll q = 1;
			while (t) {
				if (t < 10) {
					q *= t;
					break;
				} else {
					q *= 10;
					t /= 10;
				}
			}
			res = max(res, f(q - 1) + f(n - q + 1));
			printf("%d\n", res);
		}
	}
	return 0;
}
