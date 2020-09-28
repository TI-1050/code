#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const ll INF = 1e18; 
int n, q, a[N];
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
struct SEG {
	struct node {
		ll f[2][2];
		node() {
			memset(f, -0x3f, sizeof f); 
		}
		node operator + (const node &other) const {
			node res = node();
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {
					res.f[i][j] = max(f[i][j], other.f[i][j]);
				}
			}
			for (int i = 0; i < 2; ++i)
				for (int j = 0; j < 2; ++j)
					for (int k = 0; k < 2; ++k) 
						chmax(res.f[i][j], f[i][k] + other.f[k ^ 1][j]);
			return res;
		}
	}t[N << 2], res;
	void init() { for (int i = 0; i < N; ++i) t[i] = node(); } 
	void update(int id, int l, int r, int pos, ll v) {
		if (l == r) {
			t[id] = node();
			t[id].f[pos & 1][pos & 1] = v;
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
		seg.init();
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);	
		for (int i = 1; i <= n; ++i) seg.update(1, 1, n, i, a[i]); 
		int op, x, y;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) {
				a[x] = y;
				seg.update(1, 1, n, x, a[x]);
			} else {
				seg.res = SEG::node();
				seg.query(1, 1, n, x, y);
				ll t = -INF;
				for (int i = 0; i < 2; ++i)
					for (int j = 0; j < 2; ++j)
						chmax(t, seg.res.f[i][j]);
				printf("%lld\n", t);
			}
		}
	}
	return 0;
}
