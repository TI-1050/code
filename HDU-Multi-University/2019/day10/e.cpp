#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pLL pair <ll, ll>
#define fi first
#define se second
const int N = 1e5 + 10;
int n;
pLL a[N];
ll f[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%lld%lld", &a[i].fi, &a[i].se);
		sort(a + 1, a + 1 + n, [&](pLL x, pLL y){
			if (x.fi != y.fi) return x.fi < y.fi;
			return x.se > y.se; 		
		});
		f[n + 1] = 0;
		for (int i = n; i >= 1; --i) {
			f[i] = max(f[i + 1], a[i].se);
		}
		set <ll> se; 
		ll res = 5e18;
		for (int i = 1; i <= n; ++i) {
			if (i != n) res = min(res, abs(a[i].fi - f[i + 1])); 
			if (i == n || f[i + 1] <= a[i].fi) {
				auto pos = se.lower_bound(a[i].fi);
				if (pos != se.end()) {
					res = min(res, abs(a[i].fi - *pos));
				}
				if (pos != se.begin()) {
					--pos;
					if (*pos >= f[i + 1]) {
						res = min(res, abs(a[i].fi - *pos));
					}
				}
			}
			se.insert(a[i].se);
		}
	    printf("%lld\n", res);	
	}
	return 0;
}
