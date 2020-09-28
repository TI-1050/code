#include <bits/stdc++.h>
using namespace std;

const int N = 1e2 + 10;
int n, L, R, m[N], c[N], d[N];
bitset <10010> B, T;

bool check(int x) {
	for (int i = 1; i <= n; ++i) {
		d[i] = min(R, c[i] / x); 
	}
	B.reset();
	B[0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= d[i]; ++j) {
			B |= (B << m[i]); 
		}
	}
	if ((B & T).count()) return true;
	return false;
}

int main() {
	while (scanf("%d%d%d", &n, &L, &R) != EOF) {
		T.reset();
		for (int i = L; i <= R; ++i) T[i] = 1;
		for (int i = 1; i <= n; ++i) scanf("%d%d", m + i, c + i);
		int l = 1, r = 1e6, res = 0;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
