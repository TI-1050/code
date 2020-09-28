#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

int n;
int a[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + 1 + n);
		reverse(a + 1, a + 1 + n);
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			res += max(0, a[i] - (i - 1));
		}
		printf("%lld\n", res);
	}
	return 0;
}
