#include <bits/stdc++.h>
using namespace std;

#define N 5100
int n, m, a[N], b[N];

bool ok(int x) {
	for (int i = 1; i <= m; ++i) {
		if (a[b[i] + x]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			a[x] = 1;
		}
		for (int i = 1; i <= m; ++i) scanf("%d", b + i);
		for (int i = 0; i <= 2000; ++i) {
			if (ok(i)) {
				printf("%d\n", i);
				break;
			}
		}
	}
	return 0;
}
