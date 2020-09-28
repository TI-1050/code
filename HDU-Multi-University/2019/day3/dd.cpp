#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define N 400010
int n, k;
ll a[N], b[N]; 

void Hash(ll *b) {
	sort(b + 1, b + 1 + b[0]);
	b[0] = unique(b + 1, b + 1 + b[0]) - b - 1;
}

int get(ll x) {
	return lower_bound(b + 1, b + 1 + b[0], x) - b; 
}

struct SEG {
	struct node {
		int Max;
		node() {
			Max = -INF;
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
	void update(int id, int l, int r, int pos, int x) {
		if (l == r) {
			t[id].Max = max(t[id].Max, x);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return -INF;
		if (l >= ql && r <= qr) {
			return t[id].Max;
		}
		int mid = (l + r) >> 1;
		int res = -INF;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

bool check(ll x) {
	b[0] = 0;
	b[++b[0]] = 0;
	for (int i = 1; i <= n; ++i) {
		b[++b[0]] = a[i];
		b[++b[0]] = a[i] - x;
	}	
	Hash(b);
	seg.build(1, 1, b[0]);
	seg.update(1, 1, b[0], get(0), 0);
	for (int i = 1; i <= n; ++i) {
		int f = seg.query(1, 1, b[0], get(a[i] - x), b[0]) + 1;
		if (f >= k) return 1;
		seg.update(1, 1, b[0], get(a[i]), f);
	}
	return 0;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); scanf("%d", &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
			a[i] += a[i - 1];
		}
		ll l = -2e15, r = 1e9, res = -1;
		while (r - l >= 0) {
			ll mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				res = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
