#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e5 + 10;
int n; ll a[N], sum;
struct LB {
	ll d[65];
	void init() { memset(d, 0, sizeof d); }
	void insert(ll x) {
		for (int i = 60; i >= 0; --i) {
			if ((x >> i) & 1) {
				if (!d[i]) {
					d[i] = x;
					return;
				}
				x ^= d[i];
			}
		} 
	}
	bool query(ll x, int n) {
		for (int i = 60; i >= n; --i) {
			if ((x >> i) & 1) {
				if (!d[i]) return false;
				x ^= d[i];
			}
		}
		return true; 
	}
}lb;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		sum = 0;
		lb.init();
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			sum ^= a[i];
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 60; j >= 0; --j) {
				if (((sum >> j) & 1) == 0 && ((a[i] >> j) & 1) == 1) {
					a[i] ^= 1ll << j;
				}
			}
			lb.insert(a[i]);
		}
		bool F = 0;
		ll res = 0;
		for (int i= 60; i >= 0; --i) {
			if ((sum >> i) & 1) {
				if (!F) {
					res ^= 1ll << i;
					F = 1;
				} else {
					if (!lb.query(res, i))
						res ^= 1ll << i;
				}
			}
		}
		printf("%lld\n", abs(res - (sum ^ res)));
	}
	return 0;
}
