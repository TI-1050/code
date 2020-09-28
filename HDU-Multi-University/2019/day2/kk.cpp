#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010 
#define INF 0x3f3f3f3f
int n, q, a[N];

struct SEG {
	struct node {
		int a[55]; 
		node() {
			a[0] = 0;
		}
		void add(int x) {
			a[++a[0]] = x;
		}
		node operator + (const node &other) const {
			node res = node();
			int it = 1, it2 = 1;
			while (res.a[0] <= 50 && (it <= a[0] || it2 <= other.a[0])) {
				if (it > a[0]) {
					res.add(other.a[it2]);
					++it2;
				} else if (it2 > other.a[0]) {
					res.add(a[it]);
					++it;
				} else {
					if (a[it] > other.a[it2]) {
						res.add(a[it]);
						++it;
					} else {
						res.add(other.a[it2]);
						++it2;
					}
				}
			}
			return res;
		}
	}t[N << 2], res;
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].add(a[l]);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) {
			res = res + t[id];
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid) query(id << 1, l, mid, ql, qr);
		if (qr > mid) query(id << 1 | 1, mid + 1, r, ql, qr);
	}
}seg;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		seg.build(1, 1, n);
		int l, r;
		while (q--) {
			scanf("%d%d", &l, &r);
			ll res = -1;
			seg.res = SEG::node();
			seg.query(1, 1, n, l, r);
			int sze = seg.res.a[0];
			for (int i = 1; i <= sze - 2; ++i) {
				ll A = seg.res.a[i], B = seg.res.a[i + 1], C = seg.res.a[i + 2];
				if (A < B + C) {
					res = A + B + C;
					break;
				}
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}
