#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
ll k, n; int m;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%d", &k, &m);
		ll res = INFLL;
		for (int i = 1; i <= 1000; ++i) {
			ll n = k ^ i;
			if (gcd(i, n) != 1) continue;
			int cur = 0;
			for (int j = 1; j <= i; ++j) {
				cur += (gcd(j + n, n) == 1);
				if (cur > m) break;
			}
			if (cur == m) {
				res = min(res, n);
			}
		}
		if (res == INFLL) res = -1;
		printf("%lld\n", res);
	}
	return 0;
}
