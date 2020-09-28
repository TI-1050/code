#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110 
struct Hash {
	int a[N], cnt;
	void init() { cnt = 0; }
	void add(int x) { a[++cnt] = x; }
	void work() { sort(a + 1, a + 1 + cnt); cnt = unique(a + 1, a + 1 + cnt) - a - 1; }
	int get(int x) { return lower_bound(a + 1, a + 1 + cnt, x) - a; }
}hx, hy;
struct E {
	int x, y, k, t;
	void scan() {
		scanf("%d%d%d%d", &x, &y, &k, &t);
		hx.add(x); hy.add(y);
	}
}e[N]; 
int n, m, K = 60;
bool check(int x, int y) {
	for (int i = 1; i <= n; ++i) {
		if ((abs(x - e[i].x) + abs(y - e[i].y)) % e[i].k != e[i].t)
			return 0;
	}
	return 1; 
}

ll cal(int l, int r) {
	r = r - l - 1;
    if (r < 0) return 0;	
	return r / K + 1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		hx.init(); hy.init();
		hx.add(m + 1); hy.add(m + 1); hx.add(0); hy.add(0);
		for (int i = 1; i <= n; ++i) e[i].scan();
		hx.work(); hy.work();
		ll res = 0;
		for (int i = 1; i < hx.cnt; ++i)
			for (int j = 1; j < hy.cnt; ++j) 
				for (int x = 0; x < K; ++x)
					for (int y = 0; y < K; ++y) {
						if (check(hx.a[i] + x, hy.a[j] + y)) {
							res += 1ll * cal(hx.a[i] + x, hx.a[i + 1]) * cal(hy.a[j] + y, hy.a[j + 1]);		
						}
					}
		printf("%lld\n", res);
	}
	return 0;
}
