#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, x[N], r[N];

bool ok() {
	int pre = 1, far = x[1] + r[1]; 
	for (int i = 2; i <= n; ++i) {
		if (far < x[i]) return 0;
		if (x[i] - r[i] <= x[pre]) {
			pre = i;
		}
		far = max(far, x[i] + r[i]);
	}
	return pre == n;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", x + i, r + i);
		}
		if (ok()) {
			printf("%lld\n", 3ll * (x[n] - x[1]));
		} else {
			puts("-1");
		}
	}
	return 0;
}
