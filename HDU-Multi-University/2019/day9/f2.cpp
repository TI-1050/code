#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, a[N];

bool ok(int x, int y, int z, int w, int v) {
	for (int i = 0; i <= x; ++i)
		for (int j = 0; j <= y; ++j)
			for (int k = 0; k <= z; ++k) 
				for (int l = 0; l <= w; ++l)
					if (i * 10 + j * 20 + k * 50 + l * 100 == v)
						return 1;
	return 0;
}

bool check(int x, int y, int z, int w) {
	for (int i = 1; i <= n; ++i) {
		if (ok(x, y, z, w, a[i]) == 0) return 0;
	}
	return 1;
}

void gao() {
	int num = 0;
	for (int i = 1; i <= n; ++i) {
		num = max(num, a[i] / 100 - 1); 
		if (a[i] / 100) a[i] = a[i] % 100 + 100;
		if(a[i] % 10) {
			puts("-1");
			return;
		}
	}
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	int now = 1e9;
	for (int i = 0; i <= 20; ++i) {
		for (int j = 0; j <= 10; ++j) {
			for (int k = 0; k <= 4; ++k) {
				for (int l = 0; l <= 2; ++l) {
					if (check(i, j, k, l)) {
						now = min(now, i + j + k + l);
					}
				}
			}
		}
	}
	printf("%d\n", num + now);
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
