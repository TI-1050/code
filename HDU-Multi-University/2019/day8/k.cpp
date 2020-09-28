#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e6 + 10;
int n;
ll a[N][2]; 

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", a[i], a[i] + 1);
		}
		ll res = 0;
		ll peo = 0, milk = a[1][1];
		ll cnt = 0;
		for (int i = 2; i <= n; ++i) {
			if (milk > a[i][0]) {
				res += a[i][0];
				milk -= a[i][0];
				cnt += a[i][0];
				a[i][0] = 0;
			} else {
				res += milk;
				a[i][0] -= milk;
				cnt += milk;
				milk = 0;
			}
			if (peo > a[i][1]) {
				res += a[i][1];
				peo -= a[i][1];
				a[i][1] = 0;
			} else {
				res += peo;
				a[i][1] -= peo;
				peo = 0;
			}
			milk += a[i][1];
			peo += a[i][0];
		}
		if (cnt < a[1][1]) milk -= a[1][1] - cnt;
		milk = max(0ll, milk);
		res += min(a[1][0], milk);
		printf("%lld\n", res);
	}
	return 0;
}
