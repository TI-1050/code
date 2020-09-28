#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N];
ll tot;
bool check(ll x) {
	ll remind = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] > x) {
			remind += a[i] - x;
		}
	}
	ll tmp = remind;
	for (int i = 1; i <= n; ++i) {
		if (a[i] < x) {
			remind -= x - a[i];
		}
	}
	if (remind >= 0) {
		tot = min(tot, tmp);
		return true;
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		tot = 1e18;
		ll l = 0, r = 1e9;
		while (r - l >= 0) {
			ll mid = (l + r) >> 1;
			if (check(mid)) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		printf("%lld\n", tot);  
	}
	return 0;
}
