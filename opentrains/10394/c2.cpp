#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, res, a[N], b[N], c[N];
int fac[110];
inline bool ok() {
	for (int i = 1; i <= n - 1; ++i) {
		if (b[c[i]] > a[i])
			return false;
	}
	return true;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < 15; ++i) fac[i] = fac[i - 1] * i;
	while (scanf("%d", &n) != EOF) {
		//a[] 鸡蛋　b[] 小鸡
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) c[i] = i;
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + n);
		int x = 0;
		for (int i = n; i >= 1; --i) {
			if (b[n] > a[i]) break;
			++x;
		}
		if (!x) {
			puts("0");
			continue;
		}
		int res = 0;
		do {
			if (ok()) ++res;
		} while (next_permutation(c + 1, c + 1 + n - 1));
		printf("%d\n", res * x);
	}
	return 0;
}
