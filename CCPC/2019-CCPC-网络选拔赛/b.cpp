#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int n, q, m, a[N], b[N];

struct SEG {
	int t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = b[l]; 
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	void update(int id, int l, int r, int pos) { 
		if (l == r) {
			t[id] = INF;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos);
		else update(id << 1 | 1, mid + 1, r, pos);
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	int ask(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res = max(res, ask(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, ask(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
	int query(int id, int l, int r, int k, int R) {
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (mid < k || ask(id << 1, l, mid, k, mid) <= R) return query(id << 1 | 1, mid + 1, r, k, R);
		if (t[id << 1] <= R) return query(id << 1 | 1, mid + 1, r, k, R);
		else return query(id << 1, l, mid, k, R);
	}
}seg;

int main() {
	int _T; cin >> _T; 
	while (_T--) {
		scanf("%d%d", &n, &q); m = n + 1;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[a[i]] = i; 
		b[m] = INF;
		seg.build(1, 1, m);
		int lstans = 0; 
		for (int _q = 1, op, x, k; _q <= q; ++_q) {
			scanf("%d%d", &op, &x);
			x ^= lstans;
			if (op == 1) {
				seg.update(1, 1, m, a[x]);
			} else {
				scanf("%d", &k);
				k ^= lstans;
				printf("%d\n", lstans = seg.query(1, 1, m, k, x));
			}
		}
	}
	return 0;
}
