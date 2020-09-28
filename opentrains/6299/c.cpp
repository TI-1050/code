#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 5e3 + 10;
int n, a[N], A, B; ll res;
ll gao(int l, int r) {
	ll res = 0;
	for (int i = l, j = A; i <= r; ++i, ++j) {
		res += abs(a[i] - j);
	}
	return res;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%d%d", &A, &B);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + 1 + n);
		res = 1e18;
		for (int i = 1; i <= n; ++i) {
			int l = i, r = i + B - A;
			if (r > n) break;
			res = min(res, gao(l, r));
		}
		printf("%lld\n", res);
	}
	return 0;
}
