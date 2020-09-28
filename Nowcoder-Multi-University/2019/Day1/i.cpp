#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
#define N 100010
int n, m;
ll H[N];
struct node {
	ll x, y, a, b;
	node() {}
	void scan() {   
		scanf("%lld%lld%lld%lld", &x, &y, &a, &b);
		H[++m] = y;
	}
	bool operator < (const node &other) const {
		if (x != other.x) return x < other.x;
		return y > other.y;
	}
}a[N];

struct SEG {
	struct node {
		ll Max, lazy;
		node() {
			Max = lazy = 0;
		}
		void add(ll x) {
			Max += x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.Max = max(Max, other.Max);
			return res;
		}
	}t[N << 2];
	void build(int id, int l, int r) {
		t[id] = node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void pushdown(int id) {
		ll &lazy = t[id].lazy;
		if (!lazy) return;
		t[id << 1].add(lazy);
		t[id << 1 | 1].add(lazy);
		lazy = 0;
	}
	void update(int id, int l, int r, int ql, int qr, ll x) {
		if (l >= ql && r <= qr) {
			t[id].add(x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (ql <= mid) update(id << 1, l, mid, ql, qr, x);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update2(int id, int l, int r, int pos, ll x) {
		if (l == r) {
			t[id].Max = max(t[id].Max, x);
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		if (pos <= mid) update2(id << 1, l, mid, pos, x);
		else update2(id << 1 | 1, mid + 1, r, pos, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			return t[id].Max;
		}
		int mid = (l + r) >> 1;
		pushdown(id);
		ll res = 0;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int main() {
	while (scanf("%d", &n) != EOF) {
		m = 0;
		H[++m] = -INF;
		H[++m] = INF;
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		sort(a + 1, a + 1 + n);
		sort(H + 1, H + 1 + m);
		m = unique(H + 1, H + 1 + m) - H - 1;
		for (int i = 1; i <= n; ++i) {
			a[i].y = lower_bound(H + 1, H + 1 + m, a[i].y) - H;
		}
		seg.build(1, 1, m);
		for (int i = 1; i <= n; ++i) {
			ll g = seg.query(1, 1, m, 1, a[i].y);
			seg.update2(1, 1, m, a[i].y, g + a[i].b);
			seg.update(1, 1, m, a[i].y + 1, m, a[i].b);
			seg.update(1, 1, m, 1, a[i].y - 1, a[i].a); 
		}
		printf("%lld\n", seg.t[1].Max);
	}
	return 0;
}
