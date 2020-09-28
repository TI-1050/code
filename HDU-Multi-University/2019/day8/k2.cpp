#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e6 + 10;
int n, a[N], b[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d%d", a + i, b + i);
		ll Sa = accumulate(a + 1, a + 1 + n, 0ll);
		ll Sb = accumulate(b + 1, b + 1 + n, 0ll);
		ll res = min(Sa, Sb);
		for (int i = 1; i <= n; ++i) {
			res = min(res, Sa + Sb - a[i] - b[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
