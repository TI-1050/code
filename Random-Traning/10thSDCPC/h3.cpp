#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii cor[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &cor[i].fi, &cor[i].se);
		}
		sort(cor + 1, cor + 1 + n, [](pii x, pii y) {
			if (x.se != y.se) {
				return x.se < y.se;
			};
			return x.fi < y.fi; 
		});	
		int res = 0;
		set <int> se;
		for (int i = 1; i <= n; ++i) {
			if (se.empty()) {
				++res;
				se.insert(cor[i].fi);
			} else {
				for (int j = cor[i].fi; j <= cor[i].se; ++j) {
					auto pos = se.lower_bound(j);
					if (pos == se.end() || (*pos) != j) {
						++res;
						se.insert(j);
						break;
					}
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
