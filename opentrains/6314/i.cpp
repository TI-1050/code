#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n;
int a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		double res = 10;
		bool F = true;
		for (int i = 1; i <= n; ++i) {
			if (a[i] > i) {
				F = false;
				break;
			}
			res = min(res, 1.0 * a[i] / i);
		}
		if (F) {
			printf("%.10f\n", res);
		} else {
			puts("impossible");
		}
	}
	return 0;
}
