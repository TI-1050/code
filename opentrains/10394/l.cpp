#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n; ll a[110];

int main() {
	while (scanf("%d", &n) != EOF) {
		ll S = 0, res = 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			S ^= a[i];
			res = res << 1;
		}
		if (S == 0) res -= 2;
		else res = 0;
		printf("%lld\n", res);
	}
	return 0;
}
