#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 50010
int n;
ll a[N], sum[N], sum2[N];

int main() {
	int T; cin >> T;
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			sum[i] = sum[i - 1] + a[i];
			sum2[i] = sum2[i - 1] + a[i] * a[i];
		}
		ll res = 0;
		for (int i = 1; i < n; ++i) {
			res += a[i] * a[i] * (n - i) + sum2[n] - sum2[i] - a[i] * 2 * (sum[n] - sum[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
