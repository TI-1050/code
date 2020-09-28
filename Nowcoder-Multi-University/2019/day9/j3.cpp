#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 9e5 + 10;

struct node {
	int l, r, x;
   	int op;

	node() {}

	node (ll l, ll r, ll x, int op): l(l), r(r), x(x), op(op){}

	bool operator < (const node &other) const {
		return x < other.x;
	}
}a[N];

int n;

int main() {
	while (~scanf("%d", &n)) {
		int cnt = 0;
		ll l, r;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld %lld", &l, &r);
			l <<= 1, r <<= 1;
			ll mid = (l + r) >> 1;
			a[++cnt] = node(l, r, l, 1);
			a[++cnt] = node(l, r, r, 2);
			a[++cnt] = node(l, r, mid, 3);
		}
		sort(a + 1, a + 1 + cnt);
		ll res = 0;
		ll up_num = 0, sum_up = 0, down_num = 0, sum_down = 0;
		for (int i = 1; i <= cnt; ++i) {
			if (a[i].op == 1) {
				down_num++;
				sum_down += a[i].l;
			} else if (a[i].op == 2) {
				up_num--;
				sum_up -= a[i].r;
			} else {
				down_num--;
				sum_down -= a[i].l;
				up_num++;
				sum_up += a[i].r;
			}
			int x = a[i].x;
			res = max(res, (down_num * x - sum_down + sum_up - up_num * x) * 2ll);
		}
		printf("%lld\n", res / 2);
	}
	return 0;
}
