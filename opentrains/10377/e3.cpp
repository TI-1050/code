#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 2e5 + 10, M = 23, INF = 0x3f3f3f3f;
int n, pre[N], suf[N]; pII a[N], b[N], f[N][M];
struct SEG {
	pII t[N << 2];
	function <pII(int)> setv;
	void init(const function <pII(int)> &_setv) { setv = _setv; }
	void up(pII &a, pII b, pII c) {
		a.fi = min(b.fi, c.fi);
		a.se = max(b.se, c.se);
	} 
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = setv(l);
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		up(t[id], t[id << 1], t[id << 1 | 1]);
	}
	pII query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		pII res = pII(INF, -INF); 
		if (ql <= mid) up(res, res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) up(res, res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg[M];

inline pII go(SEG &seg, pII a) {
	return seg.query(1, 1, n, a.fi, a.se);
}

bool check(int x) {
	for (int i = 1; i <= n; ++i) b[i] = go(seg[x], a[i]);
	pre[0] = n;
	for (int i = 1; i <= n; ++i) pre[i] = min(pre[i - 1], b[i].se);
	suf[n + 1] = 0;
	for (int i = n; i >= 1; --i) suf[i] = max(suf[i + 1], b[i].fi);
	for (int i = 1; i <= n; ++i) {
		if (pre[b[i].fi - 1] < i) return 1;
		if (suf[b[i].se + 1] > i) return 1;
	}
	return 0;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			a[i] = pII(i, i); 
			f[i][0] = pII(max(1, i - x), min(n, i + x));
		}
		seg[0].init([&](int x) { return f[x][0]; });
		seg[0].build(1, 1, n);
		for (int i = 1; i < M; ++i) {
			for (int j = 1; j <= n; ++j) {
				f[j][i] = go(seg[i - 1], f[j][i - 1]);
			}
			seg[i].init([&](int x) { return f[x][i]; });
			seg[i].build(1, 1, n);
		}
		int ans = 0;
		for (int i = M - 1; i >= 0; --i) {
			if (check(i)) {
				for (int j = 1; j <= n; ++j) a[j] = b[j];
				ans |= 1 << i;
			}
		}
		printf("%d\n", ans + 1);
	}
	return 0;
}
