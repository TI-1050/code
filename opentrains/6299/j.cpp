#include <bits/stdc++.h>
using namespace std;
using ll = __int128;
const int N = 2e5 + 10;
const ll INF = 1e18; 
int n, m, q, a[N];

struct SEG {
	struct node {
		//0 left
		//1 right
		//2 all
		ll Max[3], sum;
		node() {
			Max[0] = Max[1] = Max[2] = sum = -INF;  
		}
		node operator + (const node &other) const {
			node res = node();
			res.sum = sum + other.sum;
			res.Max[0] = max(Max[0], sum + other.Max[0]);
			res.Max[1] = max(other.Max[1], other.sum + Max[1]);
			res.Max[2] = max(Max[2], other.Max[2]);
			res.Max[2] = max(res.Max[2], Max[1] + other.Max[0]);
			return res;
		}
	}t[N << 2], res;
	void init() { memset(t, 0, sizeof t); }
	void update(int id, int l, int r, int pos, ll v) {
		if (l == r) {
			t[id].sum = v;
			for (int i = 0; i < 3; ++i)
				t[id].Max[i] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, v);
		else update(id << 1 | 1, mid + 1, r, pos, v);
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
		seg.init(); m = 2 * n - 1;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);	
		for (int i = 1; i <= n; ++i) seg.update(1, 1, m, 2 * i - 1, a[i]);
		for (int i = 2; i <= n; ++i) {
			if (a[i] == a[i - 1]) {
				seg.update(1, 1, m, 2 * i - 2, -INF); 
			} else {
				seg.update(1, 1, m, 2 * i - 2, 0);
			}
		}
		int op, x, y;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				a[x] = y;
				seg.update(1, 1, m, 2 * x - 1, a[x]);
				if (x != 1) seg.update(1, 1, m, 2 * x - 2, (a[x] == a[x - 1]) ? -INF : 0);
			   	if (x != n) seg.update(1, 1, m, 2 * x, (a[x] == a[x + 1]) ? -INF : 0);	
			} else {
				seg.res = SEG::node();
				seg.query(1, 1, m, 2 * x - 1, 2 * y - 1);
				long long t = seg.res.Max[2];
				printf("%lld\n", t);
			}
		}
	}
	return 0;
}
