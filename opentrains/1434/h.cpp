#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, k, a[N];

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		set <int> se;
		for (int i = 1; i <= k; ++i) se.insert(a[i]);
		bool F = 0;
		for (int i = 1; i + k - 1 <= n; ++i) {
			if (*se.begin() < a[i]) {
				sort(a + i, a + i + k);
				F = 1;
				break;
			}
			se.erase(a[i]);
			if (i + k <= n) se.insert(a[i + k]);
		}
		if (!F) sort(&a[n - k + 1], &a[n + 1]);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
