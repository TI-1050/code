#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010

int main() {
	int T; cin >> T;
	while (T--) {
		int n; ll x;
		scanf("%d", &n); 
		ll res = 0; 
		scanf("%lld", &x);
		ll f[] = {
			x * x + 1,
			x * x - 1,
			-x * x + 1,
			-x * x - 1,
		};
		for (ll i = 2; i <= n; ++i) {
			scanf("%lld", &x);
			res = max(res, -x * x - i * i + f[0]);
			res = max(res, -x * x + i * i + f[1]);
			res = max(res, x * x - i * i + f[2]);
			res = max(res, x * x + i * i + f[3]);
			f[0] = max(f[0], x * x + i * i);
			f[1] = max(f[1], x * x - i * i);
			f[2] = max(f[2], -x * x + i * i);
			f[3] = max(f[3], -x * x - i * i);
		}
		printf("%lld\n", res);
	}
	return 0;
}
