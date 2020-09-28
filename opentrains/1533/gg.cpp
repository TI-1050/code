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
		if (x == 0) return;
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
		int pos = -1; 
		for (int i = 1; i <= n; ++i) {
			if (a[i] == Max) {
				pos = i;
				break;
			}
		}
		ll res = 1e18;
		//往左走
		ll f = 0, g = 0;
		bit[0].init(), bit[1].init(); 
		for (int i = n; i > pos; --i) {
			g += bit[1].query(a[i] + 1, 100000);
			bit[1].update(a[i], 1);   
		}
		for (int i = 1; i < pos; ++i) {
			f += bit[0].query(a[i] + 1, 100000);
			bit[0].update(a[i], 1);
		}
		for (int i = pos, base = 0; i >= 1; --i, ++base) {
			res = min(res, f + g + base);
			cout << i << " " << f + g + base << endl;
			f -= bit[0].query(a[i - 1] + 1, 100000);
			g += bit[1].query(a[i - 1] + 1, 100000);
			bit[0].update(a[i - 1], -1);
			bit[1].update(a[i - 1], 1);
		}
		if (pos < n) {
			//往右走
			bit[0].init(); bit[1].init();
			f = g = 0;
			for (int i = n; i > pos + 1; --i) {
				g += bit[1].query(a[i] + 1, 100000);
				bit[1].update(a[i], 1);
			}
			for (int i = 1; i < pos; ++i) {
				f += bit[0].query(a[i] + 1, 100000);
				bit[0].update(a[i], 1);
			}
			f += bit[0].query(a[pos + 1] + 1, 100000);
			bit[0].update(a[pos + 1], 1);
			for (int i = pos + 1, base = 0; i <= n; ++i) {
				if (a[i] != Max) {
					++base;
				}
				res = min(res, f + g + base);
				cout << i << " " << f + g + base << endl;
				f += bit[0].query(a[i + 1] + 1, 100000);
				g -= bit[1].query(a[i + 1] + 1, 100000);
				bit[0].update(a[i + 1], 1);
				bit[1].update(a[i + 1], -1);
			}
		}
		printf("%lld\n", res); 
	}
	return 0;
}
