#include <bits/stdc++.h>
using namespace std;

#define ll long long
int a, p;
ll mod;
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % mod;
		}
		base = base * base % mod;
		n >>= 1;
	}
	return res;  
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &a, &p);
		if (a & 1) {
			puts("1");
			continue;
		}
		mod = 1ll << p; 
		if (mod > 30) {
			ll res = 0;
			for (int i = 1; i <= p; ++i) {
				if (qmod(a, i) == qmod(i, a)) {
					++res;
				}
			}
			ll remind = mod - p;
			if (a >= p) {
				printf("%lld\n", res + (remind + 1) / 2);
			} else {
				int t = (p / a) + (p % a != 0);
				t = 1ll << t;
				res += mod / t - p / t;
				printf("%lld\n", res);
			}
		} else {
			ll res = 0;
			for (int i = 1; i <= mod; ++i) {
				if (qmod(a, i) == qmod(i, a)) {
					++res;
				}
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}
