#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N];


int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);
		}
		sort(a + 1, a + 1 + n, [&](pii x, pii y) {
			if (x.fi != y.fi) {
				return x.fi < y.fi;
			} else {
				return x.se < y.se;
			}
		});
		multiset <int> s; s.insert(-1);
		for (int i = 1; i <= n; ++i) {
			auto pos = s.upper_bound(a[i].fi);  
			if (pos != s.begin()) {
				--pos;
				s.erase(pos);
			}
			s.insert(a[i].se);
		}
		printf("%d\n", (int)s.size());
	}
	return 0;
}
