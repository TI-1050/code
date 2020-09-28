#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, a[N];

bool ok(int x, int y, int z, int v) {
	for (int i = 0; i <= x; ++i) {
		for (int j = 0; j <= y; ++j) {
			for (int k = 0; k <= z; ++k) {
				if (10 * i + 20 * j + 50 * k == v) {
					return true;
				}
			}
		}
	}
	return false;
}

void gao() {
	for (int i = 1; i <= n; ++i) {
		if (a[i] % 10) {
			puts("-1");
			return ;
		}
	}
	int res = 1e9;
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 5; ++j) {
			for (int k = 0; k <= 2; ++k) {
				int tmp = 0;
				bool F = true;
				for (int o = 1; o <= n; ++o) {
					if (a[o] < 100) {
						if (ok(i, j, k, a[o])) {
							tmp = max(tmp, a[o] / 100);
						} else {
							F = false;
							break;
						}
					} else {
						if (ok(i, j, k, a[o] % 100 + 100)) {
							tmp = max(tmp, a[o] / 100 - 1);
						} else {
							if (ok(i, j, k, a[o] % 100)) {
								tmp = max(tmp, a[o] / 100);
							} else {
								F = false;
								break;
							}
						}
					}
				}
				if (F) {
					res = min(res, i + j + k + tmp);
				}
			}
		}
	}
	printf("%d\n", res);
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		gao();
	}
	return 0;
}
