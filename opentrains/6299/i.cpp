#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x, cnt;
	while (scanf("%d", &n) != EOF) {
		cnt = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x);
			cnt += (x < 0);
		}
		printf("%lld\n", 1ll * (n - 1) * cnt);
	}
	return 0;
}
