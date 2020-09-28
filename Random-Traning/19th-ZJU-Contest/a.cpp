#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n, m;
pii a[N], b[N];
int f(pii *a, pii *b, int n, int m) {
	int res = 0;
	int pos = 1;
	while (pos <= m && b[pos].se == 0) {
		++pos; 
	}
	if (pos > m) {
		return 0;
	}
	for (int i = 1; i <= n; ++i) if (a[i].se == 0) {
		if (b[pos].fi < a[i].fi) {
			++res;
			++pos;
			while (pos <= m && b[pos].se == 0) {
				++pos;
			}
			if (pos > m) { 
				break;
			}
		}
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].fi);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &b[i].fi);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].se);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &b[i].se); 
		}
		sort(a + 1, a + 1 + n, [](pii x, pii y) {
			return x.fi < y.fi;		
		});
		sort(b + 1, b + 1 + m, [](pii x, pii y){
			return x.fi < y.fi;		
		});
		int res = 0;
		res += f(a, b, n, m);
		res += f(b, a, m, n);
		printf("%d\n", res);
	}
	return 0;
}
