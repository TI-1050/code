#include <bits/stdc++.h>
using namespace std;

#define ll long long


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 1; n % 2 == 0 && i <= k; ++i) {
			n /= 2;
		}
		for (int i = 1; n % 5 == 0 && i <= k; ++i) {
			n /= 5;
		}
		ll res = n;
		for (int i = 1; i <= k; ++i) {
			res *= 10;
		}
		printf("%lld\n", res);
	}
	return 0;
}
