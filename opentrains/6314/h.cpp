#include <bits/stdc++.h>
using namespace std;

using pII = pair <int, int>;
#define fi first
#define se second
const int N = 5e5 + 10;
int n, c, b, cnt, a[N], z[N];
pII q[N];

int main() {
	while (scanf("%d%d%d", &n, &c, &b) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1; i <= b; ++i) scanf("%d", z + i);
		cnt = 0;
		for (int i = 1, l = 1; i <= b; ++i) {
			int r = z[i] - 1;
			if (r - l >= 0) {
				q[++cnt] = pII(l, r);
			} 
			l = z[i] + 1;
		}
	//	for (int i = 1; i <= cnt; ++i) printf("%d %d\n", q[i].fi, q[i].se);
		if (c & 1) {
			a[1] = 1;
			q[1].fi += 2; 
			--c;
		} else ++q[1].fi; 
		for (int i = 1; i <= cnt; ++i) {
			int l = q[i].fi, r = q[i].se;
		//	cout << l << " " << r << endl;
			while (l <= r && c) {
				a[l] = 1;
				l += 2;
				c -= 2;
			}
		}
		for (int i = 1; i <= n; ++i) printf("%d", a[i]);
		puts("");
	}
	return 0;
}
