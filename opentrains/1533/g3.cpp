#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N];
ll res;

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
		if (l > r) return 0;
		return query(r) - query(l - 1);   
	}
}bit;

void work(int l, int r) {
	while (l <= r) {
		int x = bit.query(1, a[l].se - 1);
		int y = bit.query(a[r].se + 1, n);
		if (x < y) {
			res += x;
			bit.update(a[l].se, -1);
			++l;
		} else {
			res += y;
			bit.update(a[r].se, -1);
			--r;
		}
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].fi);
			a[i].se = i;
		}
		bit.init();
		for (int i = 1; i <= n; ++i) {
			bit.update(i, 1);
		}
		sort(a + 1, a + 1 + n);
		res = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = i;
			while (j < n && a[j + 1].fi == a[j].fi) {
				++j;
			}
			work(i, j);
		}
		printf("%lld\n", res);
	}
	return 0;
}
