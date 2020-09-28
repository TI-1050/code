#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);			
		}
		sort(a + 1, a + 1 + n, [&](pii x, pii y) {
			if (x.se != y.se) {
				return x.se < y.se;
			}		
			return x.fi < y.fi;
		});
		int pre = -1;
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (pre >= a[i].se) {
				continue;
			}
			++res;
			pre = max(pre + 1, a[i].fi);
		}
		printf("%d\n", res);
	}
	return 0;
}
