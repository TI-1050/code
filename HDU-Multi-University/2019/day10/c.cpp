#include <bits/stdc++.h>

using namespace std;

typedef double db;

const db eps = 1e-8;

const int N = 1e4 + 10;

int n;
db p[N];

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lf", p + i);
		}
		sort(p + 1, p + 1 + n);
		db res = 0;
		if (p[n] == 1.0) {
			res = 1.0;
		} else {
			db tmp1 = 1.0, tmp2 = 0.0;
			for (int i = n; i >= 1; --i) {
				tmp1 = tmp1 * (1.0 - p[i]);
				tmp2 = tmp2 + p[i] / (1.0 - p[i]);
				res = max(res, tmp1 * tmp2);
			}
		}
		printf("%.10f\n", res);
	}
	return 0;
}
