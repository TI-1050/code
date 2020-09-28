#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
int d, na, nb, nc, a[N], b[N], c[N]; 
ll res, tot;

inline int cross(int l, int r, int L, int R) {
	l = max(l, L); r = min(r, R);
	return max(0, r - l + 1);
}

void up(int *a, int n, int l, int r, int f, int x) {
	int L = lower_bound(a + 1, a + 1 + n, x - d) - a;
	int R = upper_bound(a + 1, a + 1 + n, x + d) - a - 1;
	tot += cross(l, r, L, R) * f;
}

int main() {
	while (scanf("%d%d%d%d", &d, &na, &nb, &nc) != EOF) {
		for (int i = 1; i <= na; ++i) scanf("%d", a + i);
		for (int i = 1; i <= nb; ++i) scanf("%d", b + i);
	    for (int i = 1; i <= nc; ++i) scanf("%d", c + i);
		res = 0;
		for (int i = 1; i <= na; ++i) {
			for (int j = 1; j <= nb; ++j) {
				for (int k = 1; k <= nc; ++k) {
					if (abs(a[i] - b[j]) <= d && abs(a[i] - c[k]) <= d && abs(b[j] - c[k]) <= d)
						++res;
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
