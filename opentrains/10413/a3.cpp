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
		res = tot = 0;
		int bl = 1, br = 0; int cl = 1, cr = 0;
		for (int i = 1; i <= na; ++i) {
			while (br < nb && abs(a[i] - b[br + 1]) <= d) ++br, up(c, nc, cl, cr, 1, b[br]);
			while (bl <= br && abs(a[i] - b[bl]) > d) up(c, nc, cl, cr, -1, b[bl]), ++bl;
			while (cr < nc && abs(a[i] - c[cr + 1]) <= d) ++cr, up(b, nb, bl, br, 1, c[cr]);
			while (cl <= cr && abs(a[i] - c[cl]) > d) up(b, nb, bl, br, -1, c[cl]), ++cl;
			res += tot;
		}
		printf("%lld\n", res);
	}
	return 0;
}
