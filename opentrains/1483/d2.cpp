#include <bits/stdc++.h>

using namespace std;

typedef double db;

const db eps = 1e-8;

#define N 1000010

int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1: -1;
}

int n;
int a[N];

int main() {
	while (scanf("%d %d", &n, a) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		db base = a[n];
		for (int i = n; i >= 1; --i) {
			db h = a[i - 1] - a[i];
			if (sgn(base - 2 * h) >= 0) {
				continue;
			} else {
				base += h - 0.5 * base;
			}
		}
		printf("%.10f\n", base);
	}
	return 0;
}
