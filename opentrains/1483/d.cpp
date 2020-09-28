#include <bits/stdc++.h>
using namespace std;

#define db double
const db eps = 1e-8;
const int N = 1e6 + 10;
int n, h, a[N];

bool check(db x) {
	int pre = h;
	for (int i = 1; i <= n; ++i) {
		int gap = pre - a[i]; pre = a[i];
		if (x < gap) return 0;
		x = x - max(2.0 * gap - x, 0.0);
	}
	return x >= pre || fabs(x - pre) < eps;
}

int main() {
	while (scanf("%d%d", &n, &h) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		a[0] = h;
		db l = 0, r = h, res = h;
		while (r - l >= eps) {
			db mid = (l + r) / 2;
			if (check(mid)) {
				res = mid;
				r = mid;
			} else {
				l = mid;
			}
		}
		printf("%.10f\n", res);
	}
	return 0;
}
