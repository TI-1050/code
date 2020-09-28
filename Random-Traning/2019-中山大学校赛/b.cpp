#include <bits/stdc++.h>
using namespace std;

#define N 50000010
int n, a[N];

bool ok() {
	sort(a + 1, a + 1 + n);
	for (int i = 3; i <= n; ++i) {
		if (a[i - 2] + a[i - 1] > a[i]) {
			return true;
		}
	}
	return false;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		if (n > 100) {
			puts("YES");
		} else {
			puts(ok() ? "YES" : "NO");
		}
	}
	return 0;
}
