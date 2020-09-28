#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N];

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] += v;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
}bit[2];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		int Max = *max_element(a + 1, a + 1 + n);
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		bit.init();
		for (int i = 1; i <= n; ++i) {
			f[i] = f[i - 1];
			f[i] += bit.query(a[i] + 1, 100000);
			bit.update(a[i], 1);
		}
		bit.init();
		for (int i = n; i >= 1; --i) {
			g[i] = g[i + 1];
			g[i] += bit.query(a[i] + 1, 100000);
			bit.update(a[i], 1);
		}
		int pos = -1;
		for (int i = 1; i <= n; ++i) if (a[i] == Max) {
			pos = i;
			break;
		}
		ll res = 1e18;
		for (int i = pos, base = 0; i >= 1; --i) {
			res = min(res, f[i - 1] + g[i + 1] + base);
			++base;
		}
		for (int i = pos + 1, base = 0; i <= n; ++i) {
			if (a[i] == Max) {
				base = 0;
			} else {
				++base;
			}
			res = min(res, f[i - 1] + g[i + 1] + base);
		}
		printf("%lld\n", res);
	}
	return 0;
}
