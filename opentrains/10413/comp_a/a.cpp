#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e5 + 100;

struct BIT_2D {
	struct BIT {
		int n;
		ll a[N];
		void Init(int _n) {
			n = _n;
			memset(a, 0, sizeof(a[0]) * (_n + 10));
		}

		void add(ll x, ll v) {
			for (; x <= n; a[x] += v, x += x & -x);
		}

		ll ask(ll x) {
			ll res = 0;
			for (; x > 0; res += a[x], x -= x & -x);
			return res;
		}
	}bit1, bit2;

	void Init(int _n) {
		bit1.Init(_n);
		bit2.Init(_n);
	}

	ll ask(ll x) {
		return (x + 1) * bit1.ask(x) - bit2.ask(x);
	}

	void add(ll x, ll v) {
		bit1.add(x, v);
		bit2.add(x, x * v);
	}

	ll ask(ll l, ll r) {
		if (l > r) return 0ll;
		return ask(r) - ask(l - 1);
	}

	void add(ll l, ll r, ll v) {
		if (l > r) return ;
		add(l, v);
		add(r + 1, -v);
	}
}bit;

int d, na, nb, nc;

int a[N], b[N], c[N];
int lb[N], la[N], rb[N], ra[N];

int main() {
	while (scanf("%d %d %d %d", &d, &na, &nb, &nc) != EOF) {
		bit.Init(nc + 10);
		for (int i = 1; i <= na; ++i) scanf("%d", a + i);
		for (int i = 1; i <= nb; ++i) scanf("%d", b + i);
		for (int i = 1; i <= nc; ++i) scanf("%d", c + i);
		for (int i = 1, l = 1, r = 0; i <= na; ++i) {
			while (r + 1 <= nc && c[r + 1] - a[i] <= d) ++r;
			while (l <= nc && a[i] - c[l] > d) ++l;
			la[i] = l, ra[i] = r;
		}
		for (int i = 1, l = 1, r = 0; i <= nb; ++i) {
			while (r + 1 <= nc && c[r + 1] - b[i] <= d) ++r;
		while (l <= nc && a[i] - c[l] > d) ++l;
			lb[i] = l, rb[i] = r;
		}
		ll res = 0;
		for (int i = 1, l = 1, r = 0; i <= na; ++i) {
			while (r + 1 <= nb && b[r + 1] - a[i] <= d) {
				++r;
				bit.add(lb[r], rb[r], 1);
			}
			while (l <= nb && a[i] - b[l] > d) {
				bit.add(lb[l], rb[l], -1);
				++l;
			}
			res += bit.ask(la[i], ra[i]);
		}
		printf("%lld\n", res);
	}
	return 0;
}
